/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Exception
*/

#ifndef EXCEPTIONS_HPP_
#define EXCEPTIONS_HPP_

#include <exception>

namespace RayTracer {
    namespace Exceptions {
        class fileNotFound : public std::exception {
            public:
                const char *what() const throw() {
                    return "Error: scene file not found";
                }
        };

        class invalidExtension : public std::exception {
            public:
                const char *what() const throw() {
                    return "Error: invalid file extension";
                }
        };
    }
}

#endif /* !EXCEPTIONS_HPP_ */
