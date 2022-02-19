#include "renderer.h"
#include "film.h"
#include "../objects/sphere.h"
#include "../materials/lambertian.h"
#include "../materials/metal.h"
#include "../materials/dielectric.h"
#include "rng.h"
#include <omp.h>
Renderer::Renderer(int width, int height, int samples)
    : m_width(width), m_height(height), m_samples_per_pixel(samples)
{
     m_scene = std::make_unique<Scene>();
     m_film = std::make_unique<Film>(width, height);
}

void Renderer::render()
{
    init();
    auto &width = m_film->width;
    auto &height = m_film->height;
#pragma omp parallel for
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            vec3 color;
            for (int s = 0; s < m_samples_per_pixel; s++)
            {
                auto u = (i + RNG::random_double()) / (float)width;
                auto v = (j + RNG::random_double()) / (float)height;
                auto ray = m_camera->getRay(u, v);
                color += traceRay(ray, 10);
            }
            color /= (float)m_samples_per_pixel;
            color = glm::clamp(color, vec3(0.0f), vec3(1.0f));
            m_film->set(i, j, color);
        }
    }
}

glm::vec3 Renderer::traceRay(const Ray &ray, int depth)
{
    HitRecord rec;
    if (depth <= 0)
    {
        return vec3(0, 0, 0);
    }
    auto hit = m_scene->hit(ray, 0.001f, std::numeric_limits<float>::max(), rec);
    if (hit)
    {
        Ray scattered;
        glm::vec3 attenuation;

        if (rec.material->scatter(ray, rec, attenuation, scattered))
        {

            return attenuation * traceRay(scattered, depth - 1);
        }
        // return 0.5f * glm::vec3(rec.normal.x + 1, rec.normal.y + 1, rec.normal.z + 1);
        return vec3(0, 0, 0);
    }
    auto dir = ray.direction;
    auto t = 0.5f * (dir.y + 1.0f);
    return (1.0f - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}
