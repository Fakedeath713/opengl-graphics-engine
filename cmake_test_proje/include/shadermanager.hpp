#ifndef shadermanager_hpp
#define shadermanager_hpp
#include <string>
#include <unordered_map>
namespace graf
{
    class ShaderProgram;
    class ShaderManager
    {
    public:
    static void addShaderFromFile(const std::string& fileName);
    static ShaderProgram* getProgram(const std::string& shaderFileName);
    private:

        ShaderManager();
        
        static ShaderManager* m_instance;
        static ShaderManager* getInstance();

        std::unordered_map<std::string, ShaderProgram*> m_shaderMap;
    };
}

#endif