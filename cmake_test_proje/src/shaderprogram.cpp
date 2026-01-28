#include "shaderprogram.hpp"
namespace graf
{
    void ShaderProgram::create()
    {
        m_pid = glCreateProgram();
    }
    void ShaderProgram::attachShader(const std::string& filename, unsigned int shadertype)
    {
        unsigned int shaderId = glCreateShader(shadertype);

        std::string src = getFileData(filename);
        const char* sourceTemp = &src[0];
        glShaderSource(shaderId, 1, &sourceTemp, NULL);

        glCompileShader(shaderId);

        GLint isCompiled = 0;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);

        if(isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);
            char*  errorLog = new char[maxLength];

            glGetShaderInfoLog(shaderId, maxLength, &maxLength, &errorLog[0]);
            std::cout << "shaderError:" << errorLog << std::endl;

            glDeleteShader(shaderId); 
            delete[] errorLog;
            return;
        }
        glAttachShader(m_pid,shaderId);
    }
    void ShaderProgram::link()
    {
        glLinkProgram(m_pid);
    }
    void ShaderProgram::use()
    {
        glUseProgram(m_pid);
    }
    void ShaderProgram::unuse()
    {
        glUseProgram(0);
    }
    std::string ShaderProgram::getFileData(const std::string& filename)
    {
        std::ifstream file(filename);
        std::string data;

        if(file.is_open())
        {
            char readChar;

            while((readChar = file.get()) != EOF)
                data += readChar;
            
            file.close();
        }
        return data;
    }
    void ShaderProgram::addUniform(const std::string& varname)
    {
        m_uniforms[varname] = glGetUniformLocation(m_pid, varname.data());
    }

    void ShaderProgram::setMat4(const std::string& varname, glm::mat4& value)
    {
        if(m_uniforms.count(varname) > 0)
            glUniformMatrix4fv(m_uniforms[varname], 1, false, &value[0][0]);
    }        

    void ShaderProgram::setVec4(const std::string& varname, glm::vec4& value)
    {
        if(m_uniforms.count(varname) > 0)
            glUniform4f(m_uniforms[varname], value.r, value.g, value.b, value.a);
    }
     
    void ShaderProgram::setVec3(const std::string& varname, glm::vec3& value)
    {
        if(m_uniforms.count(varname) > 0)
            glUniform3f(m_uniforms[varname], value.x, value.y, value.z);
    }
    void ShaderProgram::setVec2(const std::string& varname, glm::vec2& value)
    {
        if(m_uniforms.count(varname) > 0)
            glUniform2f(m_uniforms[varname], value.x, value.y);
    }
    void ShaderProgram::setFloat(const std::string& varname, float value)
    {
        if(m_uniforms.count(varname) > 0)
            glUniform1f(m_uniforms[varname], value);
    }
}