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

double RayTracer::Mirror::getReflectivity() const
{
    return _reflectivity;
}
