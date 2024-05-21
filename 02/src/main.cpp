
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <array>
#include <vector>
#include <stdio.h>

struct julia_vertex
{
    glm::vec2 position;
    glm::vec2 complex;
};

#include "glframework.h"

std::vector<julia_vertex> createJuliaVertices()
{
    std::vector<julia_vertex> vertices;

    glm::vec2 positions[4] = {
            glm::vec2(0.0f, 0.0f),
            glm::vec2(1.0f, 0.0f),
            glm::vec2(0.0f, 1.0f),
            glm::vec2(1.0f, 1.0f)
    };

    glm::vec2 complexes[4] = {
            glm::vec2(-2.5f, -1.0f),
            glm::vec2( 2.5f, -1.0f),
            glm::vec2(-2.5f,  1.0f),
            glm::vec2( 2.5f,  1.0f)
    };

    for (int i = 0; i < 4; ++i) {
        vertices.push_back(julia_vertex{ positions[i], complexes[i] });
    }

    return vertices;
}

glframework::vao createJuliaVertexArrayObject(std::vector<julia_vertex> vertices)
{
    // load vertex data
    GLuint vertexCount = vertices.size();

    // create vertex array object
    GLuint vertexArrayObject;
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);

    // create vertex buffer object
    GLuint vertexBufferObject;
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(julia_vertex), vertices.data(), GL_STATIC_DRAW);

    // cleanup
    glBindVertexArray(0);

    return { vertexArrayObject, vertexBufferObject, vertexCount };
}

static float zoom = 0.0f;
static glm::vec2 zoomPosition = glm::vec2();

void mouseScrollCallback(float scroll, glm::vec2 mousePos)
{
    auto oldZoom = glm::pow(2.0f, zoom);
    zoom = glm::clamp(zoom + 0.2f * scroll, 0.0f, 1000.0f);
    auto newZoom = glm::pow(2.0f, zoom);

    mousePos = ((mousePos - zoomPosition) / oldZoom) + zoomPosition;
    if (scroll > 0) zoomPosition = glm::mix(mousePos, zoomPosition, oldZoom / newZoom);
}

int main()
{
    if (!glframework::init("Interaktive Computergrafik 2"))
        return 1;

    glframework::setScrollCallback(mouseScrollCallback);

    // Load shader
    GLuint shaderProgram = glframework::loadShaderProgram("shaders/julia.vert", "shaders/julia.frag");

    // Get uniform locations
    GLint timeUniformLocation = glGetUniformLocation(shaderProgram, "time");
    GLint zoomUniformLocation = glGetUniformLocation(shaderProgram, "zoom");
    GLint zoomPositionUniformLocation = glGetUniformLocation(shaderProgram, "zoomPosition");

    // Create the quad mesh
    auto juliaVertices = createJuliaVertices();
    auto juliaVAO = createJuliaVertexArrayObject(juliaVertices);

    // Get vertex attribute locations
    GLuint positionAttrib = glGetAttribLocation(shaderProgram, "position");
    GLuint complexAttrib = glGetAttribLocation(shaderProgram, "complex");

    // Set vertex attribute pointers
    glBindVertexArray(juliaVAO.id);
    glEnableVertexAttribArray(positionAttrib);
    glVertexAttribPointer(positionAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(julia_vertex), (void*)offsetof(julia_vertex, position));
    glEnableVertexAttribArray(complexAttrib);
    glVertexAttribPointer(complexAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(julia_vertex), (void*)offsetof(julia_vertex, complex));
    glBindVertexArray(0);

    // Main rendering loop
    while (glframework::isRunning())
    {
        glframework::beginFrame();

        // Update rendered image size
        auto screen = glframework::getWindowSize();
        glViewport(0, 0, screen.x, screen.y);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set shader for rendering
        glUseProgram(shaderProgram);

        // Set uniform variables
        glUniform1f(timeUniformLocation, glframework::getTime());
        glUniform1f(zoomUniformLocation, glm::pow(2.0f, zoom));
        glUniform2f(zoomPositionUniformLocation, 2.5f * zoomPosition.x, 1.0f * zoomPosition.y);

        // Draw Julia set
        glBindVertexArray(juliaVAO.id);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        glframework::endFrame();
    }

    glframework::destroy();

    return 0;
}
