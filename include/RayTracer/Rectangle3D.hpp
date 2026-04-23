/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Rectangle3D
*/

#ifndef RECTANGLE3D_HPP_
#define RECTANGLE3D_HPP_

#include "Point3D.hpp"
#include "Vector3D.hpp"

class Rectangle3D {
    public:
        Rectangle3D();
        ~Rectangle3D() = default;

        Math::Point3D pointAt(double u, double v);

        Math::Point3D _origin;
        Math::Vector3D _bottomSide;
        Math::Vector3D _leftSide;

    protected:
    private:
};

#endif /* !RECTANGLE3D_HPP_ */
