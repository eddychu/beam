#pragma once
#include "../core/renderer.h"
#include "../materials/lambertian.h"
#include "../materials/metal.h"
#include "../materials/dielectric.h"
#include "../objects/sphere.h"
class Example1 : public Renderer
{
public:
    Example1(int width, int height, int samples)
        : Renderer(width, height, samples)
    {
    }

    void init() override {

        m_camera = std::make_unique<Camera>(glm::vec3(13, 2, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), 20, (float)m_width / (float)m_height, 0.1f, 1000.0f);
        auto groundMaterial = std::make_shared<Lambertian>(vec3(0.5, 0.5, 0.5));



        m_scene->add(std::make_shared<Sphere>(vec3(0, -1000, 0), 1000, groundMaterial));

        for (int a = -11; a< 11; a++) {
            for (int b = -11; b < 11; b++) {
                auto choose_mat = RNG::random_double();
                vec3 center(a + 0.9 * RNG::random_double(), 0.2, b + 0.9 * RNG::random_double());

                if((center - vec3(4, 0.2, 0)).length() > 0.9) {
                    std::shared_ptr<Material> sphereMaterial;
                    if(choose_mat < 0.8) {
                        auto albedo = vec3(RNG::random_double() * RNG::random_double(),
                                           RNG::random_double() * RNG::random_double(),
                                           RNG::random_double() * RNG::random_double());
                        sphereMaterial = std::make_shared<Lambertian>(albedo);
                    } else if(choose_mat < 0.95) {
                        auto albedo = vec3(0.5 * (1 + RNG::random_double()),
                                           0.5 * (1 + RNG::random_double()),
                                           0.5 * (1 + RNG::random_double()));
                        sphereMaterial = std::make_shared<Metal>(albedo, 0.5 * RNG::random_double());
                        
                    } else {
                        sphereMaterial = std::make_shared<Dielectric>(1.5);
                    }

                    m_scene->add(std::make_shared<Sphere>(center, 0.2, sphereMaterial));
                }
            }
        }

        auto material1 = std::make_shared<Dielectric>(1.5);
        m_scene->add(std::make_shared<Sphere>(vec3(0, 1, 0), 1.0, material1));

        auto material2 = std::make_shared<Lambertian>(vec3(0.4, 0.2, 0.1));
        m_scene->add(std::make_shared<Sphere>(vec3(-4, 1, 0), 1.0, material2));

        auto material3 = std::make_shared<Metal>(vec3(0.7, 0.6, 0.5), 0.0);
        m_scene->add(std::make_shared<Sphere>(vec3(4, 1, 0), 1.0, material3));
    }
};



    
