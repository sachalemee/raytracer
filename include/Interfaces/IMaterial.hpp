/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** IMaterial
*/

#ifndef IMATERIAL_HPP_
#define IMATERIAL_HPP_

#include "Vector3D.hpp"

namespace RayTracer {
    namespace Interfaces {
        class IMaterial {
            // MUST BE PURE INTERFACES -> virtual exempliGratia() = 0;
            public:
                virtual ~IMaterial() = default;
                /// Returns the color/albedo of the material
                virtual Math::Vector3D getColor() const = 0;
                /// Returns reflectivity in [0, 1] (0 = matte, 1 = perfect mirror)
                virtual double getReflectivity() const = 0;
                /// Returns the reflected ray direction given incident ray and surface normal
                virtual Math::Vector3D getReflectedDirection(
                    const Math::Vector3D &incident,
                    const Math::Vector3D &normal) const;

        };
    }
}

#endif /* !IMATERIAL_HPP_ */
