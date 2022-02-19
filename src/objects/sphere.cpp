#include "sphere.h"
// #include <glm/glm.hpp>
bool Sphere::hit(const Ray &ray, float t_min, float t_max, HitRecord &rec) const
{
    vec3 oc = ray.origin - m_center;
    float a = dot(ray.direction, ray.direction);
    float b = dot(oc, ray.direction);
    float c = dot(oc, oc) - m_radius * m_radius;
    float discriminant = b * b - a * c;
    if (discriminant < 0.0f)
        return false;
    float sqrtDiscriminant = sqrt(discriminant);
    float t = (-b - sqrtDiscriminant) / a;
    if (t < t_min || t > t_max)
    {
        t = (-b + sqrtDiscriminant) / a;
        if (t < t_min || t > t_max)
            return false;
    }
    rec.t = t;
    rec.p = ray.origin + t * ray.direction;
    auto normal = glm::normalize(rec.p - m_center);
    rec.isFront = dot(ray.direction, normal) < 0.0f;
    if (rec.isFront)
    {
        rec.normal = normal;
    }
    else
    {
        rec.normal = -normal;
    }
    rec.material = m_material;
    return true;
}
