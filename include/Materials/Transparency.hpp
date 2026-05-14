/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Transparency - Transparent material with refraction
*/

#ifndef TRANSPARENCY_HPP_
    #define TRANSPARENCY_HPP_

    #include "IMaterial.hpp"

namespace RayTracer {
    class Transparency : public Interfaces::IMaterial {
        public:
            Transparency();
            ~Transparency() = default;

            Math::Vector3D getColor() const override;
            Math::Vector3D getColorAtPoint(const Math::Point3D &point) const override;
            double getReflectivity() const override;
            Math::Vector3D getReflectedDirection(const Math::Vector3D &incident,
                const Math::Vector3D &normal) const override;
            bool isTransparent() const override;

        private:
    };
}

#endif /* !TRANSPARENCY_HPP_ */
