/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Cylinder
*/

#ifndef CYLINDER_HPP_
#define CYLINDER_HPP_

#include "IHittable.hpp"

// should
namespace RayTracer {
    class Cylinder : public Interfaces::IHittable {
        public:
            Cylinder();
            ~Cylinder() = default;

            std::optional<hitRecord> hits(const RayTracer::Ray &ray) const override;

        private:
    };
}

#endif /* !CYLINDER_HPP_ */
