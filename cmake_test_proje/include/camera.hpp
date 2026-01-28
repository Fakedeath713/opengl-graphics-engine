#ifndef Camera_hpp
#define Camera_hpp
#include "transform.hpp"
#include "glm.hpp"
#include "model.hpp"
namespace graf
{
    class Camera
    {
    public:
        Camera(float fov = 90.0f,
            float aspect = 1.0f,
            float near = 1.0f,
            float far = 100.0f
            );
        void turn(float angle);
        void look(float angle);
        Transform* getTransform();
        glm::mat4  ViewMatrix();
        glm::mat4 getProjection();
        void updateProjection();
        Model* getCameraModel();
        float& fov();
        float& aspect();
        float& near();
        float& far();
    private:
        Transform* transform;
        float m_fov;
        float m_aspect;
        float m_near;
        float m_far;
        glm::mat4 m_mtxProject;
        Model* m_model;
    };
    using CameraList = std::vector<Camera*>;
}

#endif