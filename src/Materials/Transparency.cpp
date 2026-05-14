/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Transparency
*/

#include <cmath>
#include "Transparency.hpp"

RayTracer::Transparency::Transparency()
{
}

Math::Vector3D RayTracer::Transparency::getColor() const
{
    return Math::Vector3D(1.0, 1.0, 1.0);
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
    (void)normal;
    return incident;
}

bool RayTracer::Transparency::isTransparent() const
{
    return true;
}
