/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** ITransformable
*/

#ifndef ITRANSFORMABLE_HPP_
#define ITRANSFORMABLE_HPP_

#include "Vector3D.hpp"

namespace RayTracer {
    namespace Interfaces {
        class ITransformable {
            // MUST BE PURE INTERFACES -> virtual exempliGratia() = 0;
            public:
                virtual ~ITransformable() = default;

                /// translate object by given vector (must)
                virtual void translate(const Math::Vector3D &offset) = 0;
                /// rotate around X axis in degrees (should)
                virtual void rotateX(double angleDegrees) = 0;
                /// rotate around Y axis in degrees (should)
                virtual void rotateY(double angleDegrees) = 0;
                /// rotate around Z axis in degrees (should)
                virtual void rotateZ(double angleDegrees) = 0;

        };
    }
}

#endif /* !ITRANSFORMABLE_HPP_ */
