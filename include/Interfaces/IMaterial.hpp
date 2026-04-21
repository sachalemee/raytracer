/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** IMaterial
*/

#ifndef IMATERIAL_HPP_
#define IMATERIAL_HPP_

#include "RayTracer.hpp"
#include "Vector3D.hpp"
namespace RayTracer {
    namespace Interfaces {
        class IMaterial {
            // MUST BE PURE INTERFACES -> virtual exempliGratia() = 0;
            public:
                virtual ~IMaterial() = default;
                virtual Math::Vector3D color(const hitRecord &hit) const = 0; 
            
            protected:
            private:
        };
    }
}

#endif /* !IMATERIAL_HPP_ */
