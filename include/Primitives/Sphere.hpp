/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Sphere
*/

#ifndef SPHERE_HPP_
#define SPHERE_HPP_

#include "IHittable.hpp"
#include "Point3D.hpp"
#include "Ray.hpp"

namespace RayTracer {

    class Sphere : public Interfaces::IHittable {
        public:
            Sphere(Math::Point3D center, double radius);
            ~Sphere() = default;

        bool hits(RayTracer::Ray ray);

        Math::Point3D _sphCenter;
        double _sphRadius;

        protected:
        private:
    };
}

#endif /* !SPHERE_HPP_ */
