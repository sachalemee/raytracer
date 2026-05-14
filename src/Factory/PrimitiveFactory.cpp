/*
** EPITECH PROJECT, 2026
** G-OOP-400-PAR-4-1-raytracer-29
** File description:
** PrimitiveFactory
*/

#include <libconfig.h++>
#include <memory>
#include <cctype>
#include <algorithm>
#include "PrimitiveFactory.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"
#include "Cylinder.hpp"
#include "Cone.hpp"
#include "FlatColor.hpp"
#include "Mirror.hpp"
#include "Chessboard.hpp"
#include "TextureFromFile.hpp"
#include "Transparency.hpp"
#include "Point3D.hpp"
#include "Vector3D.hpp"
#include "Colors.hpp"

static std::string toLower(const std::string &str)
{
    std::string result = str;
 
    std::transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return result;
}

static std::unique_ptr<RayTracer::Interfaces::IMaterial> parseColor(const libconfig::Setting &setting)
{
    Math::Vector3D color;

    if (setting.getType() == libconfig::Setting::TypeString) {
        std::string colorName = toLower(setting.c_str());
        color = RayTracer::Colors::getColorByName(colorName);
    }
    else if (setting.getType() == libconfig::Setting::TypeGroup)
        color = Math::Vector3D(int(setting["r"]) / 255.0, int(setting["g"]) / 255.0, int(setting["b"]) / 255.0);
    else
        color = RayTracer::Colors::WHITE;
    return std::make_unique<RayTracer::FlatColor>(color);
}

static Math::Vector3D parseColorVector(const libconfig::Setting &colorSetting)
{
    return Math::Vector3D(int(colorSetting["r"]) / 255.0, int(colorSetting["g"]) / 255.0, int(colorSetting["b"]) / 255.0);
}

static std::unique_ptr<RayTracer::Interfaces::IMaterial> parseChessboard(
    const libconfig::Setting &materialSetting)
{
    Math::Vector3D color1(1.0, 1.0, 1.0);
    Math::Vector3D color2(0.0, 0.0, 0.0);
    double scale = 10.0;

    if (materialSetting.exists("color1"))
        color1 = parseColorVector(materialSetting["color1"]);
    if (materialSetting.exists("color2"))
        color2 = parseColorVector(materialSetting["color2"]);
    if (materialSetting.exists("scale"))
        scale = materialSetting["scale"];
    return std::make_unique<RayTracer::Chessboard>(color1, color2, scale);
}

static std::unique_ptr<RayTracer::Interfaces::IMaterial> parseTextureFile(
    const libconfig::Setting &materialSetting)
{
    std::string filepath = materialSetting["filepath"].c_str();
    double scale = materialSetting.exists("scale") ? materialSetting["scale"] : 1.0;

    return std::make_unique<RayTracer::TextureFromFile>(filepath, scale);
}

static std::unique_ptr<RayTracer::Interfaces::IMaterial> parseTransparency(
    const libconfig::Setting &materialSetting)
{
    (void)materialSetting;
    return std::make_unique<RayTracer::Transparency>();
}

static std::unique_ptr<RayTracer::Interfaces::IMaterial> parseMirror(
    const libconfig::Setting &materialSetting)
{
    Math::Vector3D tint(1.0, 1.0, 1.0);
    double reflectivity = 1.0;

    if (materialSetting.exists("tint"))
        tint = parseColorVector(materialSetting["tint"]);
    if (materialSetting.exists("reflectivity"))
        reflectivity = materialSetting["reflectivity"];
    return std::make_unique<RayTracer::Mirror>(tint, reflectivity);
}

static std::unique_ptr<RayTracer::Interfaces::IMaterial> parseTypedMaterial(
    const libconfig::Setting &materialSetting)
{
    std::string materialType;

    materialType = materialSetting["type"].c_str();
    materialType = toLower(materialType);

    if (materialType == "chessboard")
        return parseChessboard(materialSetting);
    else if (materialType == "texture" || materialType == "texturefile")
        return parseTextureFile(materialSetting);
    else if (materialType == "mirror")
        return parseMirror(materialSetting);
    else if (materialType == "transparency")
        return parseTransparency(materialSetting);
    return std::make_unique<RayTracer::FlatColor>(RayTracer::Colors::WHITE);
}

static std::unique_ptr<RayTracer::Interfaces::IMaterial> parseLegacyMaterial(
    const libconfig::Setting &setting)
{
    double reflectivity = 0.0;
    Math::Vector3D color(1, 1, 1);

    if (setting.exists("reflectivity"))
        reflectivity = setting["reflectivity"];
    if (setting.exists("color")) {
        auto flatColor = parseColor(setting["color"]);
        color = flatColor->getColor();
    }
    if (reflectivity > 0.0)
        return std::make_unique<RayTracer::Mirror>(color, reflectivity);
    return std::make_unique<RayTracer::FlatColor>(color);
}

static std::unique_ptr<RayTracer::Interfaces::IMaterial> parseMaterial(
    const libconfig::Setting &setting)
{
    if (setting.exists("material")) {
        const libconfig::Setting &materialSetting = setting["material"];
        if (materialSetting.exists("type"))
            return parseTypedMaterial(materialSetting);
    }
    return parseLegacyMaterial(setting);
}

template<typename T>
static void applyTranslation(std::unique_ptr<T> &primitive, const libconfig::Setting &setting)
{
    if (!setting.exists("translate"))
        return;
    const libconfig::Setting &t = setting["translate"];
    primitive->translate(Math::Vector3D(double(t["x"]), double(t["y"]), double(t["z"])));
}

template<typename T>
static void applyRotation(std::unique_ptr<T> &primitive, const libconfig::Setting &setting)
{
    if (!setting.exists("rotation"))
        return;
    const libconfig::Setting &r = setting["rotation"];
    if (r.exists("x"))
        primitive->rotateX(double(r["x"]));
    if (r.exists("y"))
        primitive->rotateY(double(r["y"]));
    if (r.exists("z"))
        primitive->rotateZ(double(r["z"]));
}

std::unique_ptr<RayTracer::Interfaces::IHittable> PrimitiveFactory::createSphere(const libconfig::Setting &setting)
{
    double x = setting["x"];
    double y = setting["y"];
    double z = setting["z"];
    double radius = setting["r"];
    std::unique_ptr<RayTracer::Interfaces::IMaterial> material;

    if (setting.exists("color") || setting.exists("reflectivity") || setting.exists("material"))
        material = parseMaterial(setting);
    auto sphere = std::make_unique<RayTracer::Sphere>(Math::Point3D(x, y, z), radius, std::move(material));
    applyTranslation(sphere, setting);
    applyRotation(sphere, setting);
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
    std::unique_ptr<RayTracer::Interfaces::IMaterial> material;
    if (setting.exists("color") || setting.exists("reflectivity") || setting.exists("material"))
        material = parseMaterial(setting);
    auto plane = std::make_unique<RayTracer::Plane>(pos, normal, std::move(material));
    applyTranslation(plane, setting);
    applyRotation(plane, setting);
    return plane;
}

std::unique_ptr<RayTracer::Interfaces::IHittable> PrimitiveFactory::createCylinder(const libconfig::Setting &setting)
{
    double x = setting["x"];
    double y = setting["y"];
    double z = setting["z"];
    double radius = setting["r"];
    double height = setting["height"];
    std::unique_ptr<RayTracer::Interfaces::IMaterial> material;

    if (setting.exists("color") || setting.exists("reflectivity") || setting.exists("material"))
        material = parseMaterial(setting);
    auto cylinder = std::make_unique<RayTracer::Cylinder>(Math::Point3D(x, y, z), radius, height, std::move(material));
    applyRotation(cylinder, setting);
    applyTranslation(cylinder, setting);
    return cylinder;
}

std::unique_ptr<RayTracer::Interfaces::IHittable> PrimitiveFactory::createCone(const libconfig::Setting &setting)
{
    double x = setting["x"];
    double y = setting["y"];
    double z = setting["z"];
    double height = setting["height"];
    double radius = setting["r"];
    std::unique_ptr<RayTracer::Interfaces::IMaterial> material;

    if (setting.exists("color") || setting.exists("reflectivity") || setting.exists("material"))
        material = parseMaterial(setting);
    auto cone = std::make_unique<RayTracer::Cone>(Math::Point3D(x, y, z), height, radius, std::move(material));
    applyRotation(cone, setting);
    applyTranslation(cone, setting);
    return cone;
}
