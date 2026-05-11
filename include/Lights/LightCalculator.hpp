/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** LightCalculator
*/

#ifndef LIGHTCALCULATOR_HPP_
#define LIGHTCALCULATOR_HPP_

#include <vector>
#include <memory>
#include "RayTracer.hpp"
#include "ILight.hpp"
#include "IHittable.hpp"
#include "Vector3D.hpp"

namespace RayTracer {
    class LightCalculator {
        public:
            /// Compute the lit color at a hit point given all lights and primitives.
            /// Handles ambient and directional (Lambert diffuse) lights, with drop shadows.
            static Math::Vector3D compute(
                const hitRecord &record,
                const std::vector<std::unique_ptr<Interfaces::ILight>> &lights,
                const std::vector<std::unique_ptr<Interfaces::IHittable>> &primitives);

        private:
            LightCalculator() = delete;

            static Math::Vector3D componentMultiply(
                const Math::Vector3D &a, const Math::Vector3D &b);

            static bool isInShadow(
                const Math::Point3D &hitPoint,
                const Math::Vector3D &toLightDir,
                const std::vector<std::unique_ptr<Interfaces::IHittable>> &primitives);
    };
}

#endif /* !LIGHTCALCULATOR_HPP_ */
