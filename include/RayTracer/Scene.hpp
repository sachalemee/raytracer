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
            
            /// Add a primitive to the scene
            void addPrimitive(std::unique_ptr<Interfaces::IHittable> primitive);
            
            /// Add a light source to the scene
            void addLight(std::unique_ptr<Interfaces::ILight> light);
            
            /// Set the camera
            void setCamera(const Camera &camera);
            
            /// Get the camera
            const Camera &getCamera() const;
            
            /// Get all primitives
            const std::vector<std::unique_ptr<Interfaces::IHittable>> &getPrimitives() const;
            
            /// Get all lights
            const std::vector<std::unique_ptr<Interfaces::ILight>> &getLights() const;

        private:
            Camera _camera;
            std::vector<std::unique_ptr<Interfaces::IHittable>> _primitives;
            std::vector<std::unique_ptr<Interfaces::ILight>> _lights;
    };
}

#endif /* !SCENE_HPP_ */
