#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
class Transform
{
public:
    Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
        : position(position), rotation(rotation), scale(scale)
    {
        updateModelMatrix();
    }

    glm::vec3 getPosition() const
    {
        return position;
    }
    glm::vec3 getRotation() const
    {
        return glm::eulerAngles(rotation) * glm::pi<float>() / 180.0f;
    }
    glm::vec3 getScale() const
    {
        return scale;
    }

    void setPosition(glm::vec3 position)
    {
        this->position = position;
        updateModelMatrix();
    }
    void setRotation(glm::vec3 rotation)
    {
        this->rotation = rotation;
        updateModelMatrix();
    }
    void setScale(glm::vec3 scale)
    {
        this->scale = scale;
        updateModelMatrix();
    }

    void updateModelMatrix()
    {
        glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f), position);
        glm::mat4 rotateMatrix = glm::toMat4(rotation);
        glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0), scale);

        modelMatrix = translateMatrix * rotateMatrix * scaleMatrix;
        inverseModelMatrix = glm::inverse(modelMatrix);
    }

    glm::mat4 getModelMatrix() const
    {
        return modelMatrix;
    }

    glm::mat4 getInverseModelMatrix() const
    {
        return inverseModelMatrix;
    }

private:
    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scale;
    glm::mat4 modelMatrix;
    glm::mat4 inverseModelMatrix;
};