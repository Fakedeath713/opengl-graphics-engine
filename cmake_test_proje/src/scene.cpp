#include "scene.hpp"
#include "shadermanager.hpp"
#include "texturemanager.hpp"
#include <algorithm>
#include <fstream>
#include <nlohmann/json.hpp>
#include "shapecreator.hpp"
#include "iostream"
#include "glad/glad.h"
namespace graf
{
    Scene::Scene()
    {
        m_activeCamera = new Camera(90.0f, 1.0f, 0.2f, 100.0f);
        addCamera(m_activeCamera);

        m_alternativeCamera = new Camera(90.0f, 1.0f, 1.0f, 100.0f);
        m_alternativeCamera->getTransform()->position().x = 0.0f;
        m_alternativeCamera->getTransform()->position().y = 4.0f; 
        m_alternativeCamera->getTransform()->position().z = -8.0f;
        m_alternativeCamera->ViewMatrix();
        addCamera(m_alternativeCamera);

        std::ifstream file("./models/TextureTurningPyramid.json");

        using namespace nlohmann;
        auto data = json::parse(file);

        std::string TextureName = data["TextureName"].get<std::string>();

        std::string ShaderProgramName = data["ShaderProgramName"].get<std::string>();

        ShapeTypes  ShapeType=(ShapeTypes) data["ShapeType"].get<int>();
        m_pyramid = new Model();
        m_pyramid->setTextureName(TextureName);
        m_pyramid->setShaderProgramName(ShaderProgramName);
        m_pyramid->setVertexArrayObject(ShapeCreator::CreateShape(ShapeType));

        m_camCount = 2;
        m_currentCam = 0;
        m_modelCount = 0;
        m_currentModel = -1;


        TextureManager::addTextureFromFile("grass.jpg");
        TextureManager::addTextureFromFile("cobblestone.jpg");
        TextureManager::addTextureFromFile("sand.jpg");
        TextureManager::addTextureFromFile("gravel.jpg");
        TextureManager::addTextureFromFile("poker_kedi.jpg");
        TextureManager::addTextureFromFile("kedi.jpg");
    }
    void Scene::addModel(const std::string& fileName)
    {
        std::ifstream file("./models/" + fileName + ".json");

        using namespace nlohmann;
        auto data = json::parse(file);

        std::string ModelName = data["ModelName"].get<std::string>();

        std::string TextureName = data["TextureName"].get<std::string>();

        //without ".json"
        std::string ShaderProgramName = data["ShaderProgramName"].get<std::string>();

        // std::cout << ShaderProgramName << "\n";

        ShapeTypes  ShapeType=(ShapeTypes) data["ShapeType"].get<int>();

        glm::vec3 position;
        position.x = data["Position"][0].get<int>();
        position.y = data["Position"][1].get<int>();
        position.z = data["Position"][2].get<int>();

        glm::vec3 scale;
        scale.x = data["Scale"][0].get<int>();
        scale.y = data["Scale"][1].get<int>();
        scale.z = data["Scale"][2].get<int>();
        Model* model = new Model;

        model->setTextureName(TextureName);
        model->setShaderProgramName(ShaderProgramName);
        model->setVertexArrayObject(ShapeCreator::CreateShape(ShapeType));
        model->getTransform()->setPosition(position);
        model->getTransform()->setScale(scale);

        addModel(model);

    }
    void Scene::addModel(Model* model)
    {
        // std::cout << m_currentModel << std::endl;
        if(std::find(m_modelList.begin(),m_modelList.end(),model)==m_modelList.end())
        {
            std::string textureName = model->getTextureName();
            std::string shaderName = model->getShaderProgramName();
            TextureManager::addTextureFromFile(textureName);
            ShaderManager::addShaderFromFile(shaderName);
            m_modelList.push_back(model);
            m_modelCount++;
            if(m_modelCount == 1)
                m_currentModel = 0;
        }
        // std::cout << m_currentModel << std::endl;
    }
    void Scene::addCamera(Camera* camera)
    {
        if (std::find(m_cameraList.begin(), m_cameraList.end(), camera) == m_cameraList.end())
        {
            m_cameraList.push_back(camera);
            m_camCount++;
        }
    }
    void Scene::setActiveCamera(Camera* camera)
    {
        this->m_activeCamera = camera;
    }
    Camera* Scene::getActiveCamera()
    {
        return m_activeCamera;
    }
    CameraList& Scene::cameraList()
    {
        return this->m_cameraList;
    }
    void Scene::removeModel(Model* model)
    {
        auto it=std::find(m_modelList.begin(),m_modelList.end(),model);
        if(it!=m_modelList.end())
        {
            m_modelList.erase(it);
            m_modelCount--;
        }  
    }
    void Scene::render()
    {
        glViewport(0, 0, 1000, 1000);

        for(auto next:m_modelList)
        {
            next->draw(m_activeCamera->getProjection() * m_activeCamera->ViewMatrix());
        }
        m_pyramid->draw(m_activeCamera->getProjection() * m_activeCamera->ViewMatrix());
        for(auto next:m_cameraList)
        {
            next->getCameraModel()->draw(m_activeCamera->getProjection() * m_activeCamera->ViewMatrix());
        }
        glViewport(600, 600, 400, 400);
        for(auto next:m_modelList)
        {
            next->draw(m_alternativeCamera->getProjection() * m_alternativeCamera->ViewMatrix());
        }
        m_pyramid->draw(m_alternativeCamera->getProjection() * m_alternativeCamera->ViewMatrix());
        for(auto next:m_cameraList)
        {
            next->getCameraModel()->draw(m_alternativeCamera->getProjection() * m_alternativeCamera->ViewMatrix());
        }
        update();
        
        renderGui();
    }
    
    int& Scene::modelCount()
    {
        return this->m_modelCount;
    }
    int& Scene::currentModel()
    {
        return this->m_currentModel;
    }
    int& Scene::camCount()
    {
        return this->m_camCount;
    }
    int& Scene::currentCam()
    {
        return this->m_currentCam;
    }
    
}