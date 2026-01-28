#include "shadermanager.hpp"
#include <fstream>
#include "shaderprogram.hpp"
#include <nlohmann/json.hpp>
#include <iostream>
#include "glad/glad.h"
namespace graf
{
    ShaderManager* ShaderManager::m_instance = nullptr;

    ShaderManager::ShaderManager(){}

    ShaderManager* ShaderManager::getInstance()
    {
        if(m_instance == nullptr)
            m_instance = new ShaderManager();

        return m_instance;
    }

    void ShaderManager::addShaderFromFile(const std::string& fileName)
    {
        auto manager = getInstance();
        if(manager->m_shaderMap.count(fileName) == 0)
        {
            std::string path = "./shaders/" + fileName + "/";
            // std::cout << path << "settings.json" << "\n";
            std::ifstream file(path + "settings.json");
            
            using namespace nlohmann;
            auto data = json::parse(file);
            // std::cout << data.dump(4) << std::endl;


            std::string programName = data["ProgramName"].get<std::string>();
            std::string vertexShader = data["VertexShader"].get<std::string>();
            std::string fragmentShader = data["FragmentShader"].get<std::string>();
            
            ShaderProgram* program = new ShaderProgram();
            program->create();
            program->attachShader(path + vertexShader,GL_VERTEX_SHADER);
            program->attachShader(path + fragmentShader,GL_FRAGMENT_SHADER);
            program->link();

            auto uniform = data["Uniforms"];

            for(auto next:uniform)
            {
                std::string varName =  next["Name"].get<std::string>();
                program->addUniform(varName);
            }

            manager->m_shaderMap[fileName] = program;
        }
    }
    ShaderProgram* ShaderManager::getProgram(const std::string& fileName)
    {
        auto manager = getInstance();
        if(manager->m_shaderMap.count(fileName) > 0)
            return manager->m_shaderMap[fileName];
        return nullptr;
    }
}