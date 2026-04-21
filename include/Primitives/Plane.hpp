/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Plane
*/

#ifndef PLANE_HPP_
#define PLANE_HPP_

#include "IHittable.hpp"

// must
namespace RayTracer {
    class Plane : public Interfaces::IHittable {
        public:
            Plane();
            ~Plane() = default;

            std::optional<hitRecord> hits(const RayTracer::Ray &ray) const override;

        private:
    };
}

#endif /* !PLANE_HPP_ */
