/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** DirectionalLight
*/

#ifndef DIRECTIONALLIGHT_HPP_
#define DIRECTIONALLIGHT_HPP_

#include "ILight.hpp"

namespace RayTracer {
    class DirectionalLight : public Interfaces::ILight {
        public:
            DirectionalLight(Math::Vector3D direction, Math::Vector3D intensity);
            ~DirectionalLight() = default;

            /// return intensity directional light
            Math::Vector3D getIntensity() const override;
            
            /// return direction from point to the light source
            /// directional light = same everywhere (parallel rays)
            Math::Vector3D getDirection(const Math::Point3D &point) const override;

        private:
            Math::Vector3D _direction;
            Math::Vector3D _intensity;
    };
}

#endif /* !DIRECTIONALLIGHT_HPP_ */
