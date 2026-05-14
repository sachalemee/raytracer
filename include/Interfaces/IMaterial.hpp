/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** IMaterial
*/

#ifndef IMATERIAL_HPP_
#define IMATERIAL_HPP_

#include "Vector3D.hpp"
#include "Point3D.hpp"

namespace RayTracer {
    namespace Interfaces {
        class IMaterial {
            // MUST BE PURE INTERFACES -> virtual exempliGratia() = 0;
            public:
                virtual ~IMaterial() = default;
                /// return color/albedo of material
                virtual Math::Vector3D getColor() const = 0;
                /// return color of material at a specific point
                virtual Math::Vector3D getColorAtPoint(const Math::Point3D &point) const = 0;
                /// return reflectivity of material
                virtual double getReflectivity() const = 0;
                /// return reflected ray direction given incident ray and surface normal
                virtual Math::Vector3D getReflectedDirection(const Math::Vector3D &incident, const Math::Vector3D &normal) const = 0;
        };
    }
}

#endif /* !IMATERIAL_HPP_ */
