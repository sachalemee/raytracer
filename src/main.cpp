/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** main
*/

#include <iostream>
#include "Camera.hpp"
#include "Sphere.hpp"
#include "Point3D.hpp"
#include "RayTracer.hpp"

int main(int ac, char **av)
{
    RayTracer::Camera cam;
    RayTracer::Sphere s(Math::Point3D(0, 0, -1), 0.2);
    int width = 100;
    int height = 50;

    if (error_handling(ac, av) != IS_EXIT_SUCCESS)
        return IS_EXIT_FAILURE;
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
