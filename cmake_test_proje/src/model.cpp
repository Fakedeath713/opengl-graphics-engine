#include "model.hpp"
#include "transform.hpp"
#include "shadermanager.hpp"
#include "shaderprogram.hpp"
#include "texturemanager.hpp"
#include "shapecreator.hpp"
#include "vertexarrayobject.hpp"
#include "nlohmann/json.hpp"
#include <glad/glad.h>

namespace graf
{
    Model::Model()
    {
        //use this
        m_filltype = GL_FILL;

        m_transform = new Transform();

        m_textureName = "";
        m_programName = "";
        m_textureRepeat = glm::vec2(1.0f, 1.0f);
    }
    Model* Model::loadModelFromFile(const std::string& fileName)
    {
        std::ifstream file("./models/" + fileName);

        using namespace nlohmann;
        auto data = json::parse(file);

        std::string ModelName=data["ModelName"].get<std::string>();

        std::string TextureName=data["TextureName"].get<std::string>();

        std::string ShaderProgramName=data["ShaderProgramName"].get<std::string>();

        ShapeTypes  ShapeType=(ShapeTypes) data["ShapeType"].get<int>();

        Model* model = new Model;

        model->setTextureName(TextureName);
        model->setShaderProgramName(ShaderProgramName);
        model->setVertexArrayObject(ShapeCreator::CreateShape(ShapeType));
        return model;
    }
    void Model::setShaderProgramName(const std::string& programFileName)
    {
        m_programName = programFileName;
    }
    std::string Model::getShaderProgramName()
    {
        return this->m_programName;
    }
    void Model::setTextureName(const std::string& fileName)
    {
        m_textureName = fileName;
    }
    std::string Model::getTextureName()
    {
        return this->m_textureName;
    }
    Transform* Model::getTransform()
    {
        return this->m_transform;
    }
    void Model::setVertexArrayObject(VertexArrayObject* vao)
    {
        m_vao = vao;
        return;
    }
    VertexArrayObject* Model::getVertexArrayObject()
    {
        return this->m_vao;
    }

    glm::vec2& Model::getTextureRepeat()
    {
        return m_textureRepeat;
    }
    void Model::setTextureRepeat(glm::vec2 textureRepeat)
    {
        m_textureRepeat = textureRepeat;
    }
    void Model::setFillType(unsigned int filltype)
    {
        this->m_filltype = filltype;
    }
    void Model::draw(const glm::mat4& mtxTransform)
    {
        TextureManager::activateTexture(getTextureName());
        auto program = ShaderManager::getProgram(getShaderProgramName());
        program->use();
        glm::mat4 temp = mtxTransform * getTransform()->Matrix();
        program->setMat4("uWorldTransform", temp);
        program->setVec2("uTextureRepeat", m_textureRepeat);
        glPolygonMode(GL_FRONT_AND_BACK, m_filltype);
        getVertexArrayObject()->bind();
        getVertexArrayObject()->draw();
        getVertexArrayObject()->unbind();
        program->unuse();
    }
}