/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** SceneBuilder
*/

#include <libconfig.h++>
#include <cmath>
#include "SceneBuilder.hpp"
#include "Camera.hpp"
#include "Point3D.hpp"
#include "PrimitiveFactory.hpp"
#include "Scene.hpp"

RayTracer::Camera SceneBuilder::parseCamera(const libconfig::Setting &cameraSetting)
{
    RayTracer::Camera camera;

    // Parse position
    const libconfig::Setting &position = cameraSetting["position"];
    double posX = position["x"];
    double posY = position["y"];
    double posZ = position["z"];
    camera._origin = Math::Point3D(posX, posY, posZ);
    // Parse resolution
    const libconfig::Setting &resolution = cameraSetting["resolution"];
    int width = resolution["width"];
    int height = resolution["height"];
    // Configure screen based on resolution
    camera._screen._origin = Math::Point3D(posX, posY, posZ - 1.0);
    camera._screen._bottomSide = Math::Vector3D(width, 0, 0);
    camera._screen._leftSide = Math::Vector3D(0, height, 0);
    return camera;
}

RayTracer::Scene SceneBuilder::build(const std::string &configFile)
{
    RayTracer::Scene scene;
    libconfig::Config cfg;

    cfg.readFile(configFile.c_str());

    // Parse camera and lights, need to implement
    try {
        const libconfig::Setting &cameraSetting = cfg.lookup("camera");
        RayTracer::Camera camera = parseCamera(cameraSetting);
    } catch (...) {
        // Camera parsing
    }
    const libconfig::Setting &primitives = cfg.lookup("primitives");
    // Parse spheres
    if (primitives.exists("spheres")) {
        const libconfig::Setting &spheres = primitives["spheres"];
        for (int i = 0; i < spheres.getLength(); i++) {
            try {
                auto sphere = PrimitiveFactory::createSphere(spheres[i]);
                scene.add(std::move(sphere));
            } catch (...) {
                // Skip invalid spheres (need to implement)
            }
        }
    }

    return scene;
}
