/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Cone
*/

#ifndef CONE_HPP_
#define CONE_HPP_

#include "IHittable.hpp"

// should
namespace RayTracer {
    class Cone : public Interfaces::IHittable {
        public:
            Cone();
            ~Cone() = default;

            std::optional<hitRecord> hits(const RayTracer::Ray &ray) const override;

        protected:
        private:
    };
}

#endif /* !CONE_HPP_ */
