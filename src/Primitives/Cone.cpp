/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Cone
*/

#include <cmath>
#include <optional>
#include "Cone.hpp"
#include "PrimitiveUtils.hpp"
#include "Vector3D.hpp"

RayTracer::Cone::Cone(const Math::Point3D &apex, double height, double baseRadius,
    std::unique_ptr<Interfaces::IMaterial> material)
    : _apex(apex), _axis(0, 0, 1), _height(height), _baseRadius(baseRadius),
    _material(std::move(material))
{
}

std::optional<hitRecord> RayTracer::Cone::hits(const RayTracer::Ray &ray) const
{
    std::optional<hitRecord> best;

    considerHit(best, _intersectSurface(ray));
    considerHit(best, _intersectBase(ray));
    if (best && _material)
        best->color = _material->getColor();
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
    const auto baseNormal = _axis;
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