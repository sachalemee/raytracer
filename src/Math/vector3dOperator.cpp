/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** vector3dOperator
*/

#include "Vector3D.hpp"

Math::Vector3D Math::Vector3D::operator+(const Math::Vector3D &other) const
{
    Math::Vector3D result = *this;

    result += other;
    return result;
}

Math::Vector3D &Math::Vector3D::operator+=(const Math::Vector3D &other)
{
    _xCmp += other._xCmp;
    _yCmp += other._yCmp;
    _zCmp += other._zCmp;
    return *this;
}

Math::Vector3D Math::Vector3D::operator-(const Math::Vector3D &other) const
{
    Math::Vector3D result = *this;

    result -= other;
    return result;
}

Math::Vector3D &Math::Vector3D::operator-=(const Math::Vector3D &other)
{
    _xCmp -= other._xCmp;
    _yCmp -= other._yCmp;
    _zCmp -= other._zCmp;
    return *this;
}

Math::Vector3D Math::Vector3D::operator*(double scalar) const
{
    return Math::Vector3D(_xCmp * scalar, _yCmp * scalar, _zCmp * scalar);
}

Math::Vector3D &Math::Vector3D::operator*=(double scalar)
{
    _xCmp *= scalar;
    _yCmp *= scalar;
    _zCmp *= scalar;
    return *this;
}

Math::Vector3D Math::Vector3D::operator*(const Math::Vector3D &other) const
{
    return Math::Vector3D(_xCmp * other._xCmp, _yCmp * other._yCmp, _zCmp * other._zCmp);
}

Math::Vector3D &Math::Vector3D::operator*=(const Math::Vector3D &other)
{
    _xCmp *= other._xCmp;
    _yCmp *= other._yCmp;
    _zCmp *= other._zCmp;
    return *this;
}

Math::Vector3D Math::Vector3D::operator/(const Math::Vector3D &other) const
{
    return Math::Vector3D(_xCmp / other._xCmp, _yCmp / other._yCmp, _zCmp / other._zCmp);
}

Math::Vector3D &Math::Vector3D::operator/=(const Math::Vector3D &other)
{
    _xCmp /= other._xCmp;
    _yCmp /= other._yCmp;
    _zCmp /= other._zCmp;
    return *this;
}

Math::Vector3D Math::Vector3D::operator/(double scalar) const
{
    return Math::Vector3D(_xCmp / scalar, _yCmp / scalar, _zCmp / scalar);
}

Math::Vector3D &Math::Vector3D::operator/=(double scalar)
{
    _xCmp /= scalar;
    _yCmp /= scalar;
    _zCmp /= scalar;
    return *this;
}
