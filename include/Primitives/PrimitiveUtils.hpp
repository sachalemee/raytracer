/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Primitive Utils - Shared utility functions for primitives
*/

#ifndef PRIMITIVEUTILS_HPP_
#define PRIMITIVEUTILS_HPP_

#include <optional>
#include <utility>
#include <cmath>
#include <memory>
#include "Point3D.hpp"
#include "RayTracer.hpp"
#include "Vector3D.hpp"
#include "Ray.hpp"
#include "Template.hpp"
#include "IMaterial.hpp"

#define PI 3.14159265358979323846
#define EPSILON 1e-9

inline Math::Vector3D computeVectorBetween(const Math::Point3D &from,
    const Math::Point3D &to)
{
    return Math::Vector3D(
        to._xCmp - from._xCmp,
        to._yCmp - from._yCmp,
        to._zCmp - from._zCmp);
}

inline Math::Vector3D scale(const Math::Vector3D &vector, double factor)
{
    return Math::Vector3D(vector._xCmp * factor,
        vector._yCmp * factor,
        vector._zCmp * factor);
}

inline Math::Vector3D subtract(const Math::Vector3D &lhs, const Math::Vector3D &rhs)
{
    return Math::Vector3D(lhs._xCmp - rhs._xCmp,
        lhs._yCmp - rhs._yCmp,
        lhs._zCmp - rhs._zCmp);
}

inline Math::Vector3D add(const Math::Vector3D &lhs, const Math::Vector3D &rhs)
{
    return Math::Vector3D(lhs._xCmp + rhs._xCmp,
        lhs._yCmp + rhs._yCmp,
        lhs._zCmp + rhs._zCmp);
}

inline Math::Vector3D negateVector(const Math::Vector3D &vector)
{
    return Math::Vector3D(-vector._xCmp, -vector._yCmp, -vector._zCmp);
}

inline Math::Point3D offsetPoint(const Math::Point3D &point,
    const Math::Vector3D &direction, double scalar)
{
    return Math::Point3D(point._xCmp + direction._xCmp * scalar,
        point._yCmp + direction._yCmp * scalar,
        point._zCmp + direction._zCmp * scalar);
}

inline Math::Point3D computePointAlongRay(const RayTracer::Ray &ray, double distance)
{
    return offsetPoint(ray._origin, ray._direction, distance);
}

inline Math::Vector3D projectPerpendicular(const Math::Vector3D &vector,
    const Math::Vector3D &axis)
{
    return subtract(vector, scale(axis, vector.dot(axis)));
}

inline void normalizeInPlace(Math::Vector3D &vector)
{
    const double length = vector.length();

    if (length <= 0)
        return;
    vector._xCmp /= length;
    vector._yCmp /= length;
    vector._zCmp /= length;
}

inline void normalize(Math::Vector3D &vector)
{
    const double length = vector.length();

    if (length <= 0)
        return;
    vector._xCmp /= length;
    vector._yCmp /= length;
    vector._zCmp /= length;
}

inline std::optional<double> findNearestPositiveRoot(double coefA, double coefB,
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

inline void considerHit(std::optional<hitRecord> &best,
    const std::optional<hitRecord> &candidate)
{
    if (candidate && (!best || candidate->t < best->t))
        best = candidate;
}

inline double degreesToRadians(double angleDegrees)
{
    return angleDegrees * PI / 180.0;
}

inline Math::Vector3D rotateAroundX(const Math::Vector3D &vector, double angleRad)
{
    const double cosA = std::cos(angleRad);
    const double sinA = std::sin(angleRad);
    return Math::Vector3D(
        vector._xCmp,
        vector._yCmp * cosA - vector._zCmp * sinA,
        vector._yCmp * sinA + vector._zCmp * cosA);
}

inline Math::Vector3D rotateAroundY(const Math::Vector3D &vector, double angleRad)
{
    const double cosA = std::cos(angleRad);
    const double sinA = std::sin(angleRad);
    return Math::Vector3D(
        vector._xCmp * cosA + vector._zCmp * sinA,
        vector._yCmp,
        -vector._xCmp * sinA + vector._zCmp * cosA);
}

inline Math::Vector3D rotateAroundZ(const Math::Vector3D &vector, double angleRad)
{
    const double cosA = std::cos(angleRad);
    const double sinA = std::sin(angleRad);
    return Math::Vector3D(
        vector._xCmp * cosA - vector._yCmp * sinA,
        vector._xCmp * sinA + vector._yCmp * cosA,
        vector._zCmp);
}

inline std::pair<double, double> computeAngleTrig(double angleDegrees)
{
    const double angleRad = angleDegrees * PI / 180.0;
    return {std::cos(angleRad), std::sin(angleRad)};
}

inline void rotatePointAroundX(Math::Point3D &point, double cosA, double sinA)
{
    const double newY = point._yCmp * cosA - point._zCmp * sinA;
    const double newZ = point._yCmp * sinA + point._zCmp * cosA;
    point._yCmp = newY;
    point._zCmp = newZ;
}

inline void rotatePointAroundY(Math::Point3D &point, double cosA, double sinA)
{
    const double newX = point._xCmp * cosA + point._zCmp * sinA;
    const double newZ = -point._xCmp * sinA + point._zCmp * cosA;
    point._xCmp = newX;
    point._zCmp = newZ;
}

inline void rotatePointAroundZ(Math::Point3D &point, double cosA, double sinA)
{
    const double newX = point._xCmp * cosA - point._yCmp * sinA;
    const double newY = point._xCmp * sinA + point._yCmp * cosA;
    point._xCmp = newX;
    point._yCmp = newY;
}

inline Math::Vector3D computeEdge(const Math::Point3D &from, const Math::Point3D &to)
{
    return Math::Vector3D(to._xCmp - from._xCmp,
        to._yCmp - from._yCmp,
        to._zCmp - from._zCmp);
}

inline Math::Vector3D computeCrossProduct(const Math::Vector3D &a,
    const Math::Vector3D &b)
{
    return Math::Vector3D(
        a._yCmp * b._zCmp - a._zCmp * b._yCmp,
        a._zCmp * b._xCmp - a._xCmp * b._zCmp,
        a._xCmp * b._yCmp - a._yCmp * b._xCmp);
}

inline double computeDotProduct(const Math::Vector3D &a, const Math::Vector3D &b)
{
    return a._xCmp * b._xCmp + a._yCmp * b._yCmp + a._zCmp * b._zCmp;
}

inline hitRecord buildSpherehitRecord(const RayTracer::Ray &ray, double distance,
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

inline hitRecord buildhitRecord(const RayTracer::Ray &ray, double distance,
    const Math::Vector3D &normal)
{
    hitRecord record;
    record.point = Math::Point3D(
        ray._origin._xCmp + ray._direction._xCmp * distance,
        ray._origin._yCmp + ray._direction._yCmp * distance,
        ray._origin._zCmp + ray._direction._zCmp * distance);
    record.normal = normal;
    record.t = distance;
    record.frontFace = true;
    return record;
}

inline void rotateVectorAroundX(Math::Vector3D &vector, double cosA, double sinA)
{
    const double newY = vector._yCmp * cosA - vector._zCmp * sinA;
    const double newZ = vector._yCmp * sinA + vector._zCmp * cosA;
    vector._yCmp = newY;
    vector._zCmp = newZ;
}

inline void rotateVectorAroundY(Math::Vector3D &vector, double cosA, double sinA)
{
    const double newX = vector._xCmp * cosA + vector._zCmp * sinA;
    const double newZ = -vector._xCmp * sinA + vector._zCmp * cosA;
    vector._xCmp = newX;
    vector._zCmp = newZ;
}

inline void rotateVectorAroundZ(Math::Vector3D &vector, double cosA, double sinA)
{
    const double newX = vector._xCmp * cosA - vector._yCmp * sinA;
    const double newY = vector._xCmp * sinA + vector._yCmp * cosA;
    vector._xCmp = newX;
    vector._yCmp = newY;
}

inline void applyMaterial(
    hitRecord &record,
    const RayTracer::Ray &ray,
    const std::unique_ptr<RayTracer::Interfaces::IMaterial> &material)
{
    if (!material)
        return;
    record.color = material->getColor();
    record.reflectivity = material->getReflectivity();
    if (record.reflectivity > 0.0)
        record.reflectedDirection = material->getReflectedDirection(
            ray._direction, record.normal);
}

#endif /* !PRIMITIVEUTILS_HPP_ */
