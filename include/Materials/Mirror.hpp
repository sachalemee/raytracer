/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Mirror
*/

#ifndef MIRROR_HPP_
#define MIRROR_HPP_

#include "IMaterial.hpp"

namespace RayTracer {
    class Mirror : public Interfaces::IMaterial {
        public:
            Mirror(const Math::Vector3D &tint, double reflectivity = 1.0);
            ~Mirror() = default;

            Math::Vector3D getColor() const override;
            Math::Vector3D getColorAtPoint(const Math::Point3D &point) const override;
            double getReflectivity() const override;
            Math::Vector3D getReflectedDirection(const Math::Vector3D &incident,
                const Math::Vector3D &normal) const override;

        private:
            Math::Vector3D _tint;
            double _reflectivity;
    };
}

#endif /* !MIRROR_HPP_ */
