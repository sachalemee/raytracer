/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Sphere
*/

#include <cmath>
#include <optional>
#include <utility>
#include "Sphere.hpp"
#include "Template.hpp"

Math::Vector3D computeVectorBetween(const Math::Point3D &from,
    const Math::Point3D &to)
{
    return Math::Vector3D(
        to._xCmp - from._xCmp,
        to._yCmp - from._yCmp,
        to._zCmp - from._zCmp);
}

Math::Vector3D negateVector(const Math::Vector3D &vector)
{
    return Math::Vector3D(-vector._xCmp, -vector._yCmp, -vector._zCmp);
}

void normalize(Math::Vector3D &vector)
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
    double sqrtDiscriminant;
    double firstRoot;
    double secondRoot;
    double discriminant;

    if (std::abs(coefA) < EPSILON)
        return std::nullopt;
    discriminant = discriminantEquation(coefB, coefA, coefC);
    if (discriminant < 0)
        return std::nullopt;
    sqrtDiscriminant = std::sqrt(discriminant);
    firstRoot = (-coefB - sqrtDiscriminant) / (2.0 * coefA);
    secondRoot = (-coefB + sqrtDiscriminant) / (2.0 * coefA);
    if (firstRoot > 0)
        return firstRoot;
    if (secondRoot > 0)
        return secondRoot;
    return std::nullopt;
}

hitRecord buildSpherehitRecord(const RayTracer::Ray &ray, double distance,
    const Math::Point3D &center)
{
    hitRecord record;

    record.point = Math::Point3D(
        ray._origin._xCmp + ray._direction._xCmp * distance,
        ray._origin._yCmp + ray._direction._yCmp * distance,
        ray._origin._zCmp + ray._direction._zCmp * distance);
    record.t = distance;
    auto outwardNormal = computeVectorBetween(center, record.point);
    normalize(outwardNormal);
    record.frontFace = ray._direction.dot(outwardNormal) < 0;
    record.normal = record.frontFace ? outwardNormal
        : negateVector(outwardNormal);
    return record;
}

std::pair<double, double> computeAngleTrig(double angleDegrees)
{
    const double angleRad = angleDegrees * PI / 180.0;
    return {std::cos(angleRad), std::sin(angleRad)};
}

void rotatePointAroundX(Math::Point3D &point, double cosA, double sinA)
{
    const double newY = point._yCmp * cosA - point._zCmp * sinA;
    const double newZ = point._yCmp * sinA + point._zCmp * cosA;

    point._yCmp = newY;
    point._zCmp = newZ;
}

void rotatePointAroundY(Math::Point3D &point, double cosA, double sinA)
{
    const double newX = point._xCmp * cosA + point._zCmp * sinA;
    const double newZ = -point._xCmp * sinA + point._zCmp * cosA;

    point._xCmp = newX;
    point._zCmp = newZ;
}

void rotatePointAroundZ(Math::Point3D &point, double cosA, double sinA)
{
    const double newX = point._xCmp * cosA - point._yCmp * sinA;
    const double newY = point._xCmp * sinA + point._yCmp * cosA;

    point._xCmp = newX;
    point._yCmp = newY;
}

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
