/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Plane
*/

#ifndef PLANE_HPP_
#define PLANE_HPP_


#include "IHittable.hpp"
#include "ITransformable.hpp"
#include "IMaterial.hpp"
#include <memory>
#include <optional>

namespace RayTracer {
    class Plane : public Interfaces::IHittable,
                    public Interfaces::ITransformable {
    public:
        Plane(const Math::Point3D &position, const Math::Vector3D &normal,
            std::unique_ptr<Interfaces::IMaterial> material = nullptr);
        ~Plane() = default;

        std::optional<hitRecord> hits(const RayTracer::Ray &ray) const override;

        void translate(const Math::Vector3D &offset) override;
        void rotateX(double angleDegrees) override;
        void rotateY(double angleDegrees) override;
        void rotateZ(double angleDegrees) override;

    private:
        void _normalizeNormal();

        Math::Point3D _position;
        Math::Vector3D _normal;
        std::unique_ptr<Interfaces::IMaterial> _material;
    };
}

#endif /* !PLANE_HPP_ */
