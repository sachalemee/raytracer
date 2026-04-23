/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Vector3D
*/

#ifndef VECTOR3D_HPP_
#define VECTOR3D_HPP_

namespace Math {
    class Vector3D {
        public:
            Vector3D();
            Vector3D(double, double, double);
            ~Vector3D() = default;
    
            double length() const;
            double dot(const Vector3D &other) const;
    
            Vector3D operator+(const Math::Vector3D &other) const;
            Vector3D &operator+=(const Math::Vector3D &other);
    
            Vector3D operator-(const Math::Vector3D &other) const;
            Vector3D &operator-=(const Math::Vector3D &other);
    
    
            Vector3D operator*(double scalar) const;
            Vector3D &operator*=(double scalar);
    
            Vector3D operator*(const Vector3D &other) const;
            Vector3D &operator*=(const Vector3D &other);
    
            Vector3D operator/(const Vector3D &other) const;
            Vector3D &operator/=(const Vector3D &other);
    
            Vector3D operator/(double scalar) const;
            Vector3D &operator/=(double scalar);
    
            double _xCmp;
            double _yCmp;
            double _zCmp;
    
        protected:
        private:
    
    };
}

#endif /* !VECTOR3D_HPP_ */
