#ifndef shaderprogram_hpp
#define shaderprogram_hpp
#include <iostream>
#include <string>
#include <fstream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <glm.hpp>
namespace graf
{
    class ShaderProgram
    {
        public:
        void create();
        void attachShader(const std::string& filename, unsigned int shadertype);
        void link();
        void use();
        void unuse();

        void addUniform(const std::string& varName);
        void setMat4(const std::string& varName, glm::mat4& value);
        void setVec4(const std::string& varName, glm::vec4& value);
        void setVec3(const std::string& varName, glm::vec3& value);
        void setVec2(const std::string& varName, glm::vec2& value);
        void setFloat(const std::string& varName, float value);
        private:
        std::string getFileData(const std::string& filename);
        unsigned int m_pid;

        std::unordered_map<std::string, int> m_uniforms;
    };
}

#endif