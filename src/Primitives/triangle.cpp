/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Triangle
*/

#include <cmath>
#include <optional>
#include <utility>
#include "triangle.hpp"
#include "Vector3D.hpp"

Math::Vector3D computeEdge(const Math::Point3D &from, const Math::Point3D &to)
{
    return Math::Vector3D(to._xCmp - from._xCmp,
        to._yCmp - from._yCmp,
        to._zCmp - from._zCmp);
}

Math::Vector3D computeCrossProduct(const Math::Vector3D &a,
    const Math::Vector3D &b)
{
    return Math::Vector3D(
        a._yCmp * b._zCmp - a._zCmp * b._yCmp,
        a._zCmp * b._xCmp - a._xCmp * b._zCmp,
        a._xCmp * b._yCmp - a._yCmp * b._xCmp);
}

double computeDotProduct(const Math::Vector3D &a, const Math::Vector3D &b)
{
    return a._xCmp * b._xCmp + a._yCmp * b._yCmp + a._zCmp * b._zCmp;
}

hitRecord buildhitRecord(const RayTracer::Ray &ray, double distance,
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

RayTracer::Triangle::Triangle(const Math::Point3D &v0, const Math::Point3D &v1,
    const Math::Point3D &v2, std::unique_ptr<Interfaces::IMaterial> material)
    : _v0(v0), _v1(v1), _v2(v2), _material(std::move(material))
{
}

Math::Vector3D RayTracer::Triangle::_computeNormal() const
{
    auto normal = computeCrossProduct(computeEdge(_v0, _v1),
        computeEdge(_v0, _v2));
    const double length = normal.length();

    if (length > 0) {
        normal._xCmp /= length;
        normal._yCmp /= length;
        normal._zCmp /= length;
    }
    return normal;
}

std::optional<hitRecord> RayTracer::Triangle::hits(const RayTracer::Ray &ray) const
{
    const auto edge1 = computeEdge(_v0, _v1);
    const auto edge2 = computeEdge(_v0, _v2);
    const auto pVec = computeCrossProduct(ray._direction, edge2);
    const double determinant = computeDotProduct(edge1, pVec);

    if (std::abs(determinant) < EPSILON)
        return std::nullopt;
    const double invDet = 1.0 / determinant;
    const auto tVec = computeEdge(_v0, ray._origin);
    const double baryU = invDet * computeDotProduct(tVec, pVec);

    if (baryU < 0.0 || baryU > 1.0)
        return std::nullopt;
    const auto qVec = computeCrossProduct(tVec, edge1);
    const double baryV = invDet * computeDotProduct(ray._direction, qVec);

    if (baryV < 0.0 || baryU + baryV > 1.0)
        return std::nullopt;
    const double distance = invDet * computeDotProduct(edge2, qVec);
    if (distance <= 0)
        return std::nullopt;
    return buildhitRecord(ray, distance, _computeNormal());
}

void RayTracer::Triangle::translate(const Math::Vector3D &offset)
{
    _v0 += offset;
    _v1 += offset;
    _v2 += offset;
}

void RayTracer::Triangle::rotateX(double angleDegrees)
{
    const auto [cosA, sinA] = computeAngleTrig(angleDegrees);

    rotatePointAroundX(_v0, cosA, sinA);
    rotatePointAroundX(_v1, cosA, sinA);
    rotatePointAroundX(_v2, cosA, sinA);
}

void RayTracer::Triangle::rotateY(double angleDegrees)
{
    const auto [cosA, sinA] = computeAngleTrig(angleDegrees);

    rotatePointAroundY(_v0, cosA, sinA);
    rotatePointAroundY(_v1, cosA, sinA);
    rotatePointAroundY(_v2, cosA, sinA);
}

void RayTracer::Triangle::rotateZ(double angleDegrees)
{
    const auto [cosA, sinA] = computeAngleTrig(angleDegrees);

    rotatePointAroundZ(_v0, cosA, sinA);
    rotatePointAroundZ(_v1, cosA, sinA);
    rotatePointAroundZ(_v2, cosA, sinA);
}
