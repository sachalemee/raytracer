/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Transparency
*/

#include <cmath>
#include "Transparency.hpp"

RayTracer::Transparency::Transparency(double refractiveIndex, double transparency)
    : _refractiveIndex(refractiveIndex), _transparency(transparency)
{
}

Math::Vector3D RayTracer::Transparency::getColor() const
{
    return Math::Vector3D(0.0, 0.0, 0.0);
}

Math::Vector3D RayTracer::Transparency::getColorAtPoint(const Math::Point3D &point) const
{
    (void)point;
    return getColor();
}

double RayTracer::Transparency::getReflectivity() const
{
    return 1.0;
}

Math::Vector3D RayTracer::Transparency::getReflectedDirection(const Math::Vector3D &incident,
    const Math::Vector3D &normal) const
{
    double n1 = 1.0;
    double n2 = _refractiveIndex;
    double ratio = n1 / n2;
    double cosI = -incident.dot(normal);
    double cosT2 = 1.0 - ratio * ratio * (1.0 - cosI * cosI);
    Math::Vector3D refracted;

    if (cosT2 < 0.0)
        return incident - normal * (2.0 * incident.dot(normal));
    cosT2 = std::sqrt(cosT2);
    refracted = (incident * ratio) + (normal * (ratio * cosI - cosT2));
    return refracted;
}

bool RayTracer::Transparency::isTransparent() const
{
    return true;
}
