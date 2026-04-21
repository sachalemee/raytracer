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
            Ray(Math::Point3D &origin, Math::Vector3D &direction);
            ~Ray() = default;

            Math::Point3D _origin;
            Math::Vector3D _direction;
        
        protected:
        private:
    };
}

#endif /* !RAY_HPP_ */
