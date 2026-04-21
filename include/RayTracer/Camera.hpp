/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Camera
*/

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include "Point3D.hpp"
#include "Ray.hpp"
#include "Rectangle3D.hpp"

namespace RayTracer {

    class Camera {
        public:
            Camera();
            ~Camera() = default;
            
            Ray ray(double u, double v);

            Math::Point3D _origin;
            Rectangle3D _screen;

        protected:
        private:
    };
}

#endif /* !CAMERA_HPP_ */
