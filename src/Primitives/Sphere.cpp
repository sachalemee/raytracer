/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Sphere
*/

#include <cmath>
#include <optional>
#include "Sphere.hpp"
#include "PrimitiveUtils.hpp"

RayTracer::Sphere::Sphere(const Math::Point3D &center, double radius)
    : _sphCenter(center), _sphRadius(radius)
{
}

std::optional<hitRecord> RayTracer::Sphere::hits(const RayTracer::Ray &ray) const
{
    const auto originToCenter = computeVectorBetween(_sphCenter, ray._origin);
    const double coefA = ray._direction.dot(ray._direction);
    const double coefB = 2.0 * originToCenter.dot(ray._direction);
    const double coefC = originToCenter.dot(originToCenter)
        - square(_sphRadius);
    const auto distance = findNearestPositiveRoot(coefA, coefB, coefC);

    if (!distance)
        return std::nullopt;
    return buildSpherehitRecord(ray, *distance, _sphCenter);
}

void RayTracer::Sphere::translate(const Math::Vector3D &offset)
{
    _sphCenter += offset;
}

void RayTracer::Sphere::rotateX(double angleDegrees)
{
    const auto [cosA, sinA] = computeAngleTrig(angleDegrees);

    rotatePointAroundX(_sphCenter, cosA, sinA);
}

void RayTracer::Sphere::rotateY(double angleDegrees)
{
    const auto [cosA, sinA] = computeAngleTrig(angleDegrees);

    rotatePointAroundY(_sphCenter, cosA, sinA);
}

void RayTracer::Sphere::rotateZ(double angleDegrees)
{
    const auto [cosA, sinA] = computeAngleTrig(angleDegrees);

    rotatePointAroundZ(_sphCenter, cosA, sinA);
}
