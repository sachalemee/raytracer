/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** errorHandling
*/

#include <filesystem>
#include <iostream>
#include "RayTracer.hpp"
#include "Exception.hpp"

static int helper(void)
{
    std::cout << "USAGE: ./raytracer <SCENE_FILE>\n";
    std::cout << "  SCENE_FILE: scene configuration\n";
    return IS_EXIT_FAILURE;
}

// MUST use a specific error throw
int error_handling(int ac, char **av)
{
    if (ac != 2)
        return helper();
    std::filesystem::path path(av[1]);
    if (!std::filesystem::exists(path)) {
        throw RayTracer::Exceptions::fileNotFound();
    }
    if (path.extension() != SCENE_FILE_EXTENSION) {
        throw RayTracer::Exceptions::invalidExtension();
    }
    return IS_EXIT_SUCCESS;
}
