
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/transform.hpp>

#include <array>
#include <vector>
#include <stdio.h>

struct astro_object
{
    /** The distance to the planet systems center of mass. */
    float orbitDistance;
    /** The objects orbit duration. */
    float orbitPeriod;
    /** The objects equatorial and pole radius. */
    glm::vec2 size;
    /** The objects rotation axis. */
    float rotAxis;
    /** The duration of a rotation. */
    float rotPeriod;
};

struct planet_system
{
    /** The plane this system orbits around the sun. */
    float orbitPlane;
    /** The systems distance to the sun. */
    float orbitDistance;
    /** The systems orbit duration. */
    float orbitPeriod;
    /** The plane all of the systems objects orbit on. */
    float localSystemOrbitPlane;
    /** Holds a list of all objects in the system. */
    std::vector<astro_object> objects;
};

// ASTROLOGICAL CONSTANTS
const float distanceEarthSystem = 293.752f;
const float distancePlutoSystem = 578.754f;
const float distanceMoon = 30.134f;
const float distancePluto = -2.0f;
const float distanceCharon = 6.084f;

const glm::vec2 sizeSun{ 27.179f, 27.178f };
const glm::vec2 sizeEarth{ 10.0f, 9.97 };
const glm::vec2 sizeMoon{ 2.73, 2.72f };
const glm::vec2 sizePluto{ 1.87f, 1.84f };
const glm::vec2 sizeCharon{ 0.95f };

const float orbitPlaneEarth{ 0.0f };
const float orbitPlanePluto{ 17.16f };

const float orbitPlaneMoon{ 5.145f };
const float orbitPlaneCharon{ 119.591f };

const float rotAxisSun{ 7.25f };
const float rotAxisEarth{ 23.44f };
const float rotAxisMoon{ 6.68f };
const float rotAxisPluto{ 122.53f };
const float rotAxisCharon{ 0.0f };

const float rotPeriodSun = 25.38f;
const float rotPeriodEarth = 1.0f;
const float rotPeriodMoon = 27.321f;
const float rotPeriodPluto = 6.375f;
const float rotPeriodCharon = 6.387f;

const float orbitPeriodEarth = 365.256f;
const float orbitPeriodMoon = 27.321f;
const float orbitPeriodPlutoSystem = 65703.835f;
const float orbitPeriodPluto = 6.387f;
const float orbitPeriodCharon = 6.387f;

#include "glframework.h"

std::vector<glframework::vertex> createPlanetVertices()
{
    std::vector<glframework::vertex> vertices;

    const unsigned int polarSteps = 24;
    const unsigned int azimuthalSteps = 24;

    // add top cap
    float phiOld = 0.0f;
    float thetaOld = 0.0f;
    float theta = glm::pi<float>() * static_cast<float>(1) / static_cast<float>(polarSteps);
    for (unsigned int i = 0; i < azimuthalSteps; ++i) {
        float phi = glm::two_pi<float>() * static_cast<float>(i + 1) / static_cast<float>(azimuthalSteps);
        glm::vec3 p0{ 0.0f, 1.0f, 0.0f };
        glm::vec3 p1{ glm::sin(theta) * glm::cos(phiOld), glm::cos(theta), glm::sin(theta) * glm::sin(phiOld) };
        glm::vec3 p2{ glm::sin(theta) * glm::cos(phi), glm::cos(theta), glm::sin(theta) * glm::sin(phi) };

        vertices.push_back(glframework::vertex{ p0,
            glm::vec2(phi / glm::two_pi<float>(), 1.0f - thetaOld / glm::pi<float>()) });
        vertices.push_back(glframework::vertex{ p1,
            glm::vec2(phiOld / glm::two_pi<float>(), 1.0f - theta / glm::pi<float>()) });
        vertices.push_back(glframework::vertex{ p2,
            glm::vec2(phi / glm::two_pi<float>(), 1.0f - theta / glm::pi<float>()) });
        phiOld = phi;
    }
    // add stripes
    thetaOld = theta;
    for (unsigned int j = 1; j < polarSteps; ++j) {
        theta = glm::pi<float>() * static_cast<float>(j) / static_cast<float>(polarSteps);
        phiOld = 0.0f;
        for (unsigned int i = 0; i < azimuthalSteps; ++i) {
            float phi = glm::two_pi<float>() * static_cast<float>(i + 1) / static_cast<float>(azimuthalSteps);
            glm::vec3 p0{ glm::sin(thetaOld) * glm::cos(phiOld), glm::cos(thetaOld),
                         glm::sin(thetaOld) * glm::sin(phiOld) };
            glm::vec3 p1{ glm::sin(theta) * glm::cos(phiOld), glm::cos(theta), glm::sin(theta) * glm::sin(phiOld) };
            glm::vec3 p2{ glm::sin(theta) * glm::cos(phi), glm::cos(theta), glm::sin(theta) * glm::sin(phi) };
            glm::vec3 p3{ glm::sin(thetaOld) * glm::cos(phi), glm::cos(thetaOld),
                         glm::sin(thetaOld) * glm::sin(phi) };

            vertices.push_back(glframework::vertex{ p0,
                glm::vec2(phiOld / glm::two_pi<float>(), 1.0f - thetaOld / glm::pi<float>()) });
            vertices.push_back(glframework::vertex{ p1,
                glm::vec2(phiOld / glm::two_pi<float>(), 1.0f - theta / glm::pi<float>()) });
            vertices.push_back(glframework::vertex{ p2,
                glm::vec2(phi / glm::two_pi<float>(), 1.0f - theta / glm::pi<float>()) });

            vertices.push_back(glframework::vertex{ p0,
                glm::vec2(phiOld / glm::two_pi<float>(), 1.0f - thetaOld / glm::pi<float>()) });
            vertices.push_back(glframework::vertex{ p2,
                glm::vec2(phi / glm::two_pi<float>(), 1.0f - theta / glm::pi<float>()) });
            vertices.push_back(glframework::vertex{ p3,
                glm::vec2(phi / glm::two_pi<float>(), 1.0f - thetaOld / glm::pi<float>()) });

            phiOld = phi;
        }
        thetaOld = theta;
    }

    // add bottom cap
    phiOld = 0.0f;
    for (unsigned int i = 0; i < azimuthalSteps; ++i) {
        float phi = glm::two_pi<float>() * static_cast<float>(i + 1) / static_cast<float>(azimuthalSteps);
        glm::vec3 p0{ 0.0f, -1.0f, 0.0f };
        glm::vec3 p1{ glm::sin(theta) * glm::cos(phi), glm::cos(theta), glm::sin(theta) * glm::sin(phi) };
        glm::vec3 p2{ glm::sin(theta) * glm::cos(phiOld), glm::cos(theta), glm::sin(theta) * glm::sin(phiOld) };
        
        vertices.push_back(glframework::vertex{ p0, 1.0f - glm::vec2(phi / glm::two_pi<float>(), 1.0f) });
        vertices.push_back(glframework::vertex{ p1,
            glm::vec2(phiOld / glm::two_pi<float>(), 1.0f - theta / glm::pi<float>()) });
        vertices.push_back(glframework::vertex{ p2,
            glm::vec2(phi / glm::two_pi<float>(), 1.0f - theta / glm::pi<float>()) });
        phiOld = phi;
    }

    return vertices;
}

int main()
{
    if (!glframework::init("Interaktive Computergrafik 3"))
        return 1;

    // load shader
    GLuint shaderProgram = glframework::loadShaderProgram("shaders/planet.vert", "shaders/planet.frag");

    // get uniform locations
    GLuint MVPUniformLocation = glGetUniformLocation(shaderProgram, "MVP");

    // create the planet mesh
    auto planetVertices = createPlanetVertices();
    auto planetVAO = glframework::createVertexArrayObject(planetVertices);

    // load textures
    std::vector<glframework::texture> textures{
            glframework::loadTexture("res/planets/sun.jpg"),
            glframework::loadTexture("res/planets/earth.jpg"),
            glframework::loadTexture("res/planets/moon.jpg"),
            glframework::loadTexture("res/planets/pluto.jpg"),
            glframework::loadTexture("res/planets/charon.jpg") };

    // create world matrices
    std::vector<glm::mat4> worldMatrices{
            glm::mat4{ 1.0f },
            glm::mat4{ 1.0f },
            glm::mat4{ 1.0f },
            glm::mat4{ 1.0f },
            glm::mat4{ 1.0f } };

    // create astrological objects and planet systems
    const astro_object sun{ 0.0f, 0.0f, sizeSun, rotAxisSun, rotPeriodSun };
    const astro_object earth{ 0.0f, 0.0f, sizeEarth, rotAxisEarth, rotPeriodEarth };
    const astro_object moon{ distanceMoon, orbitPeriodMoon, sizeMoon, rotAxisMoon, rotPeriodMoon };
    const astro_object pluto{ 0.0f, 0.0f, sizePluto, rotAxisPluto, rotPeriodPluto };
    const astro_object charon{ distanceCharon, orbitPeriodCharon, sizeCharon, rotAxisCharon, rotPeriodCharon };
    const planet_system earthMoon{ orbitPlaneEarth, distanceEarthSystem, orbitPeriodEarth, orbitPlaneMoon, {earth, moon} };
    const planet_system plutoCharon{ orbitPlanePluto, distancePlutoSystem, orbitPeriodPlutoSystem, orbitPlaneCharon, { pluto, charon } };
    const std::vector<planet_system> planetSystems{ earthMoon, plutoCharon };

    // set rendering parameters
    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // main rendering loop
    while (glframework::isRunning())
    {
        glframework::beginFrame();

        // update rendered image size
        auto screen = glframework::getWindowSize();
        glViewport(0, 0, screen.x, screen.y);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float currentTime = glframework::getTime();
        float rotTime = currentTime / 5.0f;

        // Sun
        worldMatrices[0] = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f)) * glm::rotate(rotTime / rotPeriodSun * glm::two_pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));

        // Earth
        glm::mat4 earthOrbit = glm::rotate(glm::radians(orbitPlaneEarth), glm::vec3(0.0f, 0.0f, 1.0f)) *
                               glm::rotate(rotTime / orbitPeriodEarth * glm::two_pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)) *
                               glm::translate(glm::mat4(1.0f), glm::vec3(distanceEarthSystem, 0.0f, 0.0f));
        worldMatrices[1] = earthOrbit * glm::rotate(rotTime / rotPeriodEarth * glm::two_pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));

        // Moon
        glm::mat4 moonOrbit = glm::rotate(glm::radians(orbitPlaneMoon), glm::vec3(0.0f, 0.0f, 1.0f)) *
                              glm::rotate(rotTime / orbitPeriodMoon * glm::two_pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)) *
                              glm::translate(glm::mat4(1.0f), glm::vec3(distanceMoon, 0.0f, 0.0f));
        worldMatrices[2] = earthOrbit * moonOrbit * glm::rotate(rotTime / rotPeriodMoon * glm::two_pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));

        // Pluto
        glm::mat4 plutoOrbit = glm::rotate(glm::radians(orbitPlanePluto), glm::vec3(0.0f, 0.0f, 1.0f)) *
                               glm::rotate(rotTime / orbitPeriodPlutoSystem * glm::two_pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)) *
                               glm::translate(glm::mat4(1.0f), glm::vec3(distancePlutoSystem, 0.0f, 0.0f));
        worldMatrices[3] = plutoOrbit * glm::rotate(rotTime / rotPeriodPluto * glm::two_pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));

        // Charon
        glm::mat4 charonOrbit = glm::rotate(glm::radians(orbitPlaneCharon), glm::vec3(0.0f, 0.0f, 1.0f)) *
                                glm::rotate(rotTime / orbitPeriodCharon * glm::two_pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)) *
                                glm::translate(glm::mat4(1.0f), glm::vec3(distanceCharon, 0.0f, 0.0f));
        worldMatrices[4] = plutoOrbit * charonOrbit * glm::rotate(rotTime / rotPeriodCharon * glm::two_pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));

        // set matrices
        auto v = glframework::getCameraView();
        auto p = glframework::getCameraPerspective();

        auto earthMoonSystemWorldMatrix = worldMatrices[1];
        auto vp = p * v * glm::inverse(glm::scale(earthMoonSystemWorldMatrix, glm::vec3(100.0f)));

        // set shader for rendering
        glUseProgram(shaderProgram);
        glActiveTexture(GL_TEXTURE1);
        glBindVertexArray(planetVAO.id);

        // draw planets
        for (int i = 0; i < 5; ++i)
        {
            glm::mat4 mvpMatrix = vp * worldMatrices[i];
            glUniformMatrix4fv(MVPUniformLocation, 1, GL_FALSE, (const float *)glm::value_ptr(mvpMatrix));
            glBindTexture(GL_TEXTURE_2D, textures[i].id);
            glDrawArrays(GL_TRIANGLES, 0, planetVAO.vertexCount);
        }

        glframework::endFrame();
    }

    glframework::destroy();

    return 0;
}