#pragma once
#include <memory>
#include <glm/glm.hpp>
#include "ray.h"
#include "film.h"
#include "camera.h"
#include "scene.h"
class Renderer
{
public:
    Renderer(int width, int height, int samples);

    void render();

    glm::vec3 traceRay(const Ray &ray, int depth);

    const std::unique_ptr<Film> &film() const
    {
        return m_film;
    }

    virtual void init() = 0;

protected:
    int m_width;
    int m_height;
    std::unique_ptr<Camera> m_camera;
    std::unique_ptr<Scene> m_scene;
    //    std::unique_ptr<class Integrator> mIntegrator;
    //    std::unique_ptr<class Sampler> mSampler;
    std::unique_ptr<Film> m_film;
    int m_samples_per_pixel;
};
