/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Cone
*/

#include <cmath>
#include <optional>
#include "Cone.hpp"
#include "Template.hpp"
#include "Vector3D.hpp"

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

Math::Vector3D add(const Math::Vector3D &lhs, const Math::Vector3D &rhs)
{
    return Math::Vector3D(lhs._xCmp + rhs._xCmp,
        lhs._yCmp + rhs._yCmp,
        lhs._zCmp + rhs._zCmp);
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
    return angleDegrees * PI / 180.0;
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

RayTracer::Cone::Cone(const Math::Point3D &apex, double height, double baseRadius,
    std::unique_ptr<Interfaces::IMaterial> material)
    : _apex(apex), _axis(0, 1, 0), _height(height), _baseRadius(baseRadius),
    _material(std::move(material))
{
}

std::optional<hitRecord> RayTracer::Cone::hits(const RayTracer::Ray &ray) const
{
    std::optional<hitRecord> best;

    considerHit(best, _intersectSurface(ray));
    considerHit(best, _intersectBase(ray));
    return best;
}

std::optional<hitRecord> RayTracer::Cone::_intersectSurface(
    const RayTracer::Ray &ray) const
{
    const auto apexToOrigin = computeVectorBetween(_apex, ray._origin);
    const auto &direction = ray._direction;
    const double directionAlong = direction.dot(_axis);
    const double originAlong = apexToOrigin.dot(_axis);
    const double cosThetaSq = (_height * _height)
        / (_height * _height + _baseRadius * _baseRadius);
    const double coefA = directionAlong * directionAlong
        - cosThetaSq * direction.dot(direction);
    const double coefB = 2.0 * (originAlong * directionAlong
        - cosThetaSq * apexToOrigin.dot(direction));
    const double coefC = originAlong * originAlong
        - cosThetaSq * apexToOrigin.dot(apexToOrigin);
    const auto distance = findNearestPositiveRoot(coefA, coefB, coefC);

    if (!distance)
        return std::nullopt;
    const auto hitPoint = computePointAlongRay(ray, *distance);
    const double along = computeVectorBetween(_apex, hitPoint).dot(_axis);

    if (along > 0 || along < -_height)
        return std::nullopt;
    return _buildSurfaceHit(ray, hitPoint, *distance);
}

std::optional<hitRecord> RayTracer::Cone::_buildSurfaceHit(
    const RayTracer::Ray &ray, const Math::Point3D &hitPoint, double distance) const
{
    const auto apexToHit = computeVectorBetween(_apex, hitPoint);
    const double along = apexToHit.dot(_axis);
    const auto radial = subtract(apexToHit, scale(_axis, along));
    const double slopeSq = (_baseRadius * _baseRadius) / (_height * _height);
    auto normal = add(radial, scale(_axis, -along * slopeSq));

    normalizeInPlace(normal);
    hitRecord record;
    record.point = hitPoint;
    record.normal = normal;
    record.t = distance;
    record.frontFace = ray._direction.dot(record.normal) < 0;
    return record;
}

std::optional<hitRecord> RayTracer::Cone::_intersectBase(
    const RayTracer::Ray &ray) const
{
    const auto baseCenter = offsetPoint(_apex, _axis, -_height);
    const auto baseNormal = scale(_axis, -1.0);
    const double denominator = ray._direction.dot(baseNormal);

    if (std::abs(denominator) < EPSILON)
        return std::nullopt;
    const auto originToBase = computeVectorBetween(ray._origin, baseCenter);
    const double distance = originToBase.dot(baseNormal) / denominator;

    if (distance <= 0)
        return std::nullopt;
    const auto hitPoint = computePointAlongRay(ray, distance);

    if (computeVectorBetween(baseCenter, hitPoint).length() > _baseRadius)
        return std::nullopt;
    hitRecord record;
    record.point = hitPoint;
    record.normal = baseNormal;
    record.t = distance;
    record.frontFace = ray._direction.dot(baseNormal) < 0;
    return record;
}

void RayTracer::Cone::translate(const Math::Vector3D &offset)
{
    _apex += offset;
}

void RayTracer::Cone::rotateX(double angleDegrees)
{
    _axis = rotateAroundX(_axis, degreesToRadians(angleDegrees));
}

void RayTracer::Cone::rotateY(double angleDegrees)
{
    _axis = rotateAroundY(_axis, degreesToRadians(angleDegrees));
}

void RayTracer::Cone::rotateZ(double angleDegrees)
{
    _axis = rotateAroundZ(_axis, degreesToRadians(angleDegrees));
}