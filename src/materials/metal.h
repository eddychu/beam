#pragma once
#include <glm/glm.hpp>
#include "../core/material.h"
#include "../core/rng.h"
#include "../core/sampling.h"
#include "../core/ray.h"
#include "../core/hittable.h"
class Metal : public Material
{
public:
    Metal(const glm::vec3 &albedo, float fuzz)
        : m_albedo(albedo), m_fuzz(fuzz < 1 ? fuzz : 1)
    {
    }
    bool scatter(const Ray &r_in, const HitRecord &rec, glm::vec3 &attenuation, Ray &scattered) const override
    {
        vec3 reflected = glm::reflect(r_in.direction, rec.normal);
        auto rnd = glm::vec2(RNG::random_double(), RNG::random_double());
        auto sample = Sampling::sampleOnUniformSphere(rnd);
        scattered = Ray(rec.p, glm::normalize(reflected + m_fuzz * sample));
        attenuation = m_albedo;
        return (glm::dot(scattered.direction, rec.normal) > 0);
    }

private:
    glm::vec3 m_albedo;
    float m_fuzz;
};