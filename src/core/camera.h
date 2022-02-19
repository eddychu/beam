#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "ray.h"
#include "transform.h"
class Camera
{
public:
    Camera(const vec3 &eye,
           const vec3 &lookat,
           const vec3 &up,
           float fov,
           float aspect,
           float near,
           float far
           )
        : m_fov(glm::radians(fov)), m_aspect(aspect), m_eye(eye)
    {
        viewMatrix = glm::lookAt(eye, lookat, up);
        iviewMatrix = glm::inverse(viewMatrix);
    }
    /**
     * @brief Get the Ray object
     *
     * @param x screen coordinate x [0, 1.0]
     * @param y screen coordinate y [0, 1.0]
     * @return Ray
     */

    Ray getRay(float screenX, float screenY) const
    {
        auto halfH = tan(m_fov / 2.0f);
        auto halfW = halfH * m_aspect;
        auto viewX = (screenX - 0.5f) * 2.0f * halfW;
        auto viewY = (0.5f - screenY) * 2.0f * halfH;
        auto dirInCameraSpace = normalize(vec3(viewX, viewY, -1.0f));
        vec3 origin = iviewMatrix * vec4(0, 0, 0, 1);
        auto dirInWorldSpace = iviewMatrix * vec4(dirInCameraSpace, 0.0f);
        return Ray(origin, normalize(vec3(dirInWorldSpace)));
    }

private:
    float m_fov;
    float m_aspect;
    glm::vec3 m_eye;
    glm::mat4 viewMatrix;
    glm::mat4 iviewMatrix;
};
