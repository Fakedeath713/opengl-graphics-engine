#include "shapecreator.hpp"
#include "vertexarrayobject.hpp"
#include "vertexbuffer.hpp"
#include "indexbuffer.hpp"
#include <glad/glad.h>
#include <glm.hpp>
#include "vertextype.hpp"
namespace graf
{
    VertexArrayObject* ShapeCreator::CreateSquare()
    {
        if(m_vaoMap.count(ShapeTypes::Square) > 0)
            return m_vaoMap[ShapeTypes::Square];

        float vertices[] = {
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, //top left
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f, //top right
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, //bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, //bottom left
        };

        unsigned int indices[] = {
            0, 1, 2,
            0, 2, 3,
        };

        graf::VertexArrayObject* va = new VertexArrayObject(); 
        graf::VertexBuffer*      vb = new VertexBuffer();
        graf::IndexBuffer*       ib = new IndexBuffer();

        vb->create(vertices, sizeof(vertices));
        ib->create(indices, sizeof(indices));
        va->create();
        va->setVertexBuffer(vb);
        va->setIndexBuffer(ib);
        va->addAttribute(graf::VertexAttributeType::Position);
        va->addAttribute(graf::VertexAttributeType::Texture);
        va->activateAttributes();

        m_vaoMap[ShapeTypes::Square] = va;
        va->unbind();
        return va;
    }

    VertexArrayObject* ShapeCreator::CreatePyramid()
    {        
        if(m_vaoMap.count(ShapeTypes::Pyramid) > 0)
            return m_vaoMap[ShapeTypes::Pyramid];

        glm::vec3 positions[] = {
            {-0.5f, -0.5f,  0.5f}, // closer bottom left
            { 0.5f, -0.5f,  0.5f}, // closer bottom right
            { 0.5f, -0.5f, -0.5f}, // far bottom right
            {-0.5f, -0.5f, -0.5f}, // far bottom left
            { 0.0f,  0.5f,  0.0f}, // top
        };

        int vertexCount = 16;
        Vertex* vertexList = new Vertex[vertexCount];
        std::vector<unsigned int> indices;
        //bottom square
        vertexList[0].position = positions[0];
        vertexList[1].position = positions[1];
        vertexList[2].position = positions[2];
        vertexList[3].position = positions[3];
        vertexList[0].texture  = glm::vec2(0.0f, 1.0f);
        vertexList[1].texture  = glm::vec2(1.0f, 1.0f);
        vertexList[2].texture  = glm::vec2(1.0f, 0.0f);
        vertexList[3].texture  = glm::vec2(0.0f, 0.0f);

        indices.push_back(0);
        indices.push_back(2);
        indices.push_back(1);
        indices.push_back(0);
        indices.push_back(3);
        indices.push_back(2);

        //back triangle
        vertexList[4].position = positions[4];
        vertexList[5].position = positions[0];
        vertexList[6].position = positions[1];
        vertexList[4].texture  = glm::vec2(0.5f, 1.0f);
        vertexList[5].texture  = glm::vec2(0.0f, 0.0f);
        vertexList[6].texture  = glm::vec2(1.0f, 0.0f);

        indices.push_back(4);
        indices.push_back(5);
        indices.push_back(6);

        //right triangle
        vertexList[7].position = positions[4];
        vertexList[8].position = positions[1];
        vertexList[9].position = positions[2];
        vertexList[7].texture  = glm::vec2(0.5f, 1.0f);
        vertexList[8].texture  = glm::vec2(0.0f, 0.0f);
        vertexList[9].texture  = glm::vec2(1.0f, 0.0f);

        indices.push_back(7);
        indices.push_back(8);
        indices.push_back(9);

        //front triangle
        vertexList[10].position = positions[4];
        vertexList[11].position = positions[2];
        vertexList[12].position = positions[3];
        vertexList[10].texture  = glm::vec2(0.5f, 1.0f);
        vertexList[11].texture  = glm::vec2(0.0f, 0.0f);
        vertexList[12].texture  = glm::vec2(1.0f, 0.0f);

        indices.push_back(10);
        indices.push_back(11);
        indices.push_back(12);

        //left triangle
        vertexList[13].position = positions[4];
        vertexList[14].position = positions[3];
        vertexList[15].position = positions[0];
        vertexList[13].texture  = glm::vec2(0.5f, 1.0f);
        vertexList[14].texture  = glm::vec2(0.0f, 0.0f);
        vertexList[15].texture  = glm::vec2(1.0f, 0.0f);

        indices.push_back(13);
        indices.push_back(14);
        indices.push_back(15);

        graf::VertexArrayObject* va = new VertexArrayObject(); 
        graf::VertexBuffer*      vb = new VertexBuffer();
        graf::IndexBuffer*       ib = new IndexBuffer();

        vb->create(vertexList, sizeof(Vertex) * vertexCount);
        ib->create(indices.data(), sizeof(unsigned int) * indices.size());
        va->create();
        va->setVertexBuffer(vb);
        va->setIndexBuffer(ib);
        va->addAttribute(graf::VertexAttributeType::Position);
        va->addAttribute(graf::VertexAttributeType::Texture);
        va->activateAttributes();

        m_vaoMap[ShapeTypes::Cube] = va;
        va->unbind();
        delete[] vertexList;
        return va;
    }

    VertexArrayObject* ShapeCreator::CreateFrustum()
    {        
        if(m_vaoMap.count(ShapeTypes::Frustum) > 0)
            return m_vaoMap[ShapeTypes::Frustum];

        glm::vec3 positions[] = {
            {-0.2f,  0.5f,  0.2f}, // closer top left     0
            { 0.2f,  0.5f,  0.2f}, // closer top right    1
            { 0.2f,  0.5f, -0.2f}, // far top right       2
            {-0.2f,  0.5f, -0.2f}, // far top left        3
            {-0.5f, -0.5f,  0.5f}, // closer bottom left  4
            { 0.5f, -0.5f,  0.5f}, // closer bottom right 5
            { 0.5f, -0.5f, -0.5f}, // far bottom right    6
            {-0.5f, -0.5f, -0.5f}, // far bottom left     7
        };

        int vertexCount = 24;
        Vertex* vertexList = new Vertex[vertexCount];
        std::vector<unsigned int> indices;

        //front face
        vertexList[0].position = positions[0];
        vertexList[1].position = positions[1];
        vertexList[2].position = positions[5];
        vertexList[3].position = positions[4];
        vertexList[0].texture  = glm::vec2(0.3f, 1.0f);
        vertexList[1].texture  = glm::vec2(0.7f, 1.0f);
        vertexList[2].texture  = glm::vec2(1.0f, 0.0f);
        vertexList[3].texture  = glm::vec2(0.0f, 0.0f);

        indices.push_back(0);
        indices.push_back(2);
        indices.push_back(1);
        indices.push_back(0);
        indices.push_back(3);
        indices.push_back(2);

        //top
        vertexList[4].position = positions[3];
        vertexList[5].position = positions[2];
        vertexList[6].position = positions[1];
        vertexList[7].position = positions[0];
        vertexList[4].texture  = glm::vec2(0.0f, 1.0f);
        vertexList[5].texture  = glm::vec2(1.0f, 1.0f);
        vertexList[6].texture  = glm::vec2(1.0f, 0.0f);
        vertexList[7].texture  = glm::vec2(0.0f, 0.0f);

        indices.push_back(4);
        indices.push_back(6);
        indices.push_back(5);
        indices.push_back(4);
        indices.push_back(7);
        indices.push_back(6);

        //right face
        vertexList[8].position  = positions[1];
        vertexList[9].position  = positions[2];
        vertexList[10].position = positions[6];
        vertexList[11].position = positions[5];
        vertexList[8].texture   = glm::vec2(0.3f, 1.0f);
        vertexList[9].texture   = glm::vec2(0.7f, 1.0f);
        vertexList[10].texture  = glm::vec2(1.0f, 0.0f);
        vertexList[11].texture  = glm::vec2(0.0f, 0.0f);

        indices.push_back(8);
        indices.push_back(10);
        indices.push_back(9);
        indices.push_back(8);
        indices.push_back(11);
        indices.push_back(10);        
        
        //back face
        vertexList[12].position = positions[2];
        vertexList[13].position = positions[3];
        vertexList[14].position = positions[7];
        vertexList[15].position = positions[6];
        vertexList[12].texture  = glm::vec2(0.3f, 1.0f);
        vertexList[13].texture  = glm::vec2(0.7f, 1.0f);
        vertexList[14].texture  = glm::vec2(1.0f, 0.0f);
        vertexList[15].texture  = glm::vec2(0.0f, 0.0f);

        indices.push_back(12);
        indices.push_back(14);
        indices.push_back(13);
        indices.push_back(12);
        indices.push_back(15);
        indices.push_back(14);

        //left face
        vertexList[16].position = positions[3];
        vertexList[17].position = positions[0];
        vertexList[18].position = positions[4];
        vertexList[19].position = positions[7];
        vertexList[16].texture  = glm::vec2(0.3f, 1.0f);
        vertexList[17].texture  = glm::vec2(0.7f, 1.0f);
        vertexList[18].texture  = glm::vec2(1.0f, 0.0f);
        vertexList[19].texture  = glm::vec2(0.0f, 0.0f);

        indices.push_back(16);
        indices.push_back(18);
        indices.push_back(17);
        indices.push_back(16);
        indices.push_back(19);
        indices.push_back(18);

        //bottom
        vertexList[20].position = positions[4];
        vertexList[21].position = positions[5];
        vertexList[22].position = positions[6];
        vertexList[23].position = positions[7];
        vertexList[20].texture  = glm::vec2(0.0f, 1.0f);
        vertexList[21].texture  = glm::vec2(1.0f, 1.0f);
        vertexList[22].texture  = glm::vec2(1.0f, 0.0f);
        vertexList[23].texture  = glm::vec2(0.0f, 0.0f);

        indices.push_back(20);
        indices.push_back(22);
        indices.push_back(21);
        indices.push_back(20);
        indices.push_back(23);
        indices.push_back(22);

        graf::VertexArrayObject* va = new VertexArrayObject(); 
        graf::VertexBuffer*      vb = new VertexBuffer();
        graf::IndexBuffer*       ib = new IndexBuffer();

        vb->create(vertexList, sizeof(Vertex) * vertexCount);
        ib->create(indices.data(), sizeof(unsigned int) * indices.size());
        va->create();
        va->setVertexBuffer(vb);
        va->setIndexBuffer(ib);
        va->addAttribute(graf::VertexAttributeType::Position);
        va->addAttribute(graf::VertexAttributeType::Texture);
        va->activateAttributes();

        m_vaoMap[ShapeTypes::Cube] = va;
        va->unbind();
        delete[] vertexList;
        return va;
    }
    VertexArrayObject* ShapeCreator::CreateCube()
    {
        if(m_vaoMap.count(ShapeTypes::Cube) > 0)
            return m_vaoMap[ShapeTypes::Cube];

        glm::vec3 positions[] = {
            {-0.5f,  0.5f,  0.5f}, // closer top left
            { 0.5f,  0.5f,  0.5f}, // closer top right
            { 0.5f, -0.5f,  0.5f}, // closer bottom right
            {-0.5f, -0.5f,  0.5f}, // closer bottom left
            {-0.5f,  0.5f, -0.5f}, // far top left
            { 0.5f,  0.5f, -0.5f}, // far top right
            { 0.5f, -0.5f, -0.5f}, // far bottom right
            {-0.5f, -0.5f, -0.5f}, // far bottom left
        };
        int vertexCount = 24;
        Vertex* vertexList = new Vertex[vertexCount];
        std::vector<unsigned int> indices;
        //front face
        vertexList[0].position = positions[0];
        vertexList[1].position = positions[1];
        vertexList[2].position = positions[2];
        vertexList[3].position = positions[3];
        vertexList[0].texture  = glm::vec2(0.0f, 1.0f);
        vertexList[1].texture  = glm::vec2(1.0f, 1.0f);
        vertexList[2].texture  = glm::vec2(1.0f, 0.0f);
        vertexList[3].texture  = glm::vec2(0.0f, 0.0f);

        indices.push_back(0);
        indices.push_back(2);
        indices.push_back(1);
        indices.push_back(0);
        indices.push_back(3);
        indices.push_back(2);

        //Right face
        vertexList[4].position = positions[1];
        vertexList[5].position = positions[5];
        vertexList[6].position = positions[6];
        vertexList[7].position = positions[2];
        vertexList[4].texture  = glm::vec2(0.0f, 1.0f);
        vertexList[5].texture  = glm::vec2(1.0f, 1.0f);
        vertexList[6].texture  = glm::vec2(1.0f, 0.0f);
        vertexList[7].texture  = glm::vec2(0.0f, 0.0f);

        indices.push_back(4);
        indices.push_back(6);
        indices.push_back(5);
        indices.push_back(4);
        indices.push_back(7);
        indices.push_back(6);

        //Bottom face
        vertexList[8].position  = positions[3];
        vertexList[9].position  = positions[2];
        vertexList[10].position = positions[6];
        vertexList[11].position = positions[7];
        vertexList[8].texture   = glm::vec2(0.0f, 1.0f);
        vertexList[9].texture   = glm::vec2(1.0f, 1.0f);
        vertexList[10].texture  = glm::vec2(1.0f, 0.0f);
        vertexList[11].texture  = glm::vec2(0.0f, 0.0f);

        indices.push_back(8);
        indices.push_back(10);
        indices.push_back(9);
        indices.push_back(8);
        indices.push_back(11);
        indices.push_back(10);

        //left face
        vertexList[12].position = positions[4];
        vertexList[13].position = positions[0];
        vertexList[14].position = positions[3];
        vertexList[15].position = positions[7];
        vertexList[12].texture  = glm::vec2(0.0f, 1.0f);
        vertexList[13].texture  = glm::vec2(1.0f, 1.0f);
        vertexList[14].texture  = glm::vec2(1.0f, 0.0f);
        vertexList[15].texture  = glm::vec2(0.0f, 0.0f);

        indices.push_back(12);
        indices.push_back(14);
        indices.push_back(13);
        indices.push_back(12);
        indices.push_back(15);
        indices.push_back(14);

        //back face
        vertexList[16].position = positions[5];
        vertexList[17].position = positions[4];
        vertexList[18].position = positions[7];
        vertexList[19].position = positions[6];
        vertexList[16].texture  = glm::vec2(0.0f, 1.0f);
        vertexList[17].texture  = glm::vec2(1.0f, 1.0f);
        vertexList[18].texture  = glm::vec2(1.0f, 0.0f);
        vertexList[19].texture  = glm::vec2(0.0f, 0.0f);

        indices.push_back(16);
        indices.push_back(18);
        indices.push_back(17);
        indices.push_back(16);
        indices.push_back(19);
        indices.push_back(18);

        //back face
        vertexList[20].position = positions[4];
        vertexList[21].position = positions[5];
        vertexList[22].position = positions[1];
        vertexList[23].position = positions[0];
        vertexList[20].texture  = glm::vec2(0.0f, 1.0f);
        vertexList[21].texture  = glm::vec2(1.0f, 1.0f);
        vertexList[22].texture  = glm::vec2(1.0f, 0.0f);
        vertexList[23].texture  = glm::vec2(0.0f, 0.0f);

        indices.push_back(20);
        indices.push_back(22);
        indices.push_back(21);
        indices.push_back(20);
        indices.push_back(23);
        indices.push_back(22);

        graf::VertexArrayObject* va = new VertexArrayObject(); 
        graf::VertexBuffer*      vb = new VertexBuffer();
        graf::IndexBuffer*       ib = new IndexBuffer();

        vb->create(vertexList, sizeof(Vertex) * vertexCount);
        ib->create(indices.data(), sizeof(unsigned int) * indices.size());
        va->create();
        va->setVertexBuffer(vb);
        va->setIndexBuffer(ib);
        va->addAttribute(graf::VertexAttributeType::Position);
        va->addAttribute(graf::VertexAttributeType::Texture);
        va->activateAttributes();

        m_vaoMap[ShapeTypes::Cube] = va;
        va->unbind();
        delete[] vertexList;
        return va;
    }

    VertexArrayObject* ShapeCreator::CreateCircle(int anglesInDegree)
    {
        if(m_vaoMap.count(ShapeTypes::Circle) > 0)
            return m_vaoMap[ShapeTypes::Circle];

        int vertexCount = 360 / anglesInDegree;
        int triangleCount = vertexCount - 2;
        
        Vertex* vertexList = new Vertex[vertexCount];
        for(int i = 0; i < vertexCount; i++)
        {
            Vertex vert;
            float currentAngle = i * anglesInDegree;
            float r = 0.5f;

            vertexList[i].position.x = r * glm::cos(glm::radians(currentAngle));
            vertexList[i].position.y = r * glm::sin(glm::radians(currentAngle));
            vertexList[i].position.z = 0.0f;

            //for texture
            vertexList[i].texture.s = 0.5 + r * glm::cos(glm::radians(currentAngle));
            vertexList[i].texture.t = 0.5 + r * glm::sin(glm::radians(currentAngle));
        }

        std::vector<unsigned int> indices;

        for(int i = 0; i < triangleCount; i++)
        {
            indices.push_back(0);
            indices.push_back(i + 1);
            indices.push_back(i + 2);
        }


        graf::VertexArrayObject* va = new VertexArrayObject(); 
        graf::VertexBuffer*      vb = new VertexBuffer();
        graf::IndexBuffer*       ib = new IndexBuffer();

        vb->create(vertexList, sizeof(Vertex) * vertexCount);
        ib->create(indices.data(), sizeof(unsigned int) * indices.size());
        va->create();
        va->setVertexBuffer(vb);
        va->setIndexBuffer(ib);
        va->addAttribute(graf::VertexAttributeType::Position);
        va->addAttribute(graf::VertexAttributeType::Texture);
        va->activateAttributes();

        m_vaoMap[ShapeTypes::Square] = va;
        delete[] vertexList;
        va->unbind();
        return va;
    }
}