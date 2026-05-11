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
            void writeHeader(std::ostream &out, const Camera &camera);
            void renderPixels(std::ostream &out, const Camera &camera);
            void renderRow(std::ostream &out, const Camera &camera, int y);
            void renderPixel(std::ostream &out, const Camera &camera, int x, int y);
            
            std::optional<hitRecord> findClosestHit(const Ray &ray);
            Math::Vector3D computePixelColor(
            const std::optional<hitRecord> &closestHit);
            
            const Scene &_scene;
            /// write single pixel color to output
            void writeColor(std::ostream &out, const Math::Vector3D &pixelColor);
            /// clamp RGB values to [0, 255]
            int clamp(double value);
    };
}

#endif /* !RENDERER_HPP_ */
