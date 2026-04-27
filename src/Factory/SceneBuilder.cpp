/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** SceneBuilder
*/

#include "SceneBuilder.hpp"
#include "PrimitiveFactory.hpp"
#include "Exception.hpp"
#include <libconfig.h++>

RayTracer::Scene SceneBuilder::build(const std::string &configFile)
{
    RayTracer::Scene scene;
    libconfig::Config cfg;

    cfg.readFile(configFile.c_str());
    const libconfig::Setting &primitives = cfg.lookup("primitives");
    // Parse spheres
    if (primitives.exists("spheres")) {
        const libconfig::Setting &spheres = primitives["spheres"];
        for (int i = 0; i < spheres.getLength(); i++) {
            auto sphere = PrimitiveFactory::createSphere(spheres[i]);
            scene.add(std::move(sphere));
        }
    }
    // Parse planes
    if (primitives.exists("planes")) {
        const libconfig::Setting &planes = primitives["planes"];
        for (int i = 0; i < planes.getLength(); i++) {
            auto plane = PrimitiveFactory::createPlane(planes[i]);
            scene.add(std::move(plane));
        }
    }
    return scene;
}
