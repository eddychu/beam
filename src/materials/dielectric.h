#pragma once

#include "../core/material.h"
#include "../core/ray.h"
#include "../core/hittable.h"

// vec3 my_refract(const vec3 &uv, const vec3 &n, float etai_over_etat)
// {
//     float cos_theta = fmin(dot(-uv, n), 1.0);
//     vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
//     vec3 r_out_parallel = -sqrt(fabs(1.0f - glm::length2(r_out_perp))) * n;
//     return r_out_perp + r_out_parallel;
// }

class Dielectric : public Material
{
public:
    Dielectric(float ri) : ref_idx(ri) {}

    virtual bool scatter(const Ray &r_in, const HitRecord &rec, glm::vec3 &attenuation, Ray &scattered) const override
    {
        attenuation = glm::vec3(1.0f);
        float refractionRatio = rec.isFront ? (1.0f / ref_idx) : (ref_idx);
        float cosTheta = fmin(dot(-r_in.direction, rec.normal), 1.0);
        float sinTheta = sqrt(1.0f - cosTheta * cosTheta);

        bool cannotRefract = (refractionRatio * sinTheta > 1.0f);

        vec3 direction;
        if (cannotRefract) {
            direction = reflect(r_in.direction, rec.normal);
        } else {
            direction = refract(r_in.direction, rec.normal, refractionRatio);
        }
        
       
        scattered = Ray(rec.p, glm::normalize(direction));
        return true;
    }

private:
    float ref_idx;
};