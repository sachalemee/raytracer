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
#include "AmbientLight.hpp"
#include "DirectionalLight.hpp"

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

static void parseAmbientLight(RayTracer::Scene &scene, const libconfig::Setting &lightsSetting)
{
    if (!lightsSetting.exists("ambient"))
        return;
    double ambientVal = lightsSetting["ambient"];
    scene.add(std::make_unique<RayTracer::AmbientLight>(
        Math::Vector3D(ambientVal, ambientVal, ambientVal)));
}

static void parseDirectionalLights(RayTracer::Scene &scene, const libconfig::Setting &lightsSetting)
{
    if (!lightsSetting.exists("directional"))
        return;
    const libconfig::Setting &dirLights = lightsSetting["directional"];
    double intensity = 1.0;
    if (lightsSetting.exists("diffuse"))
        intensity = lightsSetting["diffuse"];
    for (int i = 0; i < dirLights.getLength(); i++) {
        try {
            double dx = dirLights[i]["x"];
            double dy = dirLights[i]["y"];
            double dz = dirLights[i]["z"];
            scene.add(std::make_unique<RayTracer::DirectionalLight>(
                Math::Vector3D(dx, dy, dz),
                Math::Vector3D(intensity, intensity, intensity)));
        } catch (...) {}
    }
}

void SceneBuilder::parseLights(RayTracer::Scene &scene, const libconfig::Setting &lightsSetting)
{
    parseAmbientLight(scene, lightsSetting);
    parseDirectionalLights(scene, lightsSetting);
}

RayTracer::Scene SceneBuilder::build(const std::string &configFile)
{
    RayTracer::Scene scene;
    libconfig::Config cfg;

    cfg.readFile(configFile.c_str());

    try {
        const libconfig::Setting &cameraSetting = cfg.lookup("camera");
        scene.setCamera(parseCamera(cameraSetting));
    } catch (...) {}

    try {
        const libconfig::Setting &primitives = cfg.lookup("primitives");

        if (primitives.exists("spheres")) {
            const libconfig::Setting &spheres = primitives["spheres"];
            for (int i = 0; i < spheres.getLength(); i++) {
                try {
                    scene.add(PrimitiveFactory::createSphere(spheres[i]));
                } catch (...) {}
            }
        }

        if (primitives.exists("planes")) {
            const libconfig::Setting &planes = primitives["planes"];
            for (int i = 0; i < planes.getLength(); i++) {
                try {
                    scene.add(PrimitiveFactory::createPlane(planes[i]));
                } catch (...) {}
            }
        }

        if (primitives.exists("cylinders")) {
            const libconfig::Setting &cylinders = primitives["cylinders"];
            for (int i = 0; i < cylinders.getLength(); i++) {
                try {
                    scene.add(PrimitiveFactory::createCylinder(cylinders[i]));
                } catch (...) {}
            }
        }

        if (primitives.exists("cones")) {
            const libconfig::Setting &cones = primitives["cones"];
            for (int i = 0; i < cones.getLength(); i++) {
                try {
                    scene.add(PrimitiveFactory::createCone(cones[i]));
                } catch (...) {}
            }
        }
    } catch (...) {}

    try {
        const libconfig::Setting &lights = cfg.lookup("lights");
        parseLights(scene, lights);
    } catch (...) {}

    return scene;
}
