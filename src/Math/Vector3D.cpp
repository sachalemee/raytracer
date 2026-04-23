/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Vector3D
*/

#include "Vector3D.hpp"
#include <cmath>

Math::Vector3D::Vector3D() : _xCmp(0), _yCmp(0), _zCmp(0)
{
}

Math::Vector3D::Vector3D(double xCmp, double yCmp, double zCmp) : _xCmp(xCmp), _yCmp(yCmp), _zCmp(zCmp)
{
}

double Math::Vector3D::length() const
{
    return std::sqrt((_xCmp * _xCmp) + (_yCmp * _yCmp) + (_zCmp * _zCmp));
}

double Math::Vector3D::dot(const Vector3D &other) const
{
    return (_xCmp * other._xCmp + _yCmp * other._yCmp + _zCmp * other._zCmp);
}

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
