/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Point3D
*/

#include "Point3D.hpp"

Math::Point3D::Point3D() : _xCmp(0), _yCmp(0), _zCmp(0)
{
}

Math::Point3D::Point3D(double xCmp, double yCmp, double zCmp) : _xCmp(xCmp), _yCmp(yCmp), _zCmp(zCmp)
{
}

Math::Point3D Math::Point3D::operator+(const Math::Vector3D &vec) const
{
    Math::Point3D result = *this;

    result += vec;
    return result;
}

Math::Point3D &Math::Point3D::operator+=(const Math::Vector3D &vec)
{
    _xCmp += vec._xCmp;
    _yCmp += vec._yCmp;
    _zCmp += vec._zCmp;
    return *this;
}

Math::Point3D Math::Point3D::operator-(const Math::Vector3D &vec) const
{
    Math::Point3D result = *this;

    result -= vec;
    return result;
}

Math::Point3D &Math::Point3D::operator-=(const Math::Vector3D &vec)
{
    _xCmp -= vec._xCmp;
    _yCmp -= vec._yCmp;
    _zCmp -= vec._zCmp;
    return *this;
}

Math::Vector3D Math::Point3D::operator-(const Math::Point3D &other) const
{
    return Vector3D(_xCmp - other._xCmp, _yCmp - other._yCmp, _zCmp - other._zCmp);
}
