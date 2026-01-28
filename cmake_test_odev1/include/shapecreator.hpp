#ifndef shapecreator_hpp
#define shapecreator_hpp
#include <unordered_map>
namespace graf
{
    enum class ShapeTypes
    {
        Square,
        Circle,
        Cube,
        Pyramid,
        Frustum
    };
    class VertexArrayObject;
    class ShapeCreator
    {
        public:
        VertexArrayObject* CreateSquare();
        VertexArrayObject* CreateCube();
        VertexArrayObject* CreateCircle(int anglesInDegree = 10);
        VertexArrayObject* CreatePyramid();
        VertexArrayObject* CreateFrustum();
        private:
        std::unordered_map<ShapeTypes, VertexArrayObject*> m_vaoMap;
    };
}

#endif