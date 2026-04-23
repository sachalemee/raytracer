/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Sphere
*/

#ifndef SPHERE_HPP_
#define SPHERE_HPP_

#include "IHittable.hpp"

// must
namespace RayTracer {
    class Sphere : public Interfaces::IHittable {
        public:
            Sphere(Math::Point3D center, double radius);
            ~Sphere() = default;

            std::optional<hitRecord> hits(const RayTracer::Ray &ray) const override;

        private:
            Math::Point3D _sphCenter;
            double _sphRadius;
    };
}

#endif /* !SPHERE_HPP_ */
