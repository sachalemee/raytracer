/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Cylinder
*/

#ifndef CYLINDER_HPP_
#define CYLINDER_HPP_

#include "IHittable.hpp"
#include "ITransformable.hpp"
#include "IMaterial.hpp"
#include <memory>
#include <optional>


namespace RayTracer {
    class Cylinder : public Interfaces::IHittable, public Interfaces::ITransformable {
    public:
        Cylinder(const Math::Point3D &center, double radius, double height,
            std::unique_ptr<Interfaces::IMaterial> material = nullptr);
        ~Cylinder() = default;

        std::optional<hitRecord> hits(const RayTracer::Ray &ray) const override;

        void translate(const Math::Vector3D &offset) override;
        void rotateX(double angleDegrees) override;
        void rotateY(double angleDegrees) override;
        void rotateZ(double angleDegrees) override;

    private:
        std::optional<hitRecord> _intersectBody(const RayTracer::Ray &ray) const;
        std::optional<hitRecord> _intersectCap(const RayTracer::Ray &ray,
            const Math::Point3D &capCenter, const Math::Vector3D &capNormal) const;
        std::optional<hitRecord> _buildBodyHit(const RayTracer::Ray &ray,
            const Math::Point3D &hitPoint, double t) const;

        Math::Point3D _center;
        Math::Vector3D _axis;
        double _radius;
        double _height;
        std::unique_ptr<Interfaces::IMaterial> _material;
    };
}

#endif /* !CYLINDER_HPP_ */