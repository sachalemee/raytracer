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
            double getReflectivity() const override;

        private:
            Math::Vector3D _tint;
            double _reflectivity;
    };
}

#endif /* !MIRROR_HPP_ */
