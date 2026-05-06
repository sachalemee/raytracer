/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Cylinder
*/

#include "Cylinder.hpp"
#include "Template.hpp"
#include "Vector3D.hpp"
#include <cmath>
#include <numbers>
#include <optional>

namespace {
    constexpr double EPSILON = 1e-6;

    Math::Vector3D computeVectorBetween(const Math::Point3D &from,
        const Math::Point3D &to)
    {
        return Math::Vector3D(
            to._xCmp - from._xCmp,
            to._yCmp - from._yCmp,
            to._zCmp - from._zCmp);
    }

    Math::Vector3D scale(const Math::Vector3D &vector, double factor)
    {
        return Math::Vector3D(vector._xCmp * factor,
            vector._yCmp * factor,
            vector._zCmp * factor);
    }

    Math::Vector3D subtract(const Math::Vector3D &lhs, const Math::Vector3D &rhs)
    {
        return Math::Vector3D(lhs._xCmp - rhs._xCmp,
            lhs._yCmp - rhs._yCmp,
            lhs._zCmp - rhs._zCmp);
    }

    Math::Point3D offsetPoint(const Math::Point3D &point,
        const Math::Vector3D &direction, double scalar)
    {
        return Math::Point3D(point._xCmp + direction._xCmp * scalar,
            point._yCmp + direction._yCmp * scalar,
            point._zCmp + direction._zCmp * scalar);
    }

    Math::Point3D computePointAlongRay(const RayTracer::Ray &ray, double distance)
    {
        return offsetPoint(ray._origin, ray._direction, distance);
    }

    Math::Vector3D projectPerpendicular(const Math::Vector3D &vector,
        const Math::Vector3D &axis)
    {
        return subtract(vector, scale(axis, vector.dot(axis)));
    }

    void normalizeInPlace(Math::Vector3D &vector)
    {
        const double length = vector.length();

        if (length <= 0)
            return;
        vector._xCmp /= length;
        vector._yCmp /= length;
        vector._zCmp /= length;
    }

    std::optional<double> findNearestPositiveRoot(double coefA, double coefB,
        double coefC)
    {
        if (std::abs(coefA) < EPSILON)
            return std::nullopt;
        const double discriminant = discriminantEquation(coefB, coefA, coefC);
        if (discriminant < 0)
            return std::nullopt;

        const double sqrtDiscriminant = std::sqrt(discriminant);
        const double firstRoot = (-coefB - sqrtDiscriminant) / (2.0 * coefA);
        const double secondRoot = (-coefB + sqrtDiscriminant) / (2.0 * coefA);

        if (firstRoot > 0)
            return firstRoot;
        if (secondRoot > 0)
            return secondRoot;
        return std::nullopt;
    }

    void considerHit(std::optional<hitRecord> &best,
        const std::optional<hitRecord> &candidate)
    {
        if (candidate && (!best || candidate->t < best->t))
            best = candidate;
    }

    double degreesToRadians(double angleDegrees)
    {
        return angleDegrees * std::numbers::pi / 180.0;
    }

    Math::Vector3D rotateAroundX(const Math::Vector3D &vector, double angleRad)
    {
        const double cosA = std::cos(angleRad);
        const double sinA = std::sin(angleRad);

        return Math::Vector3D(vector._xCmp,
            vector._yCmp * cosA - vector._zCmp * sinA,
            vector._yCmp * sinA + vector._zCmp * cosA);
    }

    Math::Vector3D rotateAroundY(const Math::Vector3D &vector, double angleRad)
    {
        const double cosA = std::cos(angleRad);
        const double sinA = std::sin(angleRad);

        return Math::Vector3D(vector._xCmp * cosA + vector._zCmp * sinA,
            vector._yCmp,
            -vector._xCmp * sinA + vector._zCmp * cosA);
    }

    Math::Vector3D rotateAroundZ(const Math::Vector3D &vector, double angleRad)
    {
        const double cosA = std::cos(angleRad);
        const double sinA = std::sin(angleRad);

        return Math::Vector3D(vector._xCmp * cosA - vector._yCmp * sinA,
            vector._xCmp * sinA + vector._yCmp * cosA,
            vector._zCmp);
    }
}

RayTracer::Cylinder::Cylinder(const Math::Point3D &center, double radius,
    double height, std::unique_ptr<Interfaces::IMaterial> material)
    : _center(center), _axis(0, 1, 0), _radius(radius), _height(height),
    _material(std::move(material))
{
}

std::optional<hitRecord> RayTracer::Cylinder::hits(const RayTracer::Ray &ray) const
{
    const double halfHeight = _height / 2;
    const auto topCenter = offsetPoint(_center, _axis, halfHeight);
    const auto bottomCenter = offsetPoint(_center, _axis, -halfHeight);
    const auto reversedAxis = scale(_axis, -1.0);
    std::optional<hitRecord> best;

    considerHit(best, _intersectBody(ray));
    considerHit(best, _intersectCap(ray, topCenter, _axis));
    considerHit(best, _intersectCap(ray, bottomCenter, reversedAxis));
    return best;
}

std::optional<hitRecord> RayTracer::Cylinder::_intersectBody(
    const RayTracer::Ray &ray) const
{
    const auto originToCenter = computeVectorBetween(_center, ray._origin);
    const auto originPerp = projectPerpendicular(originToCenter, _axis);
    const auto directionPerp = projectPerpendicular(ray._direction, _axis);
    const auto distance = findNearestPositiveRoot(
        directionPerp.dot(directionPerp),
        2.0 * originPerp.dot(directionPerp),
        originPerp.dot(originPerp) - square(_radius));

    if (!distance)
        return std::nullopt;
    const auto hitPoint = computePointAlongRay(ray, *distance);
    const double along = computeVectorBetween(_center, hitPoint).dot(_axis);

    if (std::abs(along) > _height / 2)
        return std::nullopt;
    return _buildBodyHit(ray, hitPoint, *distance);
}

std::optional<hitRecord> RayTracer::Cylinder::_buildBodyHit(
    const RayTracer::Ray &ray, const Math::Point3D &hitPoint, double distance) const
{
    auto normal = projectPerpendicular(computeVectorBetween(_center, hitPoint),
        _axis);
    normalizeInPlace(normal);

    hitRecord record;
    record.point = hitPoint;
    record.normal = normal;
    record.t = distance;
    record.frontFace = ray._direction.dot(normal) < 0;
    return record;
}

std::optional<hitRecord> RayTracer::Cylinder::_intersectCap(
    const RayTracer::Ray &ray, const Math::Point3D &capCenter,
    const Math::Vector3D &capNormal) const
{
    const double denominator = ray._direction.dot(capNormal);

    if (std::abs(denominator) < EPSILON)
        return std::nullopt;
    const auto originToCap = computeVectorBetween(ray._origin, capCenter);
    const double distance = originToCap.dot(capNormal) / denominator;

    if (distance <= 0)
        return std::nullopt;
    const auto hitPoint = computePointAlongRay(ray, distance);

    if (computeVectorBetween(capCenter, hitPoint).length() > _radius)
        return std::nullopt;
    hitRecord record;
    record.point = hitPoint;
    record.normal = capNormal;
    record.t = distance;
    record.frontFace = ray._direction.dot(capNormal) < 0;
    return record;
}

void RayTracer::Cylinder::translate(const Math::Vector3D &offset)
{
    _center += offset;
}

void RayTracer::Cylinder::rotateX(double angleDegrees)
{
    _axis = rotateAroundX(_axis, degreesToRadians(angleDegrees));
}

void RayTracer::Cylinder::rotateY(double angleDegrees)
{
    _axis = rotateAroundY(_axis, degreesToRadians(angleDegrees));
}

void RayTracer::Cylinder::rotateZ(double angleDegrees)
{
    _axis = rotateAroundZ(_axis, degreesToRadians(angleDegrees));
}