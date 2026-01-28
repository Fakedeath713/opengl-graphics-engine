cmake_minimum_required(VERSION 3.24.1)
#set(CMAKE_BUILD_TYPE Debug)
project(testproject)

set(PROJECT_DIR ${CMAKE_SOURCE_DIR})

set(PROJECT_INCLUDE_DIR      ${CMAKE_SOURCE_DIR}/include)
set(PROJECT_LIB_DIR          ${CMAKE_SOURCE_DIR}/../../lib)

set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

set(PROJECT_SOURCES
            ${PROJECT_SOURCE_DIR}/main.cpp
            ${PROJECT_SOURCE_DIR}/shaderprogram.cpp
            ${PROJECT_SOURCE_DIR}/vertexbuffer.cpp
            ${PROJECT_SOURCE_DIR}/indexbuffer.cpp
            ${PROJECT_SOURCE_DIR}/vertexarrayobject.cpp
            ${PROJECT_SOURCE_DIR}/glwindow.cpp
            ${PROJECT_SOURCE_DIR}/texturemanager.cpp
            ${PROJECT_SOURCE_DIR}/shapecreator.cpp
            ${PROJECT_SOURCE_DIR}/glad.c)

set(PROJECT_HEADERS
            ${PROJECT_INCLUDE_DIR}/glad/glad.h
            ${PROJECT_INCLUDE_DIR}/shaderprogram.hpp
            ${PROJECT_INCLUDE_DIR}/vertexbuffer.hpp
            ${PROJECT_INCLUDE_DIR}/indexbuffer.hpp
            ${PROJECT_INCLUDE_DIR}/vertexarrayobject.hpp
            ${PROJECT_INCLUDE_DIR}/glwindow.hpp
            ${PROJECT_INCLUDE_DIR}/texturemanager.hpp
            ${PROJECT_INCLUDE_DIR}/shapecreator.hpp
            ${PROJECT_INCLUDE_DIR}/KHR/khrplatform.h)

            #HryviEzgzm{4gy4hs_D4h_S3i3}
            #SiberVatan{4tb4s?_?4s_?3r3}
#find_package(glfw3 3.4 REQUIRED PATHS ${PROJECTLIB_DIR}/GLFW/lib/cmake/glfw3/)

include_directories(
    ${PROJECT_INCLUDE_DIR}
    ${PROJECT_LIB_DIR}/glm/glm
    ${PROJECT_LIB_DIR}/GLFW/include
    ${PROJECT_LIB_DIR}
)

link_directories(${PROJECT_LIB_DIR}/GLFW/lib)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME} glfw3)