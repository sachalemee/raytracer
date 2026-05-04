/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** AmbientLight implementation
*/

#include "AmbientLight.hpp"

namespace RayTracer {

AmbientLight::AmbientLight(Math::Vector3D intensity) : _intensity(intensity)
{
}

Math::Vector3D AmbientLight::getIntensity() const
{
    return _intensity;
}

Math::Vector3D AmbientLight::getDirection(const Math::Point3D &point) const
{
    (void)point;
    return Math::Vector3D(0, 0, 0);
}

}
