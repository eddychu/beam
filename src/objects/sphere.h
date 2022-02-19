#pragma once
#include "../core/hittable.h"
class Sphere : public Hittable
{
public:
    Sphere() = default;
    Sphere(const vec3 &center, float radius, std::shared_ptr<Material> material)
        : m_center(center), m_radius(radius), m_material(material)
    {
    }
    bool hit(const Ray &r, float t_min, float t_max, HitRecord &rec) const override;

private:
    vec3 m_center;
    float m_radius;
    std::shared_ptr<Material> m_material;
};
