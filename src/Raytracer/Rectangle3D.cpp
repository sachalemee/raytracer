/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Rectangle
*/

#include "Rectangle3D.hpp"
#include "Point3D.hpp"

Rectangle3D::Rectangle3D() 
    : _origin(Math::Point3D(-0.5, -0.5, -1.5)),
      _bottomSide(Math::Vector3D(1, 0, 0)),
      _leftSide(Math::Vector3D(0, 1, 0))
{
}

Math::Point3D Rectangle3D::pointAt(double u, double v)
{
    return Math::Point3D(
        _origin._xCmp + _bottomSide._xCmp * u + _leftSide._xCmp * v,
        _origin._yCmp + _bottomSide._yCmp * u + _leftSide._yCmp * v,
        _origin._zCmp + _bottomSide._zCmp * u + _leftSide._zCmp * v
    );
}
