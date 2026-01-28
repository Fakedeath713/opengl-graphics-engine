
#include "texturemanager.hpp"
#include <glad/glad.h>
#include <stb_image.h>
namespace graf
{
    TextureManager* TextureManager::m_instance = nullptr;


    TextureManager::TextureManager(){}
    TextureManager* TextureManager::getInstance()
    {
        if(m_instance == nullptr)
            m_instance = new TextureManager();

        return m_instance;
    }

    void TextureManager::addTextureFromFile(const std::string& filename)
    {
        auto manager = getInstance();
        std::string fullFileName = "./images/" + filename;
        //if the texture was added before, then it will do nothing.
        if(manager->m_textureMap.count(fullFileName) > 0)
        {
            return ;
        }

        int width, height, channels;
        unsigned char* data;
        unsigned int texture;

        stbi_set_flip_vertically_on_load(true);

        data = stbi_load(fullFileName.data(), &width, &height, &channels, 0);
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);


        stbi_image_free(data);

        manager->m_textureMap[filename] = texture;
    }

    void TextureManager::activateTexture(const std::string& filename)
    {
        auto manager = getInstance();

        //if the texture was not added before this function is called, then it will do nothing.
        if(manager->m_textureMap.count(filename) == 0)
        {
            return ;
        }

        unsigned int id = manager->m_textureMap[filename];

        glBindTexture(GL_TEXTURE_2D, id);
    }
}