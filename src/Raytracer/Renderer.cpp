/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Renderer
*/

#include "Renderer.hpp"
#include "LightCalculator.hpp"
#include "Ray.hpp"
#include <fstream>
#include <sstream>
#include <cmath>

RayTracer::Renderer::Renderer(const Scene &scene)
    : _scene(scene)
{
}

void RayTracer::Renderer::render(const std::string &outputFile)
{
    std::ofstream file(outputFile);

    if (!file.is_open())
        throw std::runtime_error("Failed to open output file: " + outputFile);

    file << renderToString();
    file.close();
}

std::string RayTracer::Renderer::renderToString()
{
    const Camera &camera = _scene.getCamera();

    std::ostringstream output;

    writeHeader(output, camera);
    renderPixels(output, camera);

    return output.str();
}

void RayTracer::Renderer::writeHeader(std::ostream &out, const Camera &camera)
{
    out << "P3\n";
    out << camera._width << " " << camera._height << "\n";
    out << "255\n";
}

void RayTracer::Renderer::renderPixels(std::ostream &out, const Camera &camera)
{
    int height = camera._height;

    for (int y = 0; y < height; ++y) {
        renderRow(out, camera, y);
    }
}

void RayTracer::Renderer::renderRow(std::ostream &out,
    const Camera &camera,
    int y)
{
    int width = camera._width;

    for (int x = 0; x < width; ++x) {
        renderPixel(out, camera, x, y);
    }
}

void RayTracer::Renderer::renderPixel(std::ostream &out, const Camera &camera, int x, int y)
{
    double u = static_cast<double>(x) / camera._width;
    double v = 1.0 - (static_cast<double>(y) / camera._height);
    Ray ray = camera.ray(u, v);
    std::optional<hitRecord> closestHit = findClosestHit(ray);
    Math::Vector3D pixelColor = computePixelColor(closestHit);
    writeColor(out, pixelColor);
}

std::optional<hitRecord> RayTracer::Renderer::findClosestHit(
    const Ray &ray)
{
    const std::vector<std::unique_ptr<Interfaces::IHittable>>&primitives = _scene.getPrimitives();
    std::optional<hitRecord> closestHit;
    double closestDistance = 1e100;
    for (const auto &primitive : primitives) {
        std::optional<hitRecord> hit = primitive->hits(ray);
        if (hit && hit->t < closestDistance) {
            closestDistance = hit->t;
            closestHit = hit;
        }
    }

    return closestHit;
}

Math::Vector3D RayTracer::Renderer::computePixelColor(
    const std::optional<hitRecord> &closestHit, int depth)
{
    const std::vector<std::unique_ptr<Interfaces::ILight>> &lights = _scene.getLights();
    const std::vector<std::unique_ptr<Interfaces::IHittable>> &primitives = _scene.getPrimitives();
    double offsetSign;

    if (!closestHit)
        return Math::Vector3D(0, 0, 0);
    Math::Vector3D litColor = LightCalculator::compute(*closestHit, lights, primitives);
    if (closestHit->reflectivity <= 0.0 || depth >= MAX_REFLECTION_DEPTH)
        return litColor;
    offsetSign = closestHit->isTransparent ? -1.0 : 1.0;
    Math::Point3D reflectOrigin(
        closestHit->point._xCmp + closestHit->normal._xCmp * 1e-4 * offsetSign,
        closestHit->point._yCmp + closestHit->normal._yCmp * 1e-4 * offsetSign,
        closestHit->point._zCmp + closestHit->normal._zCmp * 1e-4 * offsetSign);
    Ray reflectRay(reflectOrigin, closestHit->reflectedDirection);
    Math::Vector3D reflectedColor = computePixelColor(findClosestHit(reflectRay), depth + 1);
    double r = closestHit->reflectivity;
    return Math::Vector3D(
        (1.0 - r) * litColor._xCmp + r * reflectedColor._xCmp,
        (1.0 - r) * litColor._yCmp + r * reflectedColor._yCmp,
        (1.0 - r) * litColor._zCmp + r * reflectedColor._zCmp);
}

void RayTracer::Renderer::writeColor(std::ostream &out,
    const Math::Vector3D &pixelColor)
{
    int r = clamp(pixelColor._xCmp * 255.0);
    int g = clamp(pixelColor._yCmp * 255.0);
    int b = clamp(pixelColor._zCmp * 255.0);

    out << r << " " << g << " " << b << "\n";
}

int RayTracer::Renderer::clamp(double value)
{
    if (value < 0.0)
        return 0;
    if (value > 255.0)
        return 255;
    return static_cast<int>(value);
}
