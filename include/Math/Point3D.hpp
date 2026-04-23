/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Point3D
*/

#ifndef POINT3D_HPP_
#define POINT3D_HPP_

#include "Vector3D.hpp"

namespace Math {
    class Point3D {
        public:
            Point3D();
            Point3D(double, double, double);
            ~Point3D() = default;
    
            Point3D operator+(const Vector3D &vec) const;
            Point3D &operator+=(const Vector3D &vec);
    
            Point3D operator-(const Vector3D &vec) const;
            Point3D &operator-=(const Vector3D &vec);
    
            Vector3D operator-(const Point3D &other) const;
    
            double _xCmp;
            double _yCmp;
            double _zCmp;
    
        protected:
        private:
    
    };
}

#endif /* !POINT3D_HPP_ */
