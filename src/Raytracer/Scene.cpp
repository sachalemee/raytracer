/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Scene
*/

#include "Scene.hpp"

void RayTracer::Scene::add(std::unique_ptr<Interfaces::IHittable> primitive)
{
    _primitives.push_back(std::move(primitive));
}

void RayTracer::Scene::add(std::unique_ptr<Interfaces::ILight> light)
{
    _lights.push_back(std::move(light));
}
