#pragma once
#include <glm/glm.hpp>
class Ray;
class HitRecord;
class Material
{
public:
    virtual bool scatter(const Ray &r_in, const HitRecord &rec, glm::vec3 &attenuation, Ray &scattered) const = 0;
};