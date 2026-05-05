/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** IHittable
*/

#ifndef IHITTABLE_HPP_
#define IHITTABLE_HPP_

#include <optional>
#include "Ray.hpp"
#include "RayTracer.hpp"

namespace RayTracer {
    namespace Interfaces {    
        class IHittable {
            // MUST BE PURE INTERFACES -> virtual exempliGratia() = 0;
            public:
                virtual ~IHittable() = default;
                virtual std::optional<hitRecord> hits(const RayTracer::Ray &ray) const = 0;

        };
    }
}

#endif /* !IHITTABLE_HPP_ */
