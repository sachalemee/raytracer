/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Triangle
*/

#ifndef TRIANGLE_HPP_
#define TRIANGLE_HPP_

#include "IHittable.hpp"
#include "ITransformable.hpp"
#include "IMaterial.hpp"
#include <memory>
#include <optional>
#include <optional>


namespace RayTracer {
    class Triangle : public Interfaces::IHittable,
        public Interfaces::ITransformable {
    public:
        Triangle(const Math::Point3D &v0, const Math::Point3D &v1,
            const Math::Point3D &v2,
            std::unique_ptr<Interfaces::IMaterial> material = nullptr);
        ~Triangle() = default;

        std::optional<hitRecord> hits(const RayTracer::Ray &ray) const override;

        void translate(const Math::Vector3D &offset) override;
        void rotateX(double angleDegrees) override;
        void rotateY(double angleDegrees) override;
        void rotateZ(double angleDegrees) override;

    private:
        Math::Vector3D _computeNormal() const;

        Math::Point3D _v0;
        Math::Point3D _v1;
        Math::Point3D _v2;
        std::unique_ptr<Interfaces::IMaterial> _material;
    };
}

#endif /* !TRIANGLE_HPP_ */
