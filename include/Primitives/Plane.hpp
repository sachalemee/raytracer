/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Plane
*/

#ifndef PLANE_HPP_
#define PLANE_HPP_

#include "IHittable.hpp"
#include "IMaterial.hpp"
#include <memory>

// must
namespace RayTracer {
    class Plane : public Interfaces::IHittable {
        public:
            Plane(Math::Vector3D normal, double distance, std::unique_ptr<Interfaces::IMaterial> material);
            ~Plane() = default;

            std::optional<hitRecord> hits(const RayTracer::Ray &ray) const override;

        private:
            std::unique_ptr<Interfaces::IMaterial> _material;
            Math::Vector3D _normal;
            double _distance;
    };
}

#endif /* !PLANE_HPP_ */
