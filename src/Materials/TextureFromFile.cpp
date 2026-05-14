/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** TextureFromFile
*/

#include <cmath>
#include <fstream>
#include "TextureFromFile.hpp"

RayTracer::TextureFromFile::TextureFromFile(const std::string &filepath, double scale)
    : _width(0), _height(0), _scale(scale), _loaded(false)
{
    _loaded = loadPPM(filepath);
}

bool RayTracer::TextureFromFile::readPPMHeader(std::ifstream &file,
    std::string &magic, int &maxColor)
{
    file >> magic;
    if (magic != PPM_MAGIC)
        return false;
    file >> _width >> _height >> maxColor;
    file.ignore();
    return _width > 0 && _height > 0;
}

bool RayTracer::TextureFromFile::readPPMPixels(std::ifstream &file)
{
    int pixelCount = _width * _height * 3;

    _imageData.resize(pixelCount);
    file.read((char*)_imageData.data(), pixelCount);
    return file.good();
}

bool RayTracer::TextureFromFile::loadPPM(const std::string &filepath)
{
    std::ifstream file;
    std::string magic;
    int maxColor;

    file.open(filepath, std::ios::binary);
    if (!file.is_open())
        return false;
    if (!readPPMHeader(file, magic, maxColor)) {
        file.close();
        return false;
    }
    return readPPMPixels(file);
}

int RayTracer::TextureFromFile::wrapCoordinate(int coord, int max) const
{
    int wrapped;

    wrapped = ((coord % max) + max) % max;
    return wrapped;
}

Math::Vector3D RayTracer::TextureFromFile::getPixelAtIndex(int idx) const
{
    Math::Vector3D color;

    if (idx < 0 || idx >= int(_imageData.size() - 2))
        return Math::Vector3D(1.0, 1.0, 1.0);
    color = Math::Vector3D(_imageData[idx] / 255.0, _imageData[idx + 1] / 255.0, _imageData[idx + 2] / 255.0);
    return color;
}

Math::Vector3D RayTracer::TextureFromFile::getPixelColor(int x, int y) const
{
    int idx;

    if (!_loaded || _width <= 0 || _height <= 0)
        return Math::Vector3D(1.0, 1.0, 1.0);
    x = wrapCoordinate(x, _width);
    y = wrapCoordinate(y, _height);
    idx = (y * _width + x) * 3;
    return getPixelAtIndex(idx);
}

int RayTracer::TextureFromFile::getScaledCoordinate(double coord, double scale, int imageSize) const
{
    double normalized;
    int pixel;

    normalized = (coord / scale) * imageSize;
    pixel = (int)std::floor(normalized);
    return pixel;
}

Math::Vector3D RayTracer::TextureFromFile::getColor() const
{
    return Math::Vector3D(1.0, 1.0, 1.0);
}

Math::Vector3D RayTracer::TextureFromFile::getColorAtPoint(const Math::Point3D &point) const
{
    int x;
    int y;

    if (!_loaded || _width <= 0 || _height <= 0)
        return Math::Vector3D(1.0, 1.0, 1.0);
    x = getScaledCoordinate(point._xCmp, _scale, _width);
    y = getScaledCoordinate(point._zCmp, _scale, _height);
    return getPixelColor(x, y);
}

double RayTracer::TextureFromFile::getReflectivity() const
{
    return 0.0;
}

Math::Vector3D RayTracer::TextureFromFile::getReflectedDirection(const Math::Vector3D &incident,
    const Math::Vector3D &normal) const
{
    double dotProd = incident.dot(normal);

    return incident - normal * (2.0 * dotProd);
}
