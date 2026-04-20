/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** point3dOperator
*/

#include "Point3D.hpp"
#include "Vector3D.hpp"

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
