/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Camera
*/

#include "Camera.hpp"
#include "Point3D.hpp"
#include "Ray.hpp"
#include "Vector3D.hpp"

RayTracer::Camera::Camera() : _origin(0, 0, 0)
{
}

RayTracer::Ray RayTracer::Camera::ray(double x, double y) const
{
    Math::Point3D pixel = _screen.pointAt(x, y);
    Math::Vector3D direction(
        pixel._xCmp - _origin._xCmp,
        pixel._yCmp - _origin._yCmp,
        pixel._zCmp - _origin._zCmp
    );
    return RayTracer::Ray(_origin, direction);
}
