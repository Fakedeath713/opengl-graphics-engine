/*Bilgisayar Grafigi 1. Odev
Mahmut Azizcan Erdoğan - B211210098
Gizem Tutar - G221210378
Special Thanks:Pearlescen7*/
#include <iostream>
#include "shaderprogram.hpp"
#include "vertexarrayobject.hpp"
#include "shapecreator.hpp"
#include "glwindow.hpp"
#include <mat4x4.hpp>
#include "texturemanager.hpp"
#include <ctime>
#include "gtc/matrix_transform.hpp"
#include "transform.hpp"
#include "camera.hpp"
#include <nlohmann/json.hpp>
#include "shadermanager.hpp"
#include "model.hpp"
#include "scene.hpp"
#include "imgui.h"
#include <glad/glad.h>

int main()
{
    graf::GLWindow glwindow;
    glwindow.create(1000, 1000, "first");

    std::srand(time(0));

    std::string programName = "TextureProgram.json";



    graf::Scene scene;
    scene.addModel("TextureSand");
    scene.addModel("TextureStone");
    scene.addModel("TextureGround");
    scene.addModel("TextureWall1");
    scene.addModel("TextureWall2");
    scene.addModel("TextureWall3");

    double oldMouseX = -1.0f;
    double oldMouseY = -1.0f;
    double dx        =  0.0f;
    double dy        =  0.0f;
    float sens       =  0.4f;


    glwindow.setMouseFunction([&](double xpos, double ypos)
    {
        if(glfwGetInputMode(glwindow.getWindow(), GLFW_CURSOR) == GLFW_CURSOR_NORMAL)
            return;
            if(oldMouseX == -1)
            {
                oldMouseX = xpos;
                oldMouseY = ypos;
            }

            dx = xpos - oldMouseX;
            dy = ypos - oldMouseY;
            scene.getActiveCamera()->turn(dx * sens);
            scene.getActiveCamera()->look(dy * sens);
            oldMouseX = xpos;
            oldMouseY = ypos;
    });
    glwindow.setKeyboardFunction([&](int key, int scancode, int action)
    {
        if(key == GLFW_KEY_W)           scene.getActiveCamera()->getTransform()->MoveForward(); 
        if(key == GLFW_KEY_S)           scene.getActiveCamera()->getTransform()->MoveBackward();
        if(key == GLFW_KEY_A)           scene.getActiveCamera()->getTransform()->MoveLeft();     
        if(key == GLFW_KEY_D)           scene.getActiveCamera()->getTransform()->MoveRight();
        if(key == GLFW_KEY_SPACE)       scene.getActiveCamera()->getTransform()->MoveUp();
        if(key == GLFW_KEY_LEFT_SHIFT)  scene.getActiveCamera()->getTransform()->MoveDown();
        if(key == GLFW_KEY_F10)         glfwSetInputMode(glwindow.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        if(key == GLFW_KEY_F11)         glfwSetInputMode(glwindow.getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    });
    glwindow.setRenderFunction([&]()
    {
        glClearColor(0.0f, 0.7f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        scene.render();

    });
    
    glwindow.render();
}
