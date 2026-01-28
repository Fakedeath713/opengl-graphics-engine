#ifndef glwindow_hpp
#define glwindow_hpp
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
        private:
            static void keyboardFunction(GLFWwindow* window, int key, int scancode, int action, int mods);

            GLFWwindow*      m_window;

            RenderFunction   m_renderFunction;
            KeyboardFunction m_keyboardFunction;
    };
}

#endif