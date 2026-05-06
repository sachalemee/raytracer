/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Plane
*/

#include <cmath>
#include <optional>
#include <utility>
#include "Plane.hpp"
#include "Vector3D.hpp"

namespace {
    Math::Vector3D computeVectorBetween(const Math::Point3D &from,
        const Math::Point3D &to)
    {
        return Math::Vector3D(
            to._xCmp - from._xCmp,
            to._yCmp - from._yCmp,
            to._zCmp - from._zCmp);
    }

    Math::Point3D computePointAlongRay(const RayTracer::Ray &ray, double distance)
    {
        return Math::Point3D(
            ray._origin._xCmp + ray._direction._xCmp * distance,
            ray._origin._yCmp + ray._direction._yCmp * distance,
            ray._origin._zCmp + ray._direction._zCmp * distance);
    }

    Math::Vector3D negateVector(const Math::Vector3D &vector)
    {
        return Math::Vector3D(-vector._xCmp, -vector._yCmp, -vector._zCmp);
    }

    std::pair<double, double> computeAngleTrig(double angleDegrees)
    {
        const double angleRad = angleDegrees * PI / 180.0;
        return {std::cos(angleRad), std::sin(angleRad)};
    }

    void rotateVectorAroundX(Math::Vector3D &vector, double cosA, double sinA)
    {
        const double newY = vector._yCmp * cosA - vector._zCmp * sinA;
        const double newZ = vector._yCmp * sinA + vector._zCmp * cosA;
        vector._yCmp = newY;
        vector._zCmp = newZ;
    }

    void rotateVectorAroundY(Math::Vector3D &vector, double cosA, double sinA)
    {
        const double newX = vector._xCmp * cosA + vector._zCmp * sinA;
        const double newZ = -vector._xCmp * sinA + vector._zCmp * cosA;
        vector._xCmp = newX;
        vector._zCmp = newZ;
    }

    void rotateVectorAroundZ(Math::Vector3D &vector, double cosA, double sinA)
    {
        const double newX = vector._xCmp * cosA - vector._yCmp * sinA;
        const double newY = vector._xCmp * sinA + vector._yCmp * cosA;
        vector._xCmp = newX;
        vector._yCmp = newY;
    }
}

RayTracer::Plane::Plane(const Math::Point3D &position,
    const Math::Vector3D &normal,
    std::unique_ptr<Interfaces::IMaterial> material)
    : _position(position), _normal(normal), _material(std::move(material))
{
    _normalizeNormal();
}

void RayTracer::Plane::_normalizeNormal()
{
    const double length = _normal.length();

    if (length <= 0)
        return;
    _normal._xCmp /= length;
    _normal._yCmp /= length;
    _normal._zCmp /= length;
}

std::optional<hitRecord> RayTracer::Plane::hits(const RayTracer::Ray &ray) const
{
    const double denominator = ray._direction.dot(_normal);

    if (std::abs(denominator) < EPSILON)
        return std::nullopt;
    const auto posToOrigin = computeVectorBetween(ray._origin, _position);
    const double distance = posToOrigin.dot(_normal) / denominator;

    if (distance <= 0)
        return std::nullopt;
    hitRecord record;
    record.point = computePointAlongRay(ray, distance);
    record.t = distance;
    record.frontFace = denominator < 0;
    record.normal = record.frontFace ? _normal : negateVector(_normal);
    return record;
}

void RayTracer::Plane::translate(const Math::Vector3D &offset)
{
    _position += offset;
}

void RayTracer::Plane::rotateX(double angleDegrees)
{
    const auto [cosA, sinA] = computeAngleTrig(angleDegrees);

    rotateVectorAroundX(_normal, cosA, sinA);
}

void RayTracer::Plane::rotateY(double angleDegrees)
{
    const auto [cosA, sinA] = computeAngleTrig(angleDegrees);

    rotateVectorAroundY(_normal, cosA, sinA);
}

void RayTracer::Plane::rotateZ(double angleDegrees)
{
    const auto [cosA, sinA] = computeAngleTrig(angleDegrees);

    rotateVectorAroundZ(_normal, cosA, sinA);
}
