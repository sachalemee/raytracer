/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Cone
*/

#ifndef CONE_HPP_
#define CONE_HPP_

#include "IHittable.hpp"
#include "ITransformable.hpp"
#include "IMaterial.hpp"
#include <memory>
#include <optional>

namespace RayTracer {
    class Cone : public Interfaces::IHittable,
                public Interfaces::ITransformable {
    public:
        Cone(const Math::Point3D &apex, double height, double baseRadius,
            std::unique_ptr<Interfaces::IMaterial> material = nullptr);
        ~Cone() = default;

        std::optional<hitRecord> hits(const RayTracer::Ray &ray) const override;

        void translate(const Math::Vector3D &offset) override;
        void rotateX(double angleDegrees) override;
        void rotateY(double angleDegrees) override;
        void rotateZ(double angleDegrees) override;

    private:
        std::optional<hitRecord> _intersectSurface(const RayTracer::Ray &ray) const;
        std::optional<hitRecord> _intersectBase(const RayTracer::Ray &ray) const;
        std::optional<hitRecord> _buildSurfaceHit(const RayTracer::Ray &ray,
            const Math::Point3D &hitPoint, double t) const;

        Math::Point3D _apex;
        Math::Vector3D _axis;
        double _height;
        double _baseRadius;
        std::unique_ptr<Interfaces::IMaterial> _material;
    };
}

#endif /* !CONE_HPP_ */
