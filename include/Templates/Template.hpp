/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Template
*/

#ifndef TEMPLATE_HPP_
#define TEMPLATE_HPP_

template <typename T>
T square(T n)
{
    return n * n;
}

template <typename T>
T discriminantEquation(T b, T a, T c)
{
    return square(b) - 4 * a * c;
}

#endif /* !TEMPLATE_HPP_ */
