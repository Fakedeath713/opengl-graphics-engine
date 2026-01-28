#ifndef glwindow_hpp
#define glwindow_hpp
#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include "functiontypes.hpp"
class GLFWwindow;
namespace graf
{
    class GLWindow
    {
        public:
            int create(unsigned int width, unsigned int height, char* windowname);
            void render();
            void setRenderFunction(RenderFunction function);
            void setKeyboardFunction(KeyboardFunction function);
            void setMouseFunction(MouseFunction function);
            GLFWwindow* getWindow();
        private:
            static void keyboardFunction(GLFWwindow* window, int key, int scancode, int action, int mods);
            static void mouseFunction(GLFWwindow* window, double xpos, double ypos);

            GLFWwindow*      m_window;

            RenderFunction   m_renderFunction;
            KeyboardFunction m_keyboardFunction;
            MouseFunction    m_mouseFunction;
    };
}

#endif