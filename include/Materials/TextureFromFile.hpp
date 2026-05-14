/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** TextureFromFile
*/

#ifndef TEXTUREFROMFILE_HPP_
    #define TEXTUREFROMFILE_HPP_

    #include <vector>
    #include <string>
    #include "IMaterial.hpp"

    #define PPM_MAGIC "P6"

namespace RayTracer {
    class TextureFromFile : public Interfaces::IMaterial {
        public:
            TextureFromFile(const std::string &filepath, double scale = 1.0);
            ~TextureFromFile() = default;

            Math::Vector3D getColor() const override;
            Math::Vector3D getColorAtPoint(const Math::Point3D &point) const override;
            double getReflectivity() const override;
            Math::Vector3D getReflectedDirection(const Math::Vector3D &incident,
                const Math::Vector3D &normal) const override;

        private:
            bool loadPPM(const std::string &filepath);
            bool readPPMHeader(std::ifstream &file, std::string &magic, int &maxColor);
            bool readPPMPixels(std::ifstream &file);
            int wrapCoordinate(int coord, int max) const;
            int getScaledCoordinate(double coord, double scale, int imageSize) const;

            Math::Vector3D getPixelAtIndex(int idx) const;
            Math::Vector3D getPixelColor(int x, int y) const;

            std::vector<unsigned char> _imageData;
            int _width;
            int _height;
            double _scale;
            bool _loaded;
    };
}

#endif /* !TEXTUREFROMFILE_HPP_ */
