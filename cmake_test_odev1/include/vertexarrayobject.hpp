#ifndef vertexarrayobject_hpp
#define vertexarrayobject_hpp

#include <vector>
namespace graf
{
    enum class VertexAttributeType
    {
        Position,
        Normal,
        Color,
        Texture
    };
    class VertexBuffer;
    class IndexBuffer;
    class VertexArrayObject
    {
        public:
        void create();
        void setVertexBuffer(VertexBuffer* vb);
        void setIndexBuffer(IndexBuffer* ib);
        void addAttribute(VertexAttributeType type);
        void activateAttributes();
        void bind();
        void unbind();
        void release();
        void draw();

        private:
        int getTypeSize(VertexAttributeType type);

        unsigned int m_id;

        VertexBuffer* m_vb;
        IndexBuffer*  m_ib;

        unsigned int m_stride;
        std::vector<VertexAttributeType> m_attr;
    };
}

#endif