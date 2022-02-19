#pragma once
#include <glm/glm.hpp>
using namespace glm;
struct Ray
{
    Ray() : origin(), direction() {}
    Ray(vec3 origin, vec3 direction) : origin(origin), direction(direction) {}
    Ray(const Ray &ray) : origin(ray.origin), direction(ray.direction)
    {
    }

    Ray &operator=(const Ray &ray)
    {
        origin = ray.origin;
        direction = ray.direction;
        return *this;
    }

    vec3 at(float t) const
    {
        return origin + t * direction;
    }

    vec3 origin;
    vec3 direction;
};