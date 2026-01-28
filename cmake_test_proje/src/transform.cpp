#define GLM_ENABLE_EXPERIMENTAL
#include "gtx/euler_angles.hpp"
#include "transform.hpp"
#include <iostream>
namespace graf
{
    Transform::Transform()
    {
        m_position     = glm::vec3(0.0f);
        m_euler        = glm::vec3(0.0f);
        m_scale        = glm::vec3(1.0f);

        m_mtxRotation  = glm::mat4(1.0f);
        m_mtxScale     = glm::mat4(1.0f);
        m_mtxWorld     = glm::mat4(1.0f);

        m_mtxTranslate = glm::mat4(1.0f);
    }

    void Transform::update()
    {
        //std::cout << m_position.x << " " << m_position.y << " " << m_position.z << std::endl;
        m_mtxTranslate = glm::translate(glm::mat4(1.0f), m_position);
        m_mtxWorld = m_mtxTranslate * m_mtxRotation * m_mtxScale;
    }
    
    glm::vec3& Transform::position()
    {
        return m_position;
    }
    glm::vec3& Transform::Euler()
    {
        return m_euler;
    }
    glm::vec3& Transform::Scale()
    {
        return m_scale;
    }
    void Transform::setEuler(const glm::vec3& euler)
    {
        m_euler = euler;
        m_mtxRotation = glm::mat4(1);
        float radX =  glm::radians(euler.x);
        float radY =  glm::radians(euler.y);
        float radZ =  glm::radians(euler.z);

        auto Right   = glm::vec3(1.0f,0.0f,0.0f);
        auto Up      = glm::vec3(0.0f,1.0f,0.0f);
        auto Look    = glm::vec3(0.0f,0.0f,1.0f);

        glm::mat4 mtxRotZ = glm::rotate(glm::mat4(1),radZ,Look);

        Right      = mtxRotZ*glm::vec4(Right,0.0f);
        Up         = mtxRotZ*glm::vec4(Up,0.0f);
      
        if(radY)
        {
            glm::mat4 mtxRotY = glm::rotate(glm::mat4(1),radY,Up);

            Right    = mtxRotY*glm::vec4(Right,0.0f);
            Look     = mtxRotY*glm::vec4(Look,0.0f);
        }

        if(radX)
        {
            glm::mat4 mtxRotX = glm::rotate(glm::mat4(1),radX,Right);

            Look    = mtxRotX*glm::vec4(Look,0.0f);
            Up      = mtxRotX*glm::vec4(Up,0.0f);

        }
        Right    = glm::normalize(Right);
        Up       = glm::normalize(Up);
        Look     = glm::normalize(Look);
        
        m_mtxRotation[0] = glm::vec4(Right,0.0f);
        m_mtxRotation[1] = glm::vec4(Up,0.0f);
        m_mtxRotation[2] = glm::vec4(Look,0.0f);
        
        update();
    
    }
    void Transform::RotateLocalX(float angle)
    {
        float radX = glm::radians(angle);
        glm::vec3 normX = glm::normalize(Right());
        glm::mat4 rotX = glm::rotate(glm::mat4(1.0f), radX, normX);
        
        glm::vec3 look = glm::normalize(Look());
        glm::vec3 up = glm::normalize(Up());
        //added 0 instead of 1 because its not a point but a vector.
        look  = rotX * glm::vec4(look, 0.0f);
        up    = rotX * glm::vec4(up, 0.0f);

        look = glm::normalize(look);
        up   = glm::normalize(up);

        m_mtxRotation[2][0] = look.x;
        m_mtxRotation[2][1] = look.y;
        m_mtxRotation[2][2] = look.z;
        m_mtxRotation[1][0] = up.x;
        m_mtxRotation[1][1] = up.y;
        m_mtxRotation[1][2] = up.z;
        
        update();
    }

    void Transform::RotateLocalY(float angle)
    {
        float radY = glm::radians(angle);
        glm::vec3 normY = glm::normalize(Up());
        glm::mat4 rotY = glm::rotate(glm::mat4(1.0f), radY, normY);
        
        glm::vec3 look = glm::normalize(Look());
        glm::vec3 right = glm::normalize(Right());
        //added 0 instead of 1 because its not a point but a vector.
        look  = rotY * glm::vec4(look, 0.0f);
        right = rotY * glm::vec4(right, 0.0f);

        look = glm::normalize(look);
        right = glm::normalize(right);

        m_mtxRotation[2][0] = look.x;
        m_mtxRotation[2][1] = look.y;
        m_mtxRotation[2][2] = look.z;
        m_mtxRotation[0][0] = right.x;
        m_mtxRotation[0][1] = right.y;
        m_mtxRotation[0][2] = right.z;
        
        update();
    }

    void Transform::RotateLocalZ(float angle)
    {
        float radZ = glm::radians(angle);
        glm::vec3 normZ = glm::normalize(Look());
        glm::mat4 rotZ = glm::rotate(glm::mat4(1.0f), radZ, normZ);
        
        glm::vec3 right = glm::normalize(Right());
        glm::vec3 up = glm::normalize(Up());
        //added 0 instead of 1 because its not a point but a vector.
        right  = rotZ * glm::vec4(right, 0.0f);
        up = rotZ * glm::vec4(up, 0.0f);

        right = glm::normalize(right);
        up = glm::normalize(up);

        m_mtxRotation[0][0] = right.x;
        m_mtxRotation[0][1] = right.y;
        m_mtxRotation[0][2] = right.z;
        m_mtxRotation[1][0] = up.x;
        m_mtxRotation[1][1] = up.y;
        m_mtxRotation[1][2] = up.z;
        
        update();
    }
    
    void Transform::MoveForward()
    {
        m_position += glm::vec3(glm::normalize(Look()).x / 4, glm::normalize(Look()).y / 4, glm::normalize(Look()).z / 4);
        update();
    }

    void Transform::MoveBackward()
    {
        m_position -= glm::vec3(glm::normalize(Look()).x / 4, glm::normalize(Look()).y / 4, glm::normalize(Look()).z / 4);
        update();
    }
    void Transform::MoveRight()
    {
        m_position += glm::vec3(glm::normalize(Right()).x / 4, glm::normalize(Right()).y / 4, glm::normalize(Right()).z / 4);
        update();
    }
    void Transform::MoveLeft()
    {
        m_position -= glm::vec3(glm::normalize(Right()).x / 4, glm::normalize(Right()).y / 4, glm::normalize(Right()).z / 4);
        update();
    }
    void Transform::MoveUp()
    {
        m_position += glm::vec3(glm::normalize(Up()).x / 4, glm::normalize(Up()).y / 4, glm::normalize(Up()).z / 4);
        update();
    }
    void Transform::MoveDown()
    {
        m_position -= glm::vec3(glm::normalize(Up()).x / 4, glm::normalize(Up()).y / 4, glm::normalize(Up()).z / 4);
        update();
    }
    glm::vec3 Transform::Look()
    {
        return glm::vec3(m_mtxRotation[2][0], m_mtxRotation[2][1], m_mtxRotation[2][2]);
    }
    glm::vec3 Transform::Up()
    {
        return glm::vec3(m_mtxRotation[1][0], m_mtxRotation[1][1], m_mtxRotation[1][2]);
    }
    glm::vec3 Transform::Right()
    {
        return glm::vec3(m_mtxRotation[0][0], m_mtxRotation[0][1], m_mtxRotation[0][2]);
    }

    glm::mat4 Transform::Matrix()
    {
        return m_mtxWorld;
    }
    glm::mat4 Transform::rotationMatrix()
    {
        return m_mtxRotation;
    }

    void Transform::setScale(const glm::vec3& scale)
    {
        m_scale = scale;
        m_mtxScale = glm::scale(glm::mat4(1.0f), m_scale);
        update();
    }
    void Transform::setPosition(const glm::vec3& position)
    {
        m_position = position;
        m_mtxTranslate = glm::translate(glm::mat4(1.0f), m_position);
        update();
    }
}