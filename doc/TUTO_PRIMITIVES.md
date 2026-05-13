# Tutoriel - Comment ajouter une nouvelle primitive

Ce tutoriel vous explique comment ajouter une nouvelle primitive (sphère, plan, cylindre, cône, etc.) dans le Raytracer, en respectant l’architecture déjà en place dans le projet.

Chaque primitive implémente `IHittable` et `ITransformable`, possède un matériau, puis s’intègre automatiquement au système de parsing de scène grâce à la factory.

L’objectif est de garder une structure claire, cohérente et facile à maintenir.

## 1. Architecture des primitives

Toutes les primitives hittables suivent la même logique de fonctionnement.

Chaque primitive :

- implémente `Interfaces::IHittable` afin de gérer les intersections rayon-objet via `hits()`
- implémente `Interfaces::ITransformable` afin de gérer les transformations géométriques
- possède un matériau via `Interfaces::IMaterial`
- retourne un `std::optional<hitRecord>` contenant les informations de collision

Le hitRecord contient :

- le point d’intersection
- la normale de surface
- la distance du rayon
- la couleur du matériau
- l’information indiquant si le rayon touche la face avant ou arrière

### Structure type d’une primitive

```cpp
namespace RayTracer {
    class Sphere : public Interfaces::IHittable,
                    public Interfaces::ITransformable {
    public:
        Sphere(const Math::Point3D &center, double radius, std::unique_ptr<Interfaces::IMaterial> material = nullptr);
        ~Sphere() = default;
        std::optional<hitRecord> hits(const RayTracer::Ray &ray) const override;
        void translate(const Math::Vector3D &offset) override;
        void rotateX(double angleDegrees) override;
        void rotateY(double angleDegrees) override;
        void rotateZ(double angleDegrees) override;

    private:
        Math::Point3D _sphCenter;
        double _sphRadius;
        std::unique_ptr<Interfaces::IMaterial> _material;
    };
}
```

## 2. Implémenter la détection d’intersection

La méthode `hits()` représente le cœur de votre primitive.

Elle effectue tous les calculs géométriques nécessaires afin de déterminer si un rayon entre en collision avec l’objet.

La méthode suit toujours les mêmes étapes :

1. Calculer l’intersection rayon-objet
2. Retourner std::nullopt si aucune collision n’existe
3. Construire un hitRecord valide si une intersection est trouvée

Le hitRecord doit contenir :

- `point` : le point d’intersection 3D
- `normal` : la normale de surface au point touché
- `t` : la distance le long du rayon
- `color` : la couleur du matériau
- `frontFace` : indique si le rayon frappe la face avant

### Exemple : intersection rayon-plan

```cpp
std::optional<hitRecord> RayTracer::Plane::hits(const RayTracer::Ray &ray) const
{
    const double denominator = ray._direction.dot(_normal);

    if (std::abs(denominator) < EPSILON)
        return std::nullopt;

    const auto posToOrigin = computeVectorBetween(ray._origin, _position);
    const double distance = posToOrigin.dot(_normal) / denominator;

    if (distance <= 0)
        return std::nullopt;

    hitRecord record;

    record.point = computePointAlongRay(ray, distance);
    record.t = distance;
    record.frontFace = denominator < 0;
    record.normal = record.frontFace ? _normal : negateVector(_normal);

    if (_material)
        record.color = _material->getColor();

    return record;
}
```

Dans cet exemple :

- `denominator` permet de savoir si le rayon est parallèle au plan
- `distance` représente la distance entre l’origine du rayon et le point d’impact
- la normale est inversée si le rayon touche la face arrière
- la couleur est récupérée uniquement si un matériau existe

## 3. Implémenter les transformations géométriques

Les méthodes de transformation modifient directement les données internes de votre primitive.

La translation déplace l’objet dans l’espace.

Les rotations modifient son orientation autour des axes X, Y et Z.

### Exemple avec un plan

```cpp
void RayTracer::Plane::translate(const Math::Vector3D &offset)
{
    _position += offset;
}

void RayTracer::Plane::rotateX(double angleDegrees)
{
    const auto [cosA, sinA] = computeAngleTrig(angleDegrees);

    rotateVectorAroundX(_normal, cosA, sinA);
}

void RayTracer::Plane::rotateY(double angleDegrees)
{
    const auto [cosA, sinA] = computeAngleTrig(angleDegrees);

    rotateVectorAroundY(_normal, cosA, sinA);
}

void RayTracer::Plane::rotateZ(double angleDegrees)
{
    const auto [cosA, sinA] = computeAngleTrig(angleDegrees);

    rotateVectorAroundZ(_normal, cosA, sinA);
}
```

Ici, seule la normale du plan tourne, car elle définit entièrement son orientation.

## 4. Intégrer la primitive dans la Factory

Une fois votre primitive créée, vous devez permettre au parser de scène de l’instancier depuis un fichier `.cfg`.

Pour cela, vous ajoutez une méthode statique dans `PrimitiveFactory`.

### Exemple : création d’une sphère

```cpp
std::unique_ptr<RayTracer::Interfaces::IHittable> PrimitiveFactory::createSphere(const libconfig::Setting &setting)
{
    double x = setting["x"];
    double y = setting["y"];
    double z = setting["z"];
    double radius = setting["r"];

    std::unique_ptr<RayTracer::FlatColor> material;

    if (setting.exists("color"))
        material = parseColor(setting["color"]);

    return std::make_unique<RayTracer::Sphere>(
        Math::Point3D(x, y, z),
        radius,
        std::move(material)
    );
}
```

Cette méthode :

- récupère les paramètres depuis le fichier de configuration
- crée le matériau si une couleur existe
- construit la primitive
- retourne un `unique_ptr<IHittable>`

Ensuite, vous ajoutez votre primitive dans `SceneBuilder::parsePrimitives()` afin qu’elle soit reconnue lors du chargement de la scène.

# 5. Format de configuration de scène

Chaque primitive possède son propre bloc dans le fichier `.cfg.`

### Exemple de configuration

```cpp
primitives:
{
    spheres = (
        { x = -40; y = 30; z = -10; r = 20; color = "red"; },
        { x = 40; y = 30; z = -10; r = 20; color = "green"; }
    );

    planes = (
        { axis = "Z"; position = -50; color = "white"; }
    );

    cylinders = (
        { x = 0; y = 0; z = 0; r = 10; height = 30; color = "blue"; }
    );

    cones = (
        { x = 0; y = 50; z = 0; r = 15; height = 40; color = "magenta"; }
    );
};
```
Chaque bloc contient les paramètres nécessaires à la création de la primitive.


# 6. Ajouter une nouvelle primitive étape par étape

## Étape 1 : Créer le fichier d’en-tête

Créez le fichier :

```
include/Primitives/MaNouvellePrimitive.hpp
```

Puis définissez votre classe :

```cpp
#ifndef MANOUVELLE_PRIMITIVE_HPP_
    #define MANOUVELLE_PRIMITIVE_HPP_

    #include <memory>
    #include <optional>

    #include "IHittable.hpp"
    #include "IMaterial.hpp"
    #include "ITransformable.hpp"

namespace RayTracer {
    class MaNouvellePrimitive : public Interfaces::IHittable,
                                public Interfaces::ITransformable {
    public:
        MaNouvellePrimitive(
            const Math::Point3D &position,
            double param1,
            std::unique_ptr<Interfaces::IMaterial> material = nullptr
        );

        ~MaNouvellePrimitive() = default;

        std::optional<hitRecord> hits(const RayTracer::Ray &ray) const override;

        void translate(const Math::Vector3D &offset) override;
        void rotateX(double angleDegrees) override;
        void rotateY(double angleDegrees) override;
        void rotateZ(double angleDegrees) override;

    private:
        Math::Point3D _position;
        double _param1;
        std::unique_ptr<Interfaces::IMaterial> _material;
    };
}

#endif /* !MANOUVELLE_PRIMITIVE_HPP_ */
```

### Étape 2 : Implémenter la classe

Créez ensuite :

```
src/Primitives/MaNouvellePrimitive.cpp
```

Puis implémentez la logique de votre primitive.

```cpp
#include <cmath>
#include <optional>

#include "MaNouvellePrimitive.hpp"
#include "PrimitiveUtils.hpp"

RayTracer::MaNouvellePrimitive::MaNouvellePrimitive( const Math::Point3D &position, double param1, std::unique_ptr<Interfaces::IMaterial> material)
    : _position(position), _param1(param1), _material(std::move(material))
{
}

std::optional<hitRecord> RayTracer::MaNouvellePrimitive::hits(
    const RayTracer::Ray &ray) const
{
    // Calcul de l’intersection spécifique à votre primitive

    hitRecord record;

    record.point = /* calculé */;
    record.normal = /* calculé */;
    record.t = /* calculé */;
    record.frontFace = /* calculé */;

    if (_material)
        record.color = _material->getColor();

    return record;
}

void RayTracer::MaNouvellePrimitive::translate(
    const Math::Vector3D &offset)
{
    _position += offset;
}

void RayTracer::MaNouvellePrimitive::rotateX(double angleDegrees)
{
    // Rotation autour de l’axe X
}

void RayTracer::MaNouvellePrimitive::rotateY(double angleDegrees)
{
    // Rotation autour de l’axe Y
}

void RayTracer::MaNouvellePrimitive::rotateZ(double angleDegrees)
{
    // Rotation autour de l’axe Z
}
```

### Étape 3 : Ajouter la méthode Factory

Dans :

```
src/Factory/PrimitiveFactory.cpp
```

Ajoutez :

```cpp
std::unique_ptr<RayTracer::Interfaces::IHittable>
PrimitiveFactory::createMaNouvellePrimitive(const libconfig::Setting &setting)
{
    double x = setting["x"];
    double y = setting["y"];
    double z = setting["z"];
    double param1 = setting["param1"];

    std::unique_ptr<RayTracer::FlatColor> material;

    if (setting.exists("color"))
        material = parseColor(setting["color"]);

    return std::make_unique<RayTracer::MaNouvellePrimitive>(
        Math::Point3D(x, y, z),
        param1,
        std::move(material)
    );
}
```

### Étape 4 : Intégrer le parsing dans SceneBuilder

Dans `SceneBuilder::parsePrimitives()`, ajoutez le parsing correspondant à votre nouvelle primitive.

C’est cette étape qui permet au moteur de reconnaître automatiquement votre bloc dans le fichier `.cfg`.

## Étape 5 : Tester votre primitive

Créez un fichier de scène contenant votre nouvelle primitive.

Vérifiez ensuite :

- que la primitive apparaît correctement
- que les intersections fonctionnent
- que les rotations et translations se comportent normalement
- que la couleur du matériau est bien appliquée

# 7. Checklist avant validation

Avant de considérer votre primitive comme terminée, vérifiez les points suivants :

- `IHittable` est correctement implémenté
- `hits()` retourne un hitRecord valide
- `ITransformable` est entièrement implémenté
- les rotations X/Y/Z existent
- le matériau est stocké dans `_material`
- la factory crée correctement l’objet
- le parser de scène reconnaît la primitive
- le `.cfg` fonctionne correctement
- les normales sont normalisées
- les intersections invalides retournent `std::nullopt`


# 8. Erreurs fréquentes

Voici les erreurs qui reviennent le plus souvent lors de l’ajout d’une primitive :

- oublier de normaliser la normale du `hitRecord`
- accepter une distance négative ou nulle
- oublier de renseigner la couleur du matériau
- oublier une rotation (`rotateX`, `rotateY` ou `rotateZ`)
- oublier le `std::move()` lors du transfert du matériau
- ne pas vérifier si `_material` vaut `nullptr`
- inverser la normale lorsque le rayon touche la face arrière
- oublier d’ajouter la primitive dans `SceneBuilder`

En général, si votre primitive s’affiche mais que l’éclairage paraît incorrect, le problème vient souvent de la normale.