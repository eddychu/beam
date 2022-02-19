#pragma once
#include <memory>
#include "ray.h"
#include "material.h"
class HitRecord
{
public:
    float t;
    vec3 p;
    vec3 normal;
    std::shared_ptr<Material> material;
    bool isFront;
};

class Hittable
{
public:
    virtual bool hit(const Ray &r, float tMin, float tMax, HitRecord &rec) const = 0;
};
