/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Cylinder
*/

#ifndef CYLINDER_HPP_
#define CYLINDER_HPP_

#include "IHittable.hpp"
#include "IMaterial.hpp"
#include <memory>

// should
namespace RayTracer {
    class Cylinder : public Interfaces::IHittable {
        public:
            Cylinder(Math::Point3D center, double radius, double height, std::unique_ptr<Interfaces::IMaterial> material);
            ~Cylinder() = default;

            std::optional<hitRecord> hits(const RayTracer::Ray &ray) const override;

        private:
            std::unique_ptr<Interfaces::IMaterial> _material;
            Math::Point3D _center;
            double _radius;
            double _height;
    };
}

#endif /* !CYLINDER_HPP_ */
