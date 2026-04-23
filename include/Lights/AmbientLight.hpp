/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** AmbientLight
*/

#ifndef AMBIENTLIGHT_HPP_
#define AMBIENTLIGHT_HPP_

#include "ILight.hpp"

namespace RayTracer {
    class AmbientLight : public Interfaces::ILight {
        public:
            AmbientLight(Math::Vector3D intensity);
            ~AmbientLight() = default;

            /// return intensity of the ambient light
            Math::Vector3D getIntensity() const override;
            
            /// ambient light has no direction (returns zero vector)
            Math::Vector3D getDirection(const Math::Point3D &point) const override;

        private:
            Math::Vector3D _intensity;
    };
}

#endif /* !AMBIENTLIGHT_HPP_ */
