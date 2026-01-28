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
        Frustum,
        Cylinder
    };
    class VertexArrayObject;
    class ShapeCreator
    {
        public:
        static VertexArrayObject* CreateShape(ShapeTypes type);

        private:
        ShapeCreator();
        static ShapeCreator* m_Instance;
        VertexArrayObject* CreateSquare();
        VertexArrayObject* CreateCube();
        VertexArrayObject* CreateCircle(int anglesInDegree = 10);
        VertexArrayObject* CreatePyramid();
        VertexArrayObject* CreateFrustum();
        VertexArrayObject* CreateCylinder(int anglesInDegree = 10, float height = 2.0f);
        std::unordered_map<ShapeTypes, VertexArrayObject*> m_vaoMap;
    };
}

#endif