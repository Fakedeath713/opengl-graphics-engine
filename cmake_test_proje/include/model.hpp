#ifndef Model_hpp
#define Model_hpp
#include "glm.hpp"
#include <string>
#include <vector>

namespace graf
{
    class Transform;
    class VertexArrayObject;
    class ShaderProgram;
    class Model
    {
    public:
        Model();
        static Model* loadModelFromFile(const std::string& name);
        
        Transform* getTransform();

        void setShaderProgramName(const std::string& name);
        std::string getShaderProgramName();

        void setTextureName(const std::string& name);
        std::string getTextureName();

        void setVertexArrayObject(VertexArrayObject* vao);
        VertexArrayObject* getVertexArrayObject();

        glm::vec2& getTextureRepeat();
        void setTextureRepeat(glm::vec2 textureRepeat);
        
        void setFillType(unsigned int filltype);

        void draw(const glm::mat4& mtxTransform);
    private:
        //use
        glm::vec2 m_textureRepeat;
        unsigned int m_filltype;
        std::string  m_textureName;
        std::string m_programName;
        Transform* m_transform;
        VertexArrayObject* m_vao;
    };
    using ModelList = std::vector<Model*>;
}

#endif