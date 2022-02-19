#pragma once
#include <glm/glm.hpp>
#include "rng.h"
using namespace glm;
class Sampling
{
public:
    static vec2 sampleOnUniformDisk(const vec2 &sample)
    {
        float r = std::sqrt(sample.x);
        float angle = sample.y * (float)M_PI * 2;
        return vec2(r * cos(angle), r * sin(angle));
    }

    static vec3 sampleOnUniformSphere(const vec2 &sample)
    {
        float phi = sample.x * M_PI * 2;
        float theta = acos(1 - 2 * sample.y);
        float sinTheta = sin(theta);
        float cosTheta = cos(theta);
        float sinPhi = sin(phi);
        float cosPhi = cos(phi);
        return vec3(sinTheta * cosPhi, sinTheta * sinPhi, cosTheta);
    }

    static vec3 sampleOnUniformHemisphere(const vec2 &sample)
    {
        float phi = sample.x * M_PI * 2;
        float theta = acos(1 - sample.y);
        float sinTheta = sin(theta);
        float cosTheta = cos(theta);
        float sinPhi = sin(phi);
        float cosPhi = cos(phi);
        return vec3(sinTheta * cosPhi, sinTheta * sinPhi, cosTheta);
    }

    static vec3 sampleOnCosineHemisphere(const vec2 &sample)
    {
        float phi = sample.x * M_PI * 2;
        float theta = acos(sqrt(sample.y));
        float sinTheta = sin(theta);
        float cosTheta = cos(theta);
        float sinPhi = sin(phi);
        float cosPhi = cos(phi);
        return vec3(sinTheta * cosPhi, sinTheta * sinPhi, cosTheta);
    }
};