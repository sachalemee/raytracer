/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** main
*/

#include <iostream>
#include "RayTracer.hpp"
#include "SceneBuilder.hpp"
#include "Exception.hpp"
#include <libconfig.h++>

int main(int ac, char **av)
{
    try {
        if (error_handling(ac, av) != IS_EXIT_SUCCESS)
            return IS_EXIT_FAILURE;
        RayTracer::Scene scene = SceneBuilder::build(av[1]);
        // TODO: Use here the scene to render image
        std::cout << "Scene parsed successfully!\n";
    } catch (const RayTracer::Exceptions::fileNotFound &e) {
        std::cerr << e.what() << std::endl;
        return IS_EXIT_FAILURE;
    } catch (const RayTracer::Exceptions::invalidExtension &e) {
        std::cerr << e.what() << std::endl;
        return IS_EXIT_FAILURE;
    } catch (const libconfig::SettingTypeException &e) {
        std::cerr << "Error: Invalid setting type in config file" << std::endl;
        return IS_EXIT_FAILURE;
    } catch (const libconfig::SettingNotFoundException &e) {
        std::cerr << "Error: Missing setting in config file" << std::endl;
        return IS_EXIT_FAILURE;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return IS_EXIT_FAILURE;
    }    
    return IS_EXIT_SUCCESS;
}
