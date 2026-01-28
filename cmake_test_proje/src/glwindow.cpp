#include "glwindow.hpp"
#include <iostream>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
namespace graf
{
    void error_callback(int error, const char* description)
    {
        fprintf(stderr, "Error: %s\n", description);
    }
    void GLWindow::mouseFunction(GLFWwindow* window, double xpos, double ypos)
    {
        GLWindow* myWindow = (GLWindow*)glfwGetWindowUserPointer(window);
        myWindow->m_mouseFunction(xpos, ypos);
    }
    void GLWindow::setMouseFunction(MouseFunction function)
    {
        m_mouseFunction = function;
    }
    GLFWwindow* GLWindow::getWindow()
    {
        return this->m_window;
    }
    void GLWindow::keyboardFunction(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        GLWindow* myWindow = (GLWindow*)glfwGetWindowUserPointer(window);
        myWindow->m_keyboardFunction(key, scancode, action);
    }
    void GLWindow::setKeyboardFunction(KeyboardFunction function)
    {
        m_keyboardFunction = function;
    }
    int GLWindow::create(unsigned int width, unsigned int height, char* windowname)
    {
        glfwSetErrorCallback(error_callback);
        
        if(!glfwInit())
        {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            return -1;
        }

        // Set OpenGL context hints
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_window = glfwCreateWindow(width, height, windowname, NULL, NULL);

        if(m_window == NULL)
        {
            std::cout << "window was not created" << std::endl;
            glfwTerminate();
            return -1;
        }

        glfwMakeContextCurrent(m_window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cerr << "Failed to initialize GLAD" << std::endl;
            glfwDestroyWindow(m_window);
            glfwTerminate();
            return -1;
        }



        glfwSetWindowUserPointer(m_window, this);
        glfwSetCursorPosCallback(m_window, mouseFunction);

        glfwSetKeyCallback(m_window, keyboardFunction);
        glEnable(GL_DEPTH_TEST);
        // glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        ImGui::CreateContext();
        ImGui_ImplOpenGL3_Init("#version 330");
        ImGui_ImplGlfw_InitForOpenGL(m_window, true);
        return 1;
    }

    void GLWindow::render()
    {
        while(!glfwWindowShouldClose(m_window))
        {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            
            m_renderFunction();

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            ImGui::EndFrame();
            
            glfwSwapBuffers(m_window);
            glfwPollEvents();

        }
    }

    void GLWindow::setRenderFunction(RenderFunction function)
    {
        m_renderFunction = function;
    }
}