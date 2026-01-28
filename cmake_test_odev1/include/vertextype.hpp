#ifndef vertextype_hpp
#define vertextype_hpp
#include <glm.hpp>
namespace graf
{
    class Vertex
    {
        public:
        glm::vec3 position;
        glm::vec2 texture;
    };
}

#endif