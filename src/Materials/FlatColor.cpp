/*
** EPITECH PROJECT, 2026
** raytracer
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
