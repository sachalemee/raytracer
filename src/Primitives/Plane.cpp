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
#include "PrimitiveUtils.hpp"
#include "Vector3D.hpp"

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
