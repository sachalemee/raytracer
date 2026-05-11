/*
** EPITECH PROJECT, 2026
** G-OOP-400-PAR-4-1-raytracer-29
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
