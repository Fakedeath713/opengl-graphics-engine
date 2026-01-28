#ifndef texturemanager_hpp
#define texturemanager_hpp
#include <string>           // ADD THIS LINE
#include <unordered_map>    // Make sure this is also included
#include <glad/glad.h>      // For OpenGL types
#define  STB_IMAGE_IMPLEMENTATION
namespace graf
{
    class TextureManager
    {
        public:
        static void addTextureFromFile(const std::string& filename);
        static void activateTexture(const std::string& filename);

        private:

        TextureManager();
        static TextureManager* m_instance;
        static TextureManager* getInstance();

        std::unordered_map<std::string, unsigned int> m_textureMap;
    };
}

#endif