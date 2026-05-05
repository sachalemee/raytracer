/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Ray
*/

#include "Ray.hpp"
#include "Point3D.hpp"
#include "Vector3D.hpp"

RayTracer::Ray::Ray() : _origin(), _direction()
{
}

RayTracer::Ray::Ray(const Math::Point3D &origin, const Math::Vector3D &direction) : _origin(origin), _direction(direction)
{
}
