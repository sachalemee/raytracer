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
#include "Camera.hpp"

namespace RayTracer {
    class Scene {
        public:
            Scene();
            ~Scene() = default;

            Scene(const Scene &) = delete;
            Scene &operator=(const Scene &) = delete;
            Scene(Scene &&) = default;
            Scene &operator=(Scene &&) = default;

            /// add primitive to the scene
            void add(std::unique_ptr<Interfaces::IHittable> primitive);
            /// add light source to the scene
            void add(std::unique_ptr<Interfaces::ILight> light);
            /// set camera
            void setCamera(const Camera &camera);
            /// get camera
            const Camera &getCamera() const;
            /// get all primitives
            const std::vector<std::unique_ptr<Interfaces::IHittable>> &getPrimitives() const;
            /// get all lights
            const std::vector<std::unique_ptr<Interfaces::ILight>> &getLights() const;

        private:
            std::vector<std::unique_ptr<Interfaces::IHittable>> _primitives;
            std::vector<std::unique_ptr<Interfaces::ILight>> _lights;
            Camera _camera;
    };
}

#endif /* !SCENE_HPP_ */
