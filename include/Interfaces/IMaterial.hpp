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
            public:
                virtual ~IMaterial() = default;

                /// Returns the color/albedo of the material
                virtual Math::Vector3D getColor() const = 0;
            
            protected:
            private:
        };
    }
}

#endif /* !IMATERIAL_HPP_ */
