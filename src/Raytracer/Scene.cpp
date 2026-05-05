/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Scene
*/

#include "Scene.hpp"

RayTracer::Scene::Scene()
{
}

void RayTracer::Scene::add(std::unique_ptr<Interfaces::IHittable> primitive)
{
    _primitives.push_back(std::move(primitive));
}

void RayTracer::Scene::add(std::unique_ptr<Interfaces::ILight> light)
{
    _lights.push_back(std::move(light));
}

void RayTracer::Scene::setCamera(const Camera &camera)
{
    _camera = camera;
}

const RayTracer::Camera &RayTracer::Scene::getCamera() const
{
    return _camera;
}

const std::vector<std::unique_ptr<RayTracer::Interfaces::IHittable>> &RayTracer::Scene::getPrimitives() const
{
    return _primitives;
}

const std::vector<std::unique_ptr<RayTracer::Interfaces::ILight>> &RayTracer::Scene::getLights() const
{
    return _lights;
}
