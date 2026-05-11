/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Sphere
*/

#ifndef SPHERE_HPP_
#define SPHERE_HPP_

#include <memory>
#include <optional>
#include "IHittable.hpp"
#include "IMaterial.hpp"
#include "ITransformable.hpp"

// must
namespace RayTracer {
    class Sphere : public Interfaces::IHittable,
                    public Interfaces::ITransformable {
    public:
        Sphere(const Math::Point3D &center, double radius,
            std::unique_ptr<Interfaces::IMaterial> material = nullptr);
        ~Sphere() = default;
        std::optional<hitRecord> hits(const RayTracer::Ray &ray) const override;
        void translate(const Math::Vector3D &offset) override;
        void rotateX(double angleDegrees) override;
        void rotateY(double angleDegrees) override;
        void rotateZ(double angleDegrees) override;

    private:
        Math::Point3D _sphCenter;
        double _sphRadius;
        std::unique_ptr<Interfaces::IMaterial> _material;
    };
}

#endif /* !SPHERE_HPP_ */
