/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Chessboard
*/


#include <cmath>
#include "Chessboard.hpp"

RayTracer::Chessboard::Chessboard(const Math::Vector3D &color1,
    const Math::Vector3D &color2, double scale)
    : _color1(color1), _color2(color2), _scale(scale)
{
}

Math::Vector3D RayTracer::Chessboard::getColor() const
{
    return _color1;
}

Math::Vector3D RayTracer::Chessboard::getColorAtPoint(const Math::Point3D &point) const
{
    int x = int(std::floor(point._xCmp / _scale));
    int y = int(std::floor(point._yCmp / _scale));

    if ((x + y) % 2 == 0)
        return _color1;
    return _color2;
}

double RayTracer::Chessboard::getReflectivity() const
{
    return 0.0;
}

Math::Vector3D RayTracer::Chessboard::getReflectedDirection(const Math::Vector3D &incident,
    const Math::Vector3D &normal) const
{
    double dotProd = incident.dot(normal);

    return incident - normal * (2.0 * dotProd);
}

bool RayTracer::Chessboard::isTransparent() const
{
    return false;
}
