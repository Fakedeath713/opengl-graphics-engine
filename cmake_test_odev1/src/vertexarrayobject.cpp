#include "vertexarrayobject.hpp"
#include "vertexbuffer.hpp"
#include "indexbuffer.hpp"
#include <iostream>
#include <glad/glad.h>
namespace graf
{

    void VertexArrayObject::create()
    {
        glGenVertexArrays(1, &m_id);
        //std::cout << "created vertex array object id ->" << m_id << std::endl;
        m_stride = 0;
    }
    void VertexArrayObject::setVertexBuffer(VertexBuffer* vb)
    {
        m_vb = vb;
        bind();
        m_vb->bind();
    }
    void VertexArrayObject::setIndexBuffer(IndexBuffer* ib)
    {
        m_ib = ib;
        bind();
        m_ib->bind();
    }
    void VertexArrayObject::draw()
    {
        glDrawElements(GL_TRIANGLES, m_ib->indexCount(), GL_UNSIGNED_INT, 0);
    }
    void VertexArrayObject::addAttribute(VertexAttributeType type)
    {
        m_attr.push_back(type);
        m_stride += getTypeSize(type);
    }
    void VertexArrayObject::activateAttributes()
    {
        int location = 0;
        for(int i = 0; i < m_attr.size(); i++)
        {
            int attributeSize = getTypeSize(m_attr[i]);
            int count = attributeSize / sizeof(float);
            glVertexAttribPointer(i, count, GL_FLOAT, GL_FALSE, m_stride, (void*)location);
            location += attributeSize;
            glEnableVertexAttribArray(i);
        }
    }
    void VertexArrayObject::bind()
    {
        glBindVertexArray(m_id);
        //std::cout << "current vao ->" << m_id << std::endl;
    }
    void VertexArrayObject::unbind()
    {
        glBindVertexArray(0);
    }
    void VertexArrayObject::release()
    {
        glDeleteVertexArrays(1, &m_id);
        m_vb->release();
    }
    int VertexArrayObject::getTypeSize(VertexAttributeType type)
    {
        switch (type)
        {
        case VertexAttributeType::Color:
            return sizeof(float) * 4;
            break;

        case VertexAttributeType::Position:
        case VertexAttributeType::Normal:
            return sizeof(float) * 3;
            break;
        
        case VertexAttributeType::Texture:
            return sizeof(float) * 2;
            break;

        default:
            break;
        }
    }
}