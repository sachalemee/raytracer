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
#include "FlatColor.hpp"
#include "ITransformable.hpp"
#include "Point3D.hpp"
#include "Vector3D.hpp"
#include "Colors.hpp"
#include <libconfig.h++>
#include <memory>
#include <cctype>
#include <algorithm>

static std::string toLower(const std::string &str)
{
    std::string result = str;
 
    std::transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return result;
}

static std::unique_ptr<RayTracer::FlatColor> parseColor(const libconfig::Setting &setting)
{
    Math::Vector3D color;

    if (setting.getType() == libconfig::Setting::TypeString) {
        std::string colorName = toLower(setting.c_str());
        color = RayTracer::Colors::getColorByName(colorName);
    }
    else if (setting.getType() == libconfig::Setting::TypeGroup) {
        int r = setting["r"];
        int g = setting["g"];
        int b = setting["b"];
        color = Math::Vector3D(r / 255.0, g / 255.0, b / 255.0);
    }
    else {
        color = RayTracer::Colors::WHITE;
    }

    return std::make_unique<RayTracer::FlatColor>(color);
}

static void applyTranslation(
    RayTracer::Interfaces::IHittable *primitive,
    const libconfig::Setting &setting)
{
    if (!setting.exists("translate"))
        return;
    auto *transformable = dynamic_cast<RayTracer::Interfaces::ITransformable *>(primitive);
    if (!transformable)
        return;
    const libconfig::Setting &t = setting["translate"];
    double x = t["x"];
    double y = t["y"];
    double z = t["z"];
    transformable->translate(Math::Vector3D(x, y, z));
}

std::unique_ptr<RayTracer::Interfaces::IHittable> PrimitiveFactory::createSphere(const libconfig::Setting &setting)
{
    double x = setting["x"];
    double y = setting["y"];
    double z = setting["z"];
    double radius = setting["r"];
    std::unique_ptr<RayTracer::FlatColor> material;

    if (setting.exists("color"))
        material = parseColor(setting["color"]);
    auto sphere = std::make_unique<RayTracer::Sphere>(Math::Point3D(x, y, z), radius, std::move(material));
    applyTranslation(sphere.get(), setting);
    return sphere;
}

std::unique_ptr<RayTracer::Interfaces::IHittable> PrimitiveFactory::createPlane(const libconfig::Setting &setting)
{
    std::string axis = setting["axis"].c_str();
    double position = setting["position"];
    Math::Vector3D normal(0, 0, 0);
    Math::Point3D pos(0, 0, 0);

    if (axis == "X") {
        normal = Math::Vector3D(1, 0, 0);
        pos = Math::Point3D(position, 0, 0);
    } else if (axis == "Y") {
        normal = Math::Vector3D(0, 1, 0);
        pos = Math::Point3D(0, position, 0);
    } else {
        normal = Math::Vector3D(0, 0, 1);
        pos = Math::Point3D(0, 0, position);
    }
    std::unique_ptr<RayTracer::FlatColor> material;
    if (setting.exists("color"))
        material = parseColor(setting["color"]);
    auto plane = std::make_unique<RayTracer::Plane>(pos, normal, std::move(material));
    applyTranslation(plane.get(), setting);
    return plane;
}

std::unique_ptr<RayTracer::Interfaces::IHittable> PrimitiveFactory::createCylinder(const libconfig::Setting &setting)
{
    double x = setting["x"];
    double y = setting["y"];
    double z = setting["z"];
    double radius = setting["r"];
    double height = setting["height"];
    std::unique_ptr<RayTracer::FlatColor> material;

    if (setting.exists("color"))
        material = parseColor(setting["color"]);
    auto cylinder = std::make_unique<RayTracer::Cylinder>(Math::Point3D(x, y, z), radius, height, std::move(material));
    applyTranslation(cylinder.get(), setting);
    return cylinder;
}

std::unique_ptr<RayTracer::Interfaces::IHittable> PrimitiveFactory::createCone(const libconfig::Setting &setting)
{
    double x = setting["x"];
    double y = setting["y"];
    double z = setting["z"];
    double height = setting["height"];
    double radius = setting["r"];
    std::unique_ptr<RayTracer::FlatColor> material;

    if (setting.exists("color"))
        material = parseColor(setting["color"]);
    auto cone = std::make_unique<RayTracer::Cone>(Math::Point3D(x, y, z), height, radius, std::move(material));
    applyTranslation(cone.get(), setting);
    return cone;
}
