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
    camera._width = width;
    camera._height = height;
    // FOV-based screen setup — camera looks in +y, up is +z, right is +x
    double fov = 72.0;
    if (cameraSetting.exists("fieldOfView"))
        fov = cameraSetting["fieldOfView"];
    double halfAngle = fov / 2.0 * M_PI / 180.0;
    double halfH = std::tan(halfAngle);
    double halfW = halfH * ((double)width / height);
    camera._screen._origin = Math::Point3D(posX - halfW, posY + 1.0, posZ - halfH);
    camera._screen._bottomSide = Math::Vector3D(2.0 * halfW, 0, 0);
    camera._screen._leftSide = Math::Vector3D(0, 0, 2.0 * halfH);
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

static void parsePrimitives(RayTracer::Scene &scene, const libconfig::Setting &primitives)
{
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
}

RayTracer::Scene SceneBuilder::build(const std::string &configFile)
{
    RayTracer::Scene scene;
    libconfig::Config cfg;

    cfg.setAutoConvert(true);
    cfg.readFile(configFile.c_str());

    try {
        scene.setCamera(parseCamera(cfg.lookup("camera")));
    } catch (...) {}
    try {
        parsePrimitives(scene, cfg.lookup("primitives"));
    } catch (...) {}
    try {
        parseLights(scene, cfg.lookup("lights"));
    } catch (...) {}
    return scene;
}
