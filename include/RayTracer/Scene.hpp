/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Scene
*/

#ifndef SCENE_HPP_
#define SCENE_HPP_

#include <memory>
#include <vector>
#include "IHittable.hpp"
#include "ILight.hpp"

namespace RayTracer {
    class Scene {
        public:
            void add(std::unique_ptr<Interfaces::IHittable> primitive);
            void add(std::unique_ptr<Interfaces::ILight> light);

        private:
            std::vector<std::unique_ptr<Interfaces::IHittable>> _primitives;
            std::vector<std::unique_ptr<Interfaces::ILight>> _lights;
    };
}

#endif /* !SCENE_HPP_ */
