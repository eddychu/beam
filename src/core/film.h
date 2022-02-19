#pragma once
#include <vector>
using namespace std;
#include <glm/glm.hpp>
using namespace glm;
struct Film
{
    Film(int w, int h) : width(w), height(h), pixels(w * h) {}

    void set(int x, int y, vec3 color)
    {
        pixels[y * width + x] = color;
    }

    void set(int x, int y, float r, float g, float b)
    {
        pixels[y * width + x] = vec3(r, g, b);
    }

    vec3 get(int x, int y)
    {
        return pixels[y * width + x];
    }

    const int width;
    const int height;
    vector<vec3> pixels;
};