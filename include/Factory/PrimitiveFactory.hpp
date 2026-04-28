/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** PrimitiveFactory
*/

#ifndef PRIMITIVEFACTORY_HPP_
#define PRIMITIVEFACTORY_HPP_

#include <memory>
#include <libconfig.h++>
#include "IHittable.hpp"

// "Additionally, you must use at least 2 design patterns [..] ":
// Factory
class PrimitiveFactory {
    public:
        static std::unique_ptr<RayTracer::Interfaces::IHittable> createSphere(const libconfig::Setting &setting);
        static std::unique_ptr<RayTracer::Interfaces::IHittable> createPlane(const libconfig::Setting &setting);
        static std::unique_ptr<RayTracer::Interfaces::IHittable> createCylinder(const libconfig::Setting &setting);
        static std::unique_ptr<RayTracer::Interfaces::IHittable> createCone(const libconfig::Setting &setting);

    private:
        PrimitiveFactory() = delete;
};

#endif /* !PRIMITIVEFACTORY_HPP_ */
