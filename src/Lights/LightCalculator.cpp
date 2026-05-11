/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** LightCalculator
*/

#include "LightCalculator.hpp"
#include "Ray.hpp"
#include "PrimitiveUtils.hpp"

Math::Vector3D RayTracer::LightCalculator::componentMultiply(
    const Math::Vector3D &a, const Math::Vector3D &b)
{
    return Math::Vector3D(a._xCmp * b._xCmp, a._yCmp * b._yCmp, a._zCmp * b._zCmp);
}

bool RayTracer::LightCalculator::isInShadow(
    const Math::Point3D &hitPoint,
    const Math::Vector3D &toLightDir,
    const std::vector<std::unique_ptr<Interfaces::IHittable>> &primitives)
{
    Math::Point3D shadowOrigin(
        hitPoint._xCmp + toLightDir._xCmp * 1e-4,
        hitPoint._yCmp + toLightDir._yCmp * 1e-4,
        hitPoint._zCmp + toLightDir._zCmp * 1e-4
    );
    Ray shadowRay(shadowOrigin, toLightDir);
    for (const auto &primitive : primitives) {
        if (primitive->hits(shadowRay))
            return true;
    }
    return false;
}

Math::Vector3D RayTracer::LightCalculator::compute(
    const hitRecord &record,
    const std::vector<std::unique_ptr<Interfaces::ILight>> &lights,
    const std::vector<std::unique_ptr<Interfaces::IHittable>> &primitives)
{
    Math::Vector3D finalColor(0, 0, 0);

    for (const auto &light : lights) {
        Math::Vector3D dir = light->getDirection(record.point);
        double dirLen = dir.length();
        if (dirLen < EPSILON) {
            finalColor += componentMultiply(light->getIntensity(), record.color);
        } else {
            Math::Vector3D toLightDir(-dir._xCmp / dirLen,
                -dir._yCmp / dirLen,
                -dir._zCmp / dirLen);
            double diffuse = record.normal.dot(toLightDir);
            if (diffuse <= 0)
                continue;
            if (isInShadow(record.point, toLightDir, primitives))
                continue;
            finalColor += componentMultiply(light->getIntensity() * diffuse, record.color);
        }
    }
    return finalColor;
}
