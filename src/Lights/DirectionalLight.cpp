/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** DirectionalLight implementation
*/

#include "DirectionalLight.hpp"

namespace RayTracer {

DirectionalLight::DirectionalLight(Math::Vector3D direction, Math::Vector3D intensity) : _direction(direction), _intensity(intensity)
{
}

Math::Vector3D DirectionalLight::getIntensity() const
{
    return _intensity;
}

Math::Vector3D DirectionalLight::getDirection(const Math::Point3D &point) const
{
    (void)point;
    return _direction;
}

}
