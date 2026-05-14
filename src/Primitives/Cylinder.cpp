/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Cylinder
*/

#include <cmath>
#include <optional>
#include "Cylinder.hpp"
#include "PrimitiveUtils.hpp"
#include "Vector3D.hpp"

RayTracer::Cylinder::Cylinder(const Math::Point3D &center, double radius,
    double height, std::unique_ptr<Interfaces::IMaterial> material)
    : _center(center), _axis(0, 0, 1), _radius(radius), _height(height),
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
    if (best)
        applyMaterial(*best, ray, _material);
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
