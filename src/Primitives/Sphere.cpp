/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Sphere
*/

#include "Sphere.hpp"
#include "Template.hpp"
#include "Vector3D.hpp"

RayTracer::Sphere::Sphere(Math::Point3D center, double radius) : _sphCenter(center), _sphRadius(radius)
{
}

bool RayTracer::Sphere::hits(RayTracer::Ray ray)
{
    Math::Vector3D oc(
        ray._origin._xCmp - _sphCenter._xCmp,
        ray._origin._yCmp - _sphCenter._yCmp,
        ray._origin._zCmp - _sphCenter._zCmp
    );
    double a = ray._direction.dot(ray._direction);
    double b = 2.0 * oc.dot(ray._direction);
    double c = oc.dot(oc) - (square(_sphRadius));
    double discriminant = square(b) - 4 * a * c;  
    return discriminant >= 0;
}

