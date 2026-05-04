/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Renderer
*/

#ifndef RENDERER_HPP_
#define RENDERER_HPP_

#include <string>
#include "Scene.hpp"
#include "Vector3D.hpp"

namespace RayTracer {
    class Renderer {
        public:
            Renderer(const Scene &scene);
            ~Renderer() = default;
            
            /// render scene to ppm file
            void render(const std::string &outputFile);
            
            /// render and return ppm content as string
            std::string renderToString();

        private:
            const Scene &_scene;
            
            /// write single pixel color to output
            void writeColor(std::ostream &out, const Math::Vector3D &pixelColor);
            
            /// clamp RGB values to [0, 255]
            int clamp(double value);
    };
}

#endif /* !RENDERER_HPP_ */
