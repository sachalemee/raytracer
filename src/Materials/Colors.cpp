/*
** EPITECH PROJECT, 2026
** G-OOP-400-PAR-4-1-raytracer-29
** File description:
** Colors
*/

#include "Colors.hpp"

namespace RayTracer::Colors {

Math::Vector3D getColorByName(const std::string &colorName)
{
    static const std::unordered_map<std::string, Math::Vector3D> colorMap = {
        {"red", RED},
        {"green", GREEN},
        {"blue", BLUE},
        {"cyan", CYAN},
        {"magenta", MAGENTA},
        {"yellow", YELLOW},
        {"black", BLACK},
        {"white", WHITE},
        {"gray", GRAY},
        {"grey", GRAY},
        {"light_gray", LIGHT_GRAY},
        {"light_grey", LIGHT_GRAY},
        {"dark_gray", DARK_GRAY},
        {"dark_grey", DARK_GRAY},
        {"orange", ORANGE},
        {"purple", PURPLE},
        {"pink", PINK},
        {"brown", BROWN},
        {"lime", LIME},
        {"navy", NAVY},
        {"teal", TEAL},
        {"maroon", MAROON},
        {"olive", OLIVE},
    };

    auto it = colorMap.find(colorName);
    if (it != colorMap.end()) {
        return it->second;
    }
    return WHITE;
}

}
