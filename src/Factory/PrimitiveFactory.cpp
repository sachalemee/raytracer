/*
** EPITECH PROJECT, 2026
** G-OOP-400-PAR-4-1-raytracer-29
** File description:
** PrimitiveFactory
*/

#include "PrimitiveFactory.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"
#include "Cylinder.hpp"
#include "Cone.hpp"
#include "Point3D.hpp"
#include "Vector3D.hpp"
#include <libconfig.h++>
#include <memory>

std::unique_ptr<Interfaces::IHittable> PrimitiveFactory::createSphere(const libconfig::Setting &setting)
{
    double x = setting["x"];0.
    double y = setting["y"];
    double z = setting["z"];
    double radius = setting["r"];
    
    return std::make_unique<RayTracer::Sphere>(Math::Point3D(x, y, z), radius);
}

std::unique_ptr<Interfaces::IHittable> PrimitiveFactory::createPlane(const libconfig::Setting &setting)
{
    return nullptr;
}

std::unique_ptr<Interfaces::IHittable> PrimitiveFactory::createCylinder(const libconfig::Setting &setting)
{
    return nullptr;
}

std::unique_ptr<Interfaces::IHittable> PrimitiveFactory::createCone(const libconfig::Setting &setting)
{
    return nullptr;
}