/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Primitive Utils - Shared utility functions for primitives
*/

#ifndef PRIMITIVEUTILS_HPP_
#define PRIMITIVEUTILS_HPP_

#include <optional>
#include <utility>
#include <memory>
#include "Point3D.hpp"
#include "RayTracer.hpp"
#include "Vector3D.hpp"
#include "Ray.hpp"
#include "Template.hpp"
#include "IMaterial.hpp"

#define PI 3.14159265358979323846
#define EPSILON 1e-9

Math::Vector3D computeVectorBetween(const Math::Point3D &from, const Math::Point3D &to);
Math::Vector3D scale(const Math::Vector3D &vector, double factor);
Math::Vector3D subtract(const Math::Vector3D &lhs, const Math::Vector3D &rhs);
Math::Vector3D add(const Math::Vector3D &lhs, const Math::Vector3D &rhs);
Math::Vector3D negateVector(const Math::Vector3D &vector);
Math::Point3D offsetPoint(const Math::Point3D &point, const Math::Vector3D &direction, double scalar);
Math::Point3D computePointAlongRay(const RayTracer::Ray &ray, double distance);
Math::Vector3D projectPerpendicular(const Math::Vector3D &vector, const Math::Vector3D &axis);
void normalizeInPlace(Math::Vector3D &vector);
void normalize(Math::Vector3D &vector);
std::optional<double> findNearestPositiveRoot(double coefA, double coefB, double coefC);
void considerHit(std::optional<hitRecord> &best, const std::optional<hitRecord> &candidate);
double degreesToRadians(double angleDegrees);
Math::Vector3D rotateAroundX(const Math::Vector3D &vector, double angleRad);
Math::Vector3D rotateAroundY(const Math::Vector3D &vector, double angleRad);
Math::Vector3D rotateAroundZ(const Math::Vector3D &vector, double angleRad);
std::pair<double, double> computeAngleTrig(double angleDegrees);
void rotatePointAroundX(Math::Point3D &point, double cosA, double sinA);
void rotatePointAroundY(Math::Point3D &point, double cosA, double sinA);
void rotatePointAroundZ(Math::Point3D &point, double cosA, double sinA);
Math::Vector3D computeEdge(const Math::Point3D &from, const Math::Point3D &to);
Math::Vector3D computeCrossProduct(const Math::Vector3D &a, const Math::Vector3D &b);
double computeDotProduct(const Math::Vector3D &a, const Math::Vector3D &b);
hitRecord buildSpherehitRecord(const RayTracer::Ray &ray, double distance, const Math::Point3D &center);
hitRecord buildhitRecord(const RayTracer::Ray &ray, double distance, const Math::Vector3D &normal);
void rotateVectorAroundX(Math::Vector3D &vector, double cosA, double sinA);
void rotateVectorAroundY(Math::Vector3D &vector, double cosA, double sinA);
void rotateVectorAroundZ(Math::Vector3D &vector, double cosA, double sinA);
void applyMaterial(hitRecord &record, const RayTracer::Ray &ray,
    const std::unique_ptr<RayTracer::Interfaces::IMaterial> &material);

#endif /* !PRIMITIVEUTILS_HPP_ */
