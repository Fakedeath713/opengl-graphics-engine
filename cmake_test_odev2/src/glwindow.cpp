#include "glwindow.hpp"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
namespace graf
{
    void error_callback(int error, const char* description)
    {
        fprintf(stderr, "Error: %s\n", description);
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
        glfwSetKeyCallback(m_window, keyboardFunction);
        glEnable(GL_DEPTH_TEST);
        return 0;
    }

    void GLWindow::render()
    {
        while(!glfwWindowShouldClose(m_window))
        {
            m_renderFunction();

            glfwSwapBuffers(m_window);
            glfwPollEvents();

        }
    }

    void GLWindow::setRenderFunction(RenderFunction function)
    {
        m_renderFunction = function;
    }
}