#ifndef transform_hpp
#define transform_hpp
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
namespace graf
{
    class Transform
    {
    public:
        Transform();
        //get pos vector
        glm::vec3& position();
        //get euler vector
        glm::vec3& Euler();
        //get scale vector
        glm::vec3& Scale();

        void setEuler(const glm::vec3& euler);
        void setPosition(const glm::vec3& position);
        void setScale(const glm::vec3& scale);

        //get world matrix
        glm::mat4 Matrix();
        //get rotation matrix
        glm::mat4 rotationMatrix();

        void MoveForward();
        void MoveBackward();
        void MoveRight();
        void MoveLeft();
        void MoveUp();
        void MoveDown();

        void RotateLocalX(float angle);
        void RotateLocalY(float angle);
        void RotateLocalZ(float angle);
        //returns the z axis from the rotation matrix
        glm::vec3 Look();
        //returns the y axis from the rotation matrix
        glm::vec3 Up();
        //returns the y axis from the rotation matrix
        glm::vec3 Right();
        //updating the world matrix
        void update();


    private:
        glm::vec3 m_position;
        glm::vec3 m_euler;
        glm::vec3 m_scale;
        //all rotations
        glm::mat4 m_mtxTranslate;
        glm::mat4 m_mtxRotation;
        glm::mat4 m_mtxScale;
    
        glm::mat4 m_mtxWorld;
    };
}

#endif