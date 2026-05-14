/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Chessboard
*/

#ifndef CHESSBOARD_HPP_
    #define CHESSBOARD_HPP_

    #include "IMaterial.hpp"

namespace RayTracer {
    class Chessboard : public Interfaces::IMaterial {
        public:
            Chessboard(const Math::Vector3D &color1, const Math::Vector3D &color2,
                double scale = 1.0);
            ~Chessboard() = default;

            Math::Vector3D getColor() const override;
            Math::Vector3D getColorAtPoint(const Math::Point3D &point) const override;
            double getReflectivity() const override;
            Math::Vector3D getReflectedDirection(const Math::Vector3D &incident,
                const Math::Vector3D &normal) const override;

        private:
            Math::Vector3D _color1;
            Math::Vector3D _color2;
            double _scale;
    };
}

#endif /* !CHESSBOARD_HPP_ */
