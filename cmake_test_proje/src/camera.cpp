#include "camera.hpp"
#include "gtc/matrix_transform.hpp"
#include <iostream> //delete later
#include <glad/glad.h>

namespace graf
{
    Camera::Camera(float fov,
               float aspect,
               float near,
               float far)
    {
        transform = new Transform();
        m_mtxProject = glm::perspectiveLH(glm::radians(fov), aspect, near, far);
        m_fov = fov;
        m_aspect = aspect;
        m_near = near;
        m_far = far;
        m_model = Model::loadModelFromFile("TextureCam.json");
        m_model->setFillType(GL_LINE);
    }
    glm::mat4 Camera::getProjection()
    {
        return this->m_mtxProject;
    }
    void Camera::updateProjection()
    {
        m_mtxProject = glm::perspectiveLH(glm::radians(fov()), aspect(), near(), far());
    }
    Model* Camera::getCameraModel()
    {
        return m_model;
    }
    void Camera::turn(float angle)
    {
        auto euler = transform->Euler();
        euler.y += angle;
        transform->setEuler(euler);
    }
    void Camera::look(float angle)
    {
        auto euler = transform->Euler();
        euler.x += angle;
        transform->setEuler(euler);
    }
    Transform* Camera::getTransform()
    {
        return this->transform;
    }
    glm::mat4 Camera::ViewMatrix()
    {
        auto mtxInvTranslate = glm::translate(glm::mat4(1), -transform->position());
        auto mtxInvRotation  = glm::inverse(transform->rotationMatrix());

        m_model->getTransform()->setPosition(transform->position());
        m_model->getTransform()->setEuler(glm::vec3(transform->Euler().x - 90.0f, transform->Euler().y, transform->Euler().z));

        return mtxInvRotation * mtxInvTranslate;
    }

    float& Camera::fov()
    {
        return m_fov;
    }
    float& Camera::aspect()
    {
        return m_aspect;
    }
    float& Camera::near()
    {
        return m_near;
    }
    float& Camera::far()
    {
        return m_far;
    }
}