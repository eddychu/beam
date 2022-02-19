#pragma once
#include "../core/material.h"
#include "../core/rng.h"
#include "../core/sampling.h"
#include "../core/hittable.h"
class Lambertian : public Material
{
public:
    Lambertian(const glm::vec3 &albedo)
        : m_albedo(albedo)
    {
    }
    bool scatter(const Ray &r_in, const HitRecord &rec, glm::vec3 &attenuation, Ray &scattered) const override
    {
        auto rnd = glm::vec2(RNG::random_double(), RNG::random_double());
        auto sample = Sampling::sampleOnCosineHemisphere(rnd);
        auto scatter_direction = glm::normalize(rec.normal + sample);

        scattered = Ray(rec.p, scatter_direction);
        attenuation = m_albedo;
        return true;
    }

    glm::vec3 m_albedo;
};
