#include <iostream>
#include "shaderprogram.hpp"
#include "vertexarrayobject.hpp"
#include "shapecreator.hpp"
#include "glwindow.hpp"
#include <mat4x4.hpp>
#include "texturemanager.hpp"
#include <glm/glm/gtc/matrix_transform.hpp>
#include <ctime>

char* fragmentShaderFileLocation = "./shaders/fragment.glsl";
char* vertexShaderFileLocation   = "./shaders/vertex.glsl";


char* grassTexFileName = "./images/grass.jpg";
char* stoneTexFileName = "./images/cobblestone.jpg";
char* sandTexFileName = "./images/sand.jpg";
char* gravelTexFileName = "./images/gravel.jpg";
struct Shape
{
    int m_va = 0;
    int m_tex;
    float angle = 0.0f;
    glm::vec3 position;
}shapes[9];

glm::mat4 calculatedWorldTransformation(glm::mat4 mtxTranslate, 
                                        glm::mat4 mtxRotation_x, glm::mat4 mtxRotation_y, glm::mat4 mtxRotation_z,
                                        glm::mat4 mtxScale,
                                        glm::mat4 mtxProject)
{
    glm::mat4 mtxRotation = mtxRotation_x * mtxRotation_y * mtxRotation_z;
    glm::mat4 mtxWorld = mtxTranslate * mtxRotation * mtxScale;
    
    return (mtxProject * mtxWorld);
}

int main()
{
    graf::GLWindow glwindow;
    glwindow.create(1200, 800, "first");

    std::srand(time(0));
    graf::ShaderProgram program; 
    program.create();
    program.attachShader(fragmentShaderFileLocation, GL_FRAGMENT_SHADER);
    program.attachShader(vertexShaderFileLocation, GL_VERTEX_SHADER);
    program.link();
    program.addUniform("uWorldTransform");

    graf::TextureManager::addTextureFromFile(grassTexFileName);
    graf::TextureManager::addTextureFromFile(stoneTexFileName);
    graf::TextureManager::addTextureFromFile(sandTexFileName);
    graf::TextureManager::addTextureFromFile(gravelTexFileName);

    char* textureArray[4];
    textureArray[0] = grassTexFileName;
    textureArray[1] = stoneTexFileName;
    textureArray[2] = sandTexFileName;
    textureArray[3] = gravelTexFileName;

    graf::ShapeCreator shapeCreator;


    unsigned int degreePerTrian = 30;
    graf::VertexArrayObject* vaa = new graf::VertexArrayObject[5];
    graf::VertexArrayObject* va_square  = shapeCreator.CreateSquare();
    graf::VertexArrayObject* va_cube    = shapeCreator.CreateCube();
    graf::VertexArrayObject* va_circle  = shapeCreator.CreateCircle(degreePerTrian);
    graf::VertexArrayObject* va_pyramid = shapeCreator.CreatePyramid();
    graf::VertexArrayObject* va_frustum = shapeCreator.CreateFrustum();
    
    vaa[0] = *va_cube;
    vaa[1] = *va_circle;
    vaa[2] = *va_pyramid;
    vaa[3] = *va_square;
    vaa[4] = *va_frustum;

    int selectedShape = 0;
    
    for(int i = 0; i < 9; i++)
        shapes[i].m_tex = std::rand() % 4;
    
    shapes[0].position = glm::vec3{-2.0f,  2.0f, -3.0f}; //top left
    shapes[1].position = glm::vec3{ 0.0f,  2.0f, -3.0f}; //top
    shapes[2].position = glm::vec3{ 2.0f,  2.0f, -3.0f}; //top right
    shapes[3].position = glm::vec3{-2.0f,  0.0f, -3.0f}; //mid left
    shapes[4].position = glm::vec3{ 0.0f,  0.0f, -3.0f}; //mid
    shapes[5].position = glm::vec3{ 2.0f,  0.0f, -3.0f}; //mid right
    shapes[6].position = glm::vec3{-2.0f, -2.0f, -3.0f}; //bottom left
    shapes[7].position = glm::vec3{ 0.0f, -2.0f, -3.0f}; //bottom
    shapes[8].position = glm::vec3{ 2.0f, -2.0f, -3.0f}; //bottom right

    float translateSpeed = 0.12f;
    float angle_y        = 0.0f;
    float angle_x        = 0.0f;
    float rotationSpeed  = 0.005f;
    float scale          = 1.0f;

    glm::vec3 position(0.0f , 0.0f, -3.0f);

    glm::mat4 mtxTranslate  = glm::mat4(1);

    glm::mat4 mtxRotation_x = glm::mat4(1);
    glm::mat4 mtxRotation_y = glm::mat4(1);
    glm::mat4 mtxRotation_z = glm::mat4(1);
    glm::mat4 mtxRotation   = glm::mat4(1);

    glm::mat4 mtxScale      = glm::mat4(1);


    glm::mat4 mtxWorld      = glm::mat4(1);

    glm::mat4 mtxProject = glm::perspective(glm::radians(90.0f), 1.333f, 1.0f, 10.0f);
    glm::mat4 mtxTransform = mtxProject * mtxWorld;


    glwindow.setKeyboardFunction([&](int key, int scancode, int action)
    {
        if(key == GLFW_KEY_W)
        {
            shapes[selectedShape].position.y += translateSpeed;
            mtxTranslate = glm::translate(glm::mat4(1), position);
        }
        if(key == GLFW_KEY_S)
        {
            shapes[selectedShape].position.y -= translateSpeed;
            mtxTranslate = glm::translate(glm::mat4(1), position);
        }
        if(key == GLFW_KEY_A)
        {
            shapes[selectedShape].position.x -= translateSpeed;
            mtxTranslate = glm::translate(glm::mat4(1), position);
        }
        if(key == GLFW_KEY_D)
        {
            shapes[selectedShape].position.x += translateSpeed;
            mtxTranslate = glm::translate(glm::mat4(1), position);
        }
        if(key == GLFW_KEY_SPACE && action == GLFW_PRESS)
            shapes[selectedShape].m_va = (shapes[selectedShape].m_va + 1) % 5;

        if(key == GLFW_KEY_1)
            selectedShape = 0;
        if(key == GLFW_KEY_2)
            selectedShape = 1;
        if(key == GLFW_KEY_3)
            selectedShape = 2;
        if(key == GLFW_KEY_4)
            selectedShape = 3;
        if(key == GLFW_KEY_5)
            selectedShape = 4;
        if(key == GLFW_KEY_6)
            selectedShape = 5;
        if(key == GLFW_KEY_7)
            selectedShape = 6;
        if(key == GLFW_KEY_8)
            selectedShape = 7;
        if(key == GLFW_KEY_9)
            selectedShape = 8;







        //if(key == GLFW_KEY_UP)
        //{
        //    angle_x += 1.0f;
        //    mtxRotation_x  = glm::rotate(glm::mat4(1), glm::radians(angle_x), glm::vec3(1.0f, 0.0f, 0.0f));
        //}
        //if(key == GLFW_KEY_DOWN)
        //{
        //    angle_x -= 1.0f;
        //    mtxRotation_x = glm::rotate(glm::mat4(1), glm::radians(angle_x), glm::vec3(1.0f, 0.0f, 0.0f));
        //}
        //if(key == GLFW_KEY_LEFT)
        //{
        //    angle_y += 1.0f;
        //    mtxRotation_y = glm::rotate(glm::mat4(1), glm::radians(angle_y), glm::vec3(0.0f, 1.0f, 0.0f));
        //}
        //if(key == GLFW_KEY_RIGHT)
        //{
        //    angle_y -= 1.0f;
        //    mtxRotation_y = glm::rotate(glm::mat4(1), glm::radians(angle_y), glm::vec3(0.0f, 1.0f, 0.0f));
        //}


        mtxTransform = calculatedWorldTransformation(mtxTranslate, mtxRotation_x, mtxRotation_y, mtxRotation_z, mtxScale, mtxProject);
    });


    glwindow.setRenderFunction([&]()
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shapes[selectedShape].angle += rotationSpeed;
        program.use();
        for(int i = 0; i < 9; i++)
        {
            mtxTranslate = glm::translate(glm::mat4(1), shapes[i].position);
            mtxRotation_y = glm::rotate(glm::mat4(1), glm::radians(shapes[i].angle), glm::vec3(0.0f, 1.0f, 0.0f));

            vaa[shapes[i].m_va].bind();
            graf::TextureManager::activateTexture(textureArray[shapes[i].m_tex]);

            mtxTransform = calculatedWorldTransformation(mtxTranslate, mtxRotation_x, mtxRotation_y, mtxRotation_z, mtxScale, mtxProject);
            program.setMat4("uWorldTransform", mtxTransform);
            vaa[shapes[i].m_va].draw();
        }


    });
    
    glwindow.render();
    exit(EXIT_SUCCESS);
}