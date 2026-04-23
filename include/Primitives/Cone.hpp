/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Cone
*/

#ifndef CONE_HPP_
#define CONE_HPP_

#include "IHittable.hpp"
#include "IMaterial.hpp"
#include <memory>

// should
namespace RayTracer {
    class Cone : public Interfaces::IHittable {
        public:
            Cone(Math::Point3D apex, double radius, double height, std::unique_ptr<Interfaces::IMaterial> material);
            ~Cone() = default;

            std::optional<hitRecord> hits(const RayTracer::Ray &ray) const override;

        private:
            std::unique_ptr<Interfaces::IMaterial> _material;
            Math::Point3D _apex;
            double _radius;
            double _height;
    };
}

#endif /* !CONE_HPP_ */
