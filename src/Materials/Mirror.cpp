/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Mirror
*/

#include "Mirror.hpp"

RayTracer::Mirror::Mirror(const Math::Vector3D &tint, double reflectivity)
    : _tint(tint), _reflectivity(reflectivity)
{
}

Math::Vector3D RayTracer::Mirror::getColor() const
{
    return _tint;
}

Math::Vector3D RayTracer::Mirror::getColorAtPoint(const Math::Point3D &point) const
{
    (void)point;
    return getColor();
}

double RayTracer::Mirror::getReflectivity() const
{
    return _reflectivity;
}

Math::Vector3D RayTracer::Mirror::getReflectedDirection(const Math::Vector3D &incident,
    const Math::Vector3D &normal) const
{
    double dotProd = incident.dot(normal);

    return incident - normal * (2.0 * dotProd);
}
