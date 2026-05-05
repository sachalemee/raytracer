/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** ILight
*/

#ifndef ILIGHT_HPP_
#define ILIGHT_HPP_

#include "Point3D.hpp"
#include "Vector3D.hpp"

namespace RayTracer {
    namespace Interfaces {
        class ILight {
            // MUST BE PURE INTERFACES -> virtual exempliGratia() = 0;
            public:
                virtual ~ILight() = default;

                // return intensity/color contribution of the light
                virtual Math::Vector3D getIntensity() const = 0;

                // return direction from point to light source
                // for ambient light direction is irrelevant
                virtual Math::Vector3D getDirection(const Math::Point3D &point) const = 0;

        };
    }
}

#endif /* !ILIGHT_HPP_ */
