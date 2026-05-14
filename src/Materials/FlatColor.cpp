/*
** EPITECH PROJECT, 2026
** G-OOP-400-PAR-4-1-raytracer-29
** File description:
** FlatColor
*/

#include "FlatColor.hpp"

RayTracer::FlatColor::FlatColor(const Math::Vector3D &color)
    : _color(color)
{
}

Math::Vector3D RayTracer::FlatColor::getColor() const
{
    return _color;
}

Math::Vector3D RayTracer::FlatColor::getColorAtPoint(const Math::Point3D &point) const
{
    (void)point;
    return getColor();
}

double RayTracer::FlatColor::getReflectivity() const
{
    return 0.0;
}

Math::Vector3D RayTracer::FlatColor::getReflectedDirection(const Math::Vector3D &incident,
    const Math::Vector3D &normal) const
{
    double dotProd = incident.dot(normal);

    return incident - normal * (2.0 * dotProd);
}

bool RayTracer::FlatColor::isTransparent() const
{
    return false;
}
