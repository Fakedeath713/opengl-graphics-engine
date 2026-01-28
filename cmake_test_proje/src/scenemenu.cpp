#include "scene.hpp"
#include "imgui.h"
#include <string>
#include <iostream>
#include "transform.hpp"
#include <vector>
#include "camera.hpp"
#include <cmath>
namespace graf
{
    std::vector<std::string> textures = { "cobblestone.jpg", "grass.jpg", "gravel.jpg", "kedi.jpg", "poker_kedi.jpg", "sand.jpg"};

    std::vector<std::string> shapeTypesVector      = {"Square", "Circle", "Cube", "Pyramid", "Frustum", "Cylinder"};
    std::vector<ShapeTypes> shapeTypesCreateVector = {ShapeTypes::Square, ShapeTypes::Circle, ShapeTypes::Cube, ShapeTypes::Pyramid, ShapeTypes::Frustum, ShapeTypes::Cylinder};

    
    int updateShapeTypeIndex = 0;
    glm::vec3 updatePosition = glm::vec3(0.0f);
    glm::vec3 updateEuler    = glm::vec3(0.0f);
    glm::vec3 updateScale    = glm::vec3(1.0f);
    
    glm::vec3 updateEulerForCamera = glm::vec3(0.0f);

    int shapeTypeIndex = 0;
    int textureIndex   = 0;
    glm::vec2 textureRepeat = glm::vec2(1.0f);

    //camera
    float fov    = 90.0f;
    float near   = 1.0f;
    float far    = 10.0f;
    float width  = 1000.0f;
    float height = 1000.0f;

    void Scene::renderGui()
    {
        ImGui::Begin("Update");
        //if you don't want the id to show up in menu,
        //you need to write "##" before the id
        ImGui::Text("Model Selection");
        if(ImGui::SliderInt("CurrentModel", &currentModel(), 0, modelCount() - 1))
        {
            updatePosition = m_modelList[currentModel()]->getTransform()->position();
            updateEuler = m_modelList[currentModel()]->getTransform()->Euler();
            updateScale = m_modelList[currentModel()]->getTransform()->Scale();
        }
        static const char* shapeCurrentUpdate = shapeTypesVector[0].c_str();
        if(ImGui::BeginCombo("ShapeUpdate", shapeCurrentUpdate))
        {
            for(int i = 0; i < shapeTypesVector.size(); i++)
            {
                bool is_selected = (shapeCurrentUpdate == shapeTypesVector[i]);
                if(ImGui::Selectable(shapeTypesVector[i].c_str(), is_selected))
                {
                    shapeCurrentUpdate = shapeTypesVector[i].c_str();
                    m_modelList[currentModel()]->setVertexArrayObject(ShapeCreator::CreateShape(shapeTypesCreateVector[i]));
                }
                if(is_selected)
                    ImGui::SetItemDefaultFocus();
            }
        ImGui::EndCombo();
        }
        ImGui::Separator();

        ImGui::Text("Texture Selection");
        ImGui::SliderFloat2("TextureRepeatUpdate", &m_modelList[currentModel()]->getTextureRepeat().x, 0.0f, 10.0f);
        
        if(ImGui::SliderFloat3("ModelPositionUpdate", &updatePosition.x, -30.0f, 30.0f))
            m_modelList[currentModel()]->getTransform()->setPosition(updatePosition);
        if(ImGui::SliderFloat3("ModelRotationUpdate", &updateEuler.x, 0.0f, 360.0f))
            m_modelList[currentModel()]->getTransform()->setEuler(updateEuler);
        if(ImGui::SliderFloat3("ModelScaleUpdate",    &updateScale.x, 0.5f, 10.0f))
            m_modelList[currentModel()]->getTransform()->setScale(updateScale);

            

        static const char* current = textures[0].c_str();
        if(ImGui::BeginCombo("TextureUpdate", current))// The second parameter is the label previewed before opening the combo.
        {
            for(int i = 0; i < textures.size(); i++)
            {
                bool is_selected = (current == textures[i]);
                if(ImGui::Selectable(textures[i].c_str(), is_selected))
                {
                    current = textures[i].c_str();
                    m_modelList[currentModel()]->setTextureName(textures[i]);
                }
                if(is_selected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }
        ImGui::EndCombo();
        }
        ImGui::Separator();


        ImGui::Text("Camera Selection");
        if(ImGui::SliderInt("CurrentCamera", &currentCam(), 0, camCount() - 1))
        {
            setActiveCamera(cameraList()[currentCam()]);
        }
        ImGui::Separator();


        ImGui::Text("Camera Transform");
        ImGui::SliderFloat3("CameraPositionsUpdate", &m_activeCamera->getTransform()->position().x, -40.0f, 40.0f);
        if(ImGui::SliderFloat3("CameraRotationsUpdate", &updateEulerForCamera.x, 0.0f, 360.0f))
            m_activeCamera->getTransform()->setEuler(updateEulerForCamera);
        ImGui::Separator();


        ImGui::Text("Camera Model");
        if(ImGui::SliderFloat("CameraFovUpdate",   &m_activeCamera->fov(), 50.0f, 150.0f))
            m_activeCamera->updateProjection();
        if(ImGui::SliderFloat("CameraRatioUpdate", &m_activeCamera->aspect(), 0.5f, 2.0f))
            m_activeCamera->updateProjection();
        if(ImGui::SliderFloat("CameraNearUpdate",  &m_activeCamera->near(), 0.2f, 3.0f))
            m_activeCamera->updateProjection();
        if(ImGui::SliderFloat("CameraFarUpdate",   &m_activeCamera->far(), 10.0f, 200.0f))
            m_activeCamera->updateProjection();
        ImGui::End();
        
        

        ImGui::Begin("Create");
            ImGui::Text("Model Creation");
            static const char* shapeCurrentCreate = shapeTypesVector[0].c_str();
            if(ImGui::BeginCombo("ShapeCreate", shapeCurrentCreate))
            {
                for(int i = 0; i < shapeTypesVector.size(); i++)
                {
                    bool is_selected = (shapeCurrentCreate == shapeTypesVector[i]);
                    if(ImGui::Selectable(shapeTypesVector[i].c_str(), is_selected))
                    {
                        shapeCurrentCreate = shapeTypesVector[i].c_str();
                        shapeTypeIndex = i;
                    }
                    if(is_selected)
                        ImGui::SetItemDefaultFocus();
                }
            ImGui::EndCombo();
            }




            static const char* textureCurrentCreate = textures[0].c_str();
            if(ImGui::BeginCombo("TextureCreate", textureCurrentCreate))
            {
                for(int i = 0; i < textures.size(); i++)
                {
                    bool is_selected = (textureCurrentCreate == textures[i].c_str());
                    if(ImGui::Selectable(textures[i].c_str(), is_selected))
                    {
                        textureCurrentCreate = textures[i].c_str();
                        textureIndex = i;
                    }
                    if(is_selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }

            ImGui::SliderFloat2("TextureRepeatCreate", &textureRepeat.x, 0.0f, 10.0f);

            if(ImGui::Button("Create"))
            {
                Model* model = new Model();
                model->setVertexArrayObject(ShapeCreator::CreateShape(shapeTypesCreateVector[shapeTypeIndex]));
                model->setTextureName(textures[textureIndex]);
                model->setTextureRepeat(textureRepeat);
                model->setShaderProgramName("TextureShader");
                addModel(model);
            }
            ImGui::Separator();
            ImGui::Text("Camera Creation");
            ImGui::SliderFloat("CameraFovCreate", &fov, 50.0f, 150.0f); //fov
            ImGui::SliderFloat("CameraNearCreate", &near, 0.2f, 3.0f); //near
            ImGui::SliderFloat("CameraFarCreate", &far, 10.0f, 200.0f); //far
            ImGui::SliderFloat("CameraWidthCreate", &width, 500.0f, 1000.0f); //width
            ImGui::SliderFloat("CameraHeightCreate", &height, 500.0f, 1000.0f); //height
            if(ImGui::Button("Create Camera"))
            {
                Camera* camera =  new Camera(fov, (width / height), near, far);
                camera->ViewMatrix();
                addCamera(camera);
            }
        ImGui::End();
    }


    void Scene::update()
    {
        static float angle = 0.0f;       // For rotation (degrees)
        static float frameCount = 0.0f; // For simulating time in frames

        // Target position (assume currentModel is the target model index)
        Model* targetModel = m_modelList[currentModel()];
        glm::vec3 targetPosition = targetModel->getTransform()->position();

        // Animate the pyramid
         // Index or pointer to your pyramid
        angle += 0.08f;  // Increment angle for spinning (1 degree per frame)
        if (angle >= 360.0f) angle -= 360.0f; // Keep angle in [0, 360]

        frameCount += 0.04f; // Increment frame count for up-down motion

        // Reset frameCount periodically to avoid overflow
        if (frameCount >= 1000.0f) frameCount -= 1000.0f; // Wrap after 1000 frames

        // Calculate vertical oscillation
        float height = 1.0f * sin(frameCount * 0.05f);  // Amplitude = 2.0, speed = 0.05 per frame

        // Update pyramid's position and rotation
        m_pyramid->getTransform()->setPosition(targetPosition + glm::vec3(0.0f, height + 3.0f, 0.0f)); // Offset above the target
        m_pyramid->getTransform()->setEuler(glm::vec3(180.0f, angle, 0.0f)); // Y-axis rotation
    }
}