/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Raytracer
*/

#ifndef RAYTRACER_HPP_
#define RAYTRACER_HPP_

#include "Point3D.hpp"
#include "Vector3D.hpp"

#define IS_EXIT_SUCCESS 0
#define IS_EXIT_FAILURE 84

#define SCENE_FILE_EXTENSION ".cfg"

//intersection struct, contain hit infos
struct hitRecord {
    Math::Point3D point; //intersection point
    Math::Vector3D normal; // normal at the surface
    double t; //distance along the radius
    Math::Vector3D color; //material color
    bool frontFace; //ray hits front face or back face
    double reflectivity = 0.0; //material reflectivity [0, 1]
    Math::Vector3D reflectedDirection; //reflected ray direction (if reflectivity > 0)
};

int error_handling(int ac, char **av);

#endif /* !RAYTRACER_HPP_ */
