cmake_minimum_required(VERSION 3.24.1)
set(CMAKE_BUILD_TYPE Debug)
project(testproject)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MDd")
set(PROJECT_DIR ${CMAKE_SOURCE_DIR})

set(PROJECT_INCLUDE_DIR      ${CMAKE_SOURCE_DIR}/include)
set(PROJECT_LIB_DIR          ${CMAKE_SOURCE_DIR}/../../lib)
set(PROJECT_SOURCE_DIR       ${CMAKE_SOURCE_DIR}/src)

set(ImGui_Source_Files  ${PROJECT_LIB_DIR}/imgui/imgui.cpp
                        ${PROJECT_LIB_DIR}/imgui/imgui_draw.cpp
                        ${PROJECT_LIB_DIR}/imgui/imgui_tables.cpp
                        ${PROJECT_LIB_DIR}/imgui/imgui_widgets.cpp
                        ${PROJECT_LIB_DIR}/imgui/backends/imgui_impl_glfw.cpp   
                        ${PROJECT_LIB_DIR}/imgui/backends/imgui_impl_opengl3.cpp
                        )
set(PROJECT_SOURCES
            ${PROJECT_SOURCE_DIR}/main.cpp
            ${PROJECT_SOURCE_DIR}/glad.c
            ${PROJECT_SOURCE_DIR}/shaderprogram.cpp
            ${PROJECT_SOURCE_DIR}/vertexbuffer.cpp
            ${PROJECT_SOURCE_DIR}/indexbuffer.cpp
            ${PROJECT_SOURCE_DIR}/vertexarrayobject.cpp
            ${PROJECT_SOURCE_DIR}/glwindow.cpp
            ${PROJECT_SOURCE_DIR}/texturemanager.cpp
            ${PROJECT_SOURCE_DIR}/shapecreator.cpp
            ${PROJECT_SOURCE_DIR}/transform.cpp
            ${PROJECT_SOURCE_DIR}/camera.cpp
            ${PROJECT_SOURCE_DIR}/shadermanager.cpp
            ${PROJECT_SOURCE_DIR}/model.cpp
            ${PROJECT_SOURCE_DIR}/scene.cpp
            ${PROJECT_SOURCE_DIR}/scenemenu.cpp
            ${ImGui_Source_Files}
            )

set(PROJECT_HEADERS
            ${PROJECT_INCLUDE_DIR}/glad/glad.h
            ${PROJECT_INCLUDE_DIR}/shaderprogram.hpp
            ${PROJECT_INCLUDE_DIR}/vertexbuffer.hpp
            ${PROJECT_INCLUDE_DIR}/indexbuffer.hpp
            ${PROJECT_INCLUDE_DIR}/vertexarrayobject.hpp
            ${PROJECT_INCLUDE_DIR}/glwindow.hpp
            ${PROJECT_INCLUDE_DIR}/texturemanager.hpp
            ${PROJECT_INCLUDE_DIR}/shapecreator.hpp
            ${PROJECT_INCLUDE_DIR}/transform.hpp
            ${PROJECT_INCLUDE_DIR}/camera.hpp
            ${PROJECT_INCLUDE_DIR}/shadermanager.hpp
            ${PROJECT_INCLUDE_DIR}/model.hpp
            ${PROJECT_INCLUDE_DIR}/scene.hpp
            ${PROJECT_INCLUDE_DIR}/KHR/khrplatform.h)

#find_package(glfw3 3.4 REQUIRED PATHS ${PROJECTLIB_DIR}/GLFW/lib/cmake/glfw3/)


include_directories(
    ${PROJECT_INCLUDE_DIR}
    ${PROJECT_LIB_DIR}/glm/glm
    ${PROJECT_LIB_DIR}/GLFW/include
    ${PROJECT_LIB_DIR}/imgui
    ${PROJECT_LIB_DIR}/imgui/backends
    ${PROJECT_LIB_DIR}/json
    ${PROJECT_LIB_DIR}/stb
)



link_directories(${PROJECT_LIB_DIR}/GLFW/lib)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME} glfw3 opengl32)