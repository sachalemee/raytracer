# Tutoriel - Comment ajouter une nouvelle primitive

Ce tutoriel vous explique comment ajouter une nouvelle primitive (sphère, plan, cylindre, cône, etc.) dans le Raytracer, en respectant l’architecture déjà en place dans le projet.

Chaque primitive implémente `IHittable` et `ITransformable`, possède un matériau, puis s’intègre automatiquement au système de parsing de scène grâce à la factory.

L’objectif est de garder une structure claire, cohérente et facile à maintenir.

## 1. Architecture des primitives

Toutes les primitives hittables suivent la même logique de fonctionnement.

### Chaque primitive :

- implémente Interfaces::IHittable afin de gérer les intersections rayon-objet via hits()
- implémente Interfaces::ITransformable afin de gérer les transformations géométriques
- possède un matériau via Interfaces::IMaterial
- retourne un std::optional<hitRecord> contenant les informations de collision

### Le hitRecord contient :

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

