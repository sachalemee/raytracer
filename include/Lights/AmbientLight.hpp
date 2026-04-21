/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** AmbientLight
*/

#ifndef AMBIENTLIGHT_HPP_
#define AMBIENTLIGHT_HPP_

#include "ILight.hpp"
class AmbientLight : public RayTracer::Interfaces::ILight {
    public:
        AmbientLight();
        ~AmbientLight();

    protected:
    private:
};

#endif /* !AMBIENTLIGHT_HPP_ */
