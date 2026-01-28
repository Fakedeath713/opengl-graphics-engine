#ifndef Scene_hpp
#define Scene_hpp
#include "model.hpp"
#include "shapecreator.hpp"
#include "camera.hpp"

namespace graf
{
    class Camera;
    class Scene
    {
    public:
        Scene();
        void addModel(const std::string& filename);
        void addModel(Model* model);
        void addCamera(Camera* camera);
        void removeModel(Model* model);
        void render();
        void renderGui();
        int& modelCount();
        int& currentModel();
        
        int& camCount();
        int& currentCam();

        void update();

        void setActiveCamera(Camera* camera);
        Camera* getActiveCamera();

        CameraList& cameraList();
    private:
        Camera* m_activeCamera;
        Camera* m_alternativeCamera;
        CameraList m_cameraList;
        ModelList m_modelList;
        Model* m_pyramid;
        int m_modelCount;
        int m_currentModel;
        int m_camCount;
        int m_currentCam;
    };
}

#endif