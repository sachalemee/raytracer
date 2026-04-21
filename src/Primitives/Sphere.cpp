/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Sphere
*/

#include "Sphere.hpp"
#include "RayTracer.hpp"
#include "Template.hpp"
#include "Vector3D.hpp"
#include <optional>

RayTracer::Sphere::Sphere(Math::Point3D center, double radius) : _sphCenter(center), _sphRadius(radius)
{
}

std::optional<hitRecord> RayTracer::Sphere::hits(const RayTracer::Ray &ray) const
{
    Math::Vector3D oc(
        ray._origin._xCmp - _sphCenter._xCmp,
        ray._origin._yCmp - _sphCenter._yCmp,
        ray._origin._zCmp - _sphCenter._zCmp
    );
    double a = ray._direction.dot(ray._direction);
    double b = 2.0 * oc.dot(ray._direction);
    double c = oc.dot(oc) - (square(_sphRadius));
    double discriminant = discriminantEquation(b, a, c);
    if (discriminant < 0)
        return std::optional<hitRecord>();
    return hitRecord{{}, {}, 0, {}, discriminant >= 0};
}
