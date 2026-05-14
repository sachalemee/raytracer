/*
** EPITECH PROJECT, 2026
** G-OOP-400-PAR-4-1-raytracer-29
** File description:
** FlatColor
*/

#ifndef FLATCOLOR_HPP_
#define FLATCOLOR_HPP_

#include "IMaterial.hpp"

namespace RayTracer {
    class FlatColor : public Interfaces::IMaterial {
        public:
            FlatColor(const Math::Vector3D &color);
            ~FlatColor() = default;

            Math::Vector3D getColor() const override;
            Math::Vector3D getColorAtPoint(const Math::Point3D &point) const override;
            double getReflectivity() const override;
            Math::Vector3D getReflectedDirection(const Math::Vector3D &incident,
                const Math::Vector3D &normal) const override;
            bool isTransparent() const override;

        private:
            Math::Vector3D _color;
    };
}

#endif /* !FLATCOLOR_HPP_ */
