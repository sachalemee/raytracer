/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Ray
*/

#ifndef RAY_HPP_
#define RAY_HPP_

#include "Point3D.hpp"
#include "Vector3D.hpp"

namespace RayTracer {
    class Ray {
        public:
            Ray();
            Ray(const Math::Point3D &origin, const Math::Vector3D &direction);
            ~Ray() = default;

            Math::Point3D at(double t) const;

            Math::Point3D _origin;
            Math::Vector3D _direction;
        
        protected:
        private:
    };
}

#endif /* !RAY_HPP_ */
