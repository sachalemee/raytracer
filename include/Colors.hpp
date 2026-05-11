/*
** EPITECH PROJECT, 2026
** G-OOP-400-PAR-4-1-raytracer-29
** File description:
** Colors
*/

#ifndef COLORS_HPP_
#define COLORS_HPP_

#include "Vector3D.hpp"
#include <string>
#include <unordered_map>

namespace RayTracer::Colors {

inline static const Math::Vector3D RED{1.0, 0.0, 0.0};
inline static const Math::Vector3D GREEN{0.0, 1.0, 0.0};
inline static const Math::Vector3D BLUE{0.0, 0.0, 1.0};

inline static const Math::Vector3D CYAN{0.0, 1.0, 1.0};
inline static const Math::Vector3D MAGENTA{1.0, 0.0, 1.0};
inline static const Math::Vector3D YELLOW{1.0, 1.0, 0.0};

inline static const Math::Vector3D BLACK{0.0, 0.0, 0.0};
inline static const Math::Vector3D WHITE{1.0, 1.0, 1.0};
inline static const Math::Vector3D GRAY{0.5, 0.5, 0.5};
inline static const Math::Vector3D LIGHT_GRAY{0.75, 0.75, 0.75};
inline static const Math::Vector3D DARK_GRAY{0.25, 0.25, 0.25};

inline static const Math::Vector3D ORANGE{1.0, 0.5, 0.0};
inline static const Math::Vector3D PURPLE{0.5, 0.0, 0.5};
inline static const Math::Vector3D PINK{1.0, 0.75, 0.8};
inline static const Math::Vector3D BROWN{0.6, 0.3, 0.0};
inline static const Math::Vector3D LIME{0.5, 1.0, 0.0};
inline static const Math::Vector3D NAVY{0.0, 0.0, 0.5};
inline static const Math::Vector3D TEAL{0.0, 0.5, 0.5};
inline static const Math::Vector3D MAROON{0.5, 0.0, 0.0};
inline static const Math::Vector3D OLIVE{0.5, 0.5, 0.0};

Math::Vector3D getColorByName(const std::string &colorName);

}

#endif /* !COLORS_HPP_ */