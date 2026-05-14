/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** IMaterial
*/

#include "IMaterial.hpp"

Math::Vector3D RayTracer::Interfaces::IMaterial::getReflectedDirection(
    const Math::Vector3D &incident, const Math::Vector3D &normal) const
{
    double dot = incident.dot(normal);
    return Math::Vector3D(incident._xCmp - 2.0 * dot * normal._xCmp,
        incident._yCmp - 2.0 * dot * normal._yCmp,
        incident._zCmp - 2.0 * dot * normal._zCmp);
}
