/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** main
*/

#include "Camera.hpp"
#include "Sphere.hpp"
#include "Point3D.hpp"
#include <iostream>

int main()
{
    RayTracer::Camera cam;
    RayTracer::Sphere s(Math::Point3D(0, 0, -1), 0.2);
    int width = 100;
    int height = 50;

    // MUST implement error handling, done but have to link it with makefile and corresponding .hpp file
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double u = (double)x / width;
            double v = (double)(height - 1 - y) / height;
            RayTracer::Ray r = cam.ray(u, v);
            if (s.hits(r)) {
                std::cout << "O";
            } else {
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }
    return 0;
}
