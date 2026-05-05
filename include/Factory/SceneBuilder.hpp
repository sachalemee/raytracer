/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** SceneBuilder
*/

#ifndef SCENEBUILDER_HPP_
#define SCENEBUILDER_HPP_

#include <string>
#include "Scene.hpp"
#include "Camera.hpp"
#include <libconfig.h++>

// "Additionally, you must use at least 2 design patterns [..] ":
// Builder
class SceneBuilder {
    public:
        static RayTracer::Scene build(const std::string &configFile);
        static RayTracer::Camera parseCamera(const libconfig::Setting &cameraSetting);

    private:
        SceneBuilder() = delete;
};

#endif /* !SCENEBUILDER_HPP_ */