//
// COMP 371 Labs Framework
//
// Created by Nicolas Bergeron on 20/06/2019.
//
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>
#include <list>

#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> // cross-platform interface for creating a graphical context,
                        // initializing OpenGL and binding inputs

#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // include this to create transformation matrices
#include <glm/common.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <algorithm>
#include <ctime>

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 color;
};

using namespace glm;
using namespace std;

struct TexturedColoredVertex
{
    TexturedColoredVertex(vec3 _position, vec3 _color, vec2 _uv, vec3 _normal)
        : position(_position), color(_color), uv(_uv), normal(_normal) {}

    vec3 position;
    vec3 color;
    vec2 uv;
    vec3 normal;
};

// Textured Cube model
const TexturedColoredVertex texturedCubeVertexArray[] = {  // position,                            color
    TexturedColoredVertex(vec3(-0.5f,-0.5f,-0.5f), vec3(1.0f, 1.0f, 1.0f), vec2(0.0f, 0.0f), vec3(-0.5f,-0.5f,-0.5f)), //left - red
    TexturedColoredVertex(vec3(-0.5f,-0.5f, 0.5f), vec3(1.0f, 1.0f, 1.0f), vec2(0.0f, 1.0f), vec3(-0.5f,-0.5f, 0.5f)),
    TexturedColoredVertex(vec3(-0.5f, 0.5f, 0.5f), vec3(1.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f), vec3(-0.5f, 0.5f, 0.5f)),

    TexturedColoredVertex(vec3(-0.5f,-0.5f,-0.5f), vec3(1.0f, 1.0f, 1.0f), vec2(0.0f, 0.0f), vec3(-0.5f,-0.5f,-0.5f)),
    TexturedColoredVertex(vec3(-0.5f, 0.5f, 0.5f), vec3(1.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f), vec3(-0.5f, 0.5f, 0.5f)),
    TexturedColoredVertex(vec3(-0.5f, 0.5f,-0.5f), vec3(1.0f, 1.0f, 1.0f), vec2(1.0f, 0.0f), vec3(-0.5f, 0.5f,-0.5f)),

    TexturedColoredVertex(vec3(0.5f, 0.5f,-0.5f), vec3(1.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f), vec3(0.5f, 0.5f,-0.5f)), // far - blue
    TexturedColoredVertex(vec3(-0.5f,-0.5f,-0.5f), vec3(1.0f, 1.0f, 1.0f), vec2(0.0f, 0.0f), vec3(-0.5f,-0.5f,-0.5f)),
    TexturedColoredVertex(vec3(-0.5f, 0.5f,-0.5f), vec3(1.0f, 1.0f, 1.0f), vec2(0.0f, 1.0f), vec3(-0.5f, 0.5f,-0.5f)),

    TexturedColoredVertex(vec3(0.5f, 0.5f,-0.5f), vec3(1.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f), vec3(0.5f, 0.5f,-0.5f)),
    TexturedColoredVertex(vec3(0.5f,-0.5f,-0.5f), vec3(1.0f, 1.0f, 1.0f), vec2(1.0f, 0.0f), vec3(0.5f,-0.5f,-0.5f)),
    TexturedColoredVertex(vec3(-0.5f,-0.5f,-0.5f), vec3(1.0f, 1.0f, 1.0f), vec2(0.0f, 0.0f), vec3(-0.5f,-0.5f,-0.5f)),

    TexturedColoredVertex(vec3(0.5f,-0.5f, 0.5f), vec3(1.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f), vec3(0.5f,-0.5f, 0.5f)), // bottom - turquoise
    TexturedColoredVertex(vec3(-0.5f,-0.5f,-0.5f), vec3(1.0f, 1.0f, 1.0f), vec2(0.0f, 0.0f), vec3(-0.5f,-0.5f,-0.5f)),
    TexturedColoredVertex(vec3(0.5f,-0.5f,-0.5f), vec3(1.0f, 1.0f, 1.0f), vec2(1.0f, 0.0f), vec3(0.5f,-0.5f,-0.5f)),

    TexturedColoredVertex(vec3(0.5f,-0.5f, 0.5f), vec3(1.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f), vec3(0.5f,-0.5f, 0.5f)),
    TexturedColoredVertex(vec3(-0.5f,-0.5f, 0.5f), vec3(1.0f, 1.0f, 1.0f), vec2(0.0f, 1.0f), vec3(-0.5f,-0.5f, 0.5f)),
    TexturedColoredVertex(vec3(-0.5f,-0.5f,-0.5f), vec3(1.0f, 1.0f, 1.0f), vec2(0.0f, 0.0f), vec3(-0.5f,-0.5f,-0.5f)),

    TexturedColoredVertex(vec3(-0.5f, 0.5f, 0.5f), vec3(1.0f, 1.0f, 1.0f), vec2(0.0f, 1.0f), vec3(-0.5f, 0.5f, 0.5f)), // near - green
    TexturedColoredVertex(vec3(-0.5f,-0.5f, 0.5f), vec3(1.0f, 1.0f, 1.0f), vec2(0.0f, 0.0f), vec3(-0.5f,-0.5f, 0.5f)),
    TexturedColoredVertex(vec3(0.5f,-0.5f, 0.5f), vec3(1.0f, 1.0f, 1.0f), vec2(1.0f, 0.0f), vec3(0.5f,-0.5f, 0.5f)),

    TexturedColoredVertex(vec3(0.5f, 0.5f, 0.5f), vec3(1.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f), vec3(0.5f, 0.5f, 0.5f)),
    TexturedColoredVertex(vec3(-0.5f, 0.5f, 0.5f), vec3(1.0f, 1.0f, 1.0f), vec2(0.0f, 1.0f), vec3(-0.5f, 0.5f, 0.5f)),
    TexturedColoredVertex(vec3(0.5f,-0.5f, 0.5f), vec3(1.0f, 1.0f, 1.0f), vec2(1.0f, 0.0f), vec3(0.5f,-0.5f, 0.5f)),

    TexturedColoredVertex(vec3(0.5f, 0.5f, 0.5f), vec3(1.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f), vec3(0.5f, 0.5f, 0.5f)), // right - purple
    TexturedColoredVertex(vec3(0.5f,-0.5f,-0.5f), vec3(1.0f, 1.0f, 1.0f), vec2(0.0f, 0.0f), vec3(0.5f,-0.5f,-0.5f)),
    TexturedColoredVertex(vec3(0.5f, 0.5f,-0.5f), vec3(1.0f, 1.0f, 1.0f), vec2(1.0f, 0.0f), vec3(0.5f, 0.5f,-0.5f)),

    TexturedColoredVertex(vec3(0.5f,-0.5f,-0.5f), vec3(1.0f, 1.0f, 1.0f), vec2(0.0f, 0.0f), vec3(0.5f,-0.5f,-0.5f)),
    TexturedColoredVertex(vec3(0.5f, 0.5f, 0.5f), vec3(1.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f), vec3(0.5f, 0.5f, 0.5f)),
    TexturedColoredVertex(vec3(0.5f,-0.5f, 0.5f), vec3(1.0f, 1.0f, 1.0f), vec2(0.0f, 1.0f), vec3(0.5f,-0.5f, 0.5f)),

    TexturedColoredVertex(vec3(0.5f, 0.5f, 0.5f), vec3(1.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f), vec3(0.5f, 0.5f, 0.5f)), // top - yellow
    TexturedColoredVertex(vec3(0.5f, 0.5f,-0.5f), vec3(1.0f, 1.0f, 1.0f), vec2(1.0f, 0.0f), vec3(0.5f, 0.5f,-0.5f)),
    TexturedColoredVertex(vec3(-0.5f, 0.5f,-0.5f), vec3(1.0f, 1.0f, 1.0f), vec2(0.0f, 0.0f), vec3(-0.5f, 0.5f,-0.5f)),

    TexturedColoredVertex(vec3(0.5f, 0.5f, 0.5f), vec3(1.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f), vec3(0.5f, 0.5f, 0.5f)),
    TexturedColoredVertex(vec3(-0.5f, 0.5f,-0.5f), vec3(1.0f, 1.0f, 1.0f), vec2(0.0f, 0.0f), vec3(-0.5f, 0.5f,-0.5f)),
    TexturedColoredVertex(vec3(-0.5f, 0.5f, 0.5f), vec3(1.0f, 1.0f, 1.0f), vec2(0.0f, 1.0f), vec3(-0.5f, 0.5f, 0.5f))
};


GLuint loadTexture(const char* filename);

const char* getVertexShaderSource();

const char* getFragmentShaderSource();

const char* getTexturedVertexShaderSource();

const char* getTexturedFragmentShaderSource();

int compileAndLinkShaders(const char* vertexShaderSource, const char* fragmentShaderSource);

int createVertexArrayObject();

int createVertexArrayObjectforSpheres();

int createTexturedCubeVertexArrayObject();


void setProjectionMatrix(int shaderProgram, mat4 projectionMatrix)
{
    glUseProgram(shaderProgram);
    GLuint projectionMatrixLocation = glGetUniformLocation(shaderProgram, "projectionMatrix");
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
}

void setViewMatrix(int shaderProgram, mat4 viewMatrix)
{
    glUseProgram(shaderProgram);
    GLuint viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
}

void setWorldMatrix(int shaderProgram, mat4 worldMatrix)
{
    glUseProgram(shaderProgram);
    GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
    glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &worldMatrix[0][0]);
}


bool initContext();

GLFWwindow* window = NULL;

int main(int argc, char* argv[])
{
    if (!initContext()) return -1;

    GLuint snowTextureID = loadTexture("../Assets/Textures/snow.jpg");
    GLuint carrotTextureID = loadTexture("../Assets/Textures/carrot.jpg");
    GLuint metalTextureID = loadTexture("../Assets/Textures/metal.jpg");

    bool texture = true;

    // Black background
    glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
    // Compile and link shaders here ...
    int shaderProgram = compileAndLinkShaders(getVertexShaderSource(), getFragmentShaderSource());
    int texturedShaderProgram = compileAndLinkShaders(getTexturedVertexShaderSource(), getTexturedFragmentShaderSource());


    // We can set the shader once, since we have only one
    glUseProgram(shaderProgram);

    // Camera parameters for view transform
    vec3 cameraPosition(-5.0f, 9.5f, 20.0f);
    vec3 cameraLookAt(0.2f, -0.2f, -1.0f);
    vec3 cameraUp(0.0f, 1.0f, 0.0f);

    // Other camera parameters
    float cameraSpeed = 1.0f;
    float cameraFastSpeed = 2 * cameraSpeed;
    float cameraHorizontalAngle = 90.0f;
    float cameraVerticalAngle = 0.0f;
    float cameraZoom = 0.0f;

    // Set projection matrix for shader, this won't change
    mat4 projectionMatrix = glm::perspective(70.0f + cameraZoom,            // field of view in degrees
        1024.0f / 768.0f,  // aspect ratio
        0.01f, 100.0f);   // near and far (near > 0)

    // Set initial view matrix
    mat4 viewMatrix = lookAt(cameraPosition,  // eye
        cameraPosition + cameraLookAt,  // center
        cameraUp); // up

    setViewMatrix(shaderProgram, viewMatrix);
    setViewMatrix(texturedShaderProgram, viewMatrix);

    setProjectionMatrix(shaderProgram, projectionMatrix);
    setProjectionMatrix(texturedShaderProgram, projectionMatrix);

    // Define and upload geometry to the GPU here ...
    int vao = createVertexArrayObject();
    int vaoSphere = createVertexArrayObjectforSpheres();
    int texturedCubeVAO = createTexturedCubeVertexArrayObject();

    // For frame time
    float lastFrameTime = glfwGetTime();
    int lastMouseLeftState = GLFW_RELEASE;
    double lastMousePosX, lastMousePosY;
    glfwGetCursorPos(window, &lastMousePosX, &lastMousePosY);

    double keyX{ 0.0 }, keyY{ 0.0 };
    double lastKeyX{ 0.0 }, lastKeyY{ 0.0 };

    // Other OpenGL states to set once before the Game Loop
    // Enable Backface culling
    //glEnable(GL_CULL_FACE);

    glEnable(GL_DEPTH_TEST);

    float x{ 0.0f }, y{ 0.0f }, z{ 0.0f }, s{ 1.0f }, r{ 0.0f };

    // Entering Game Loop
    while (!glfwWindowShouldClose(window))
    {
        // Frame time calculation
        float dt = glfwGetTime() - lastFrameTime;
        lastFrameTime += dt;

        // Each frame, reset color of each pixel to glClearColor

        // Add the GL_DEPTH_BUFFER_BIT to glClear – TODO 1
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // Draw geometry
        glBindVertexArray(vao);
        //glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glUseProgram(shaderProgram);


        GLuint colourLocation = glGetUniformLocation(shaderProgram, "objectColour");
        GLuint lightColour = glGetUniformLocation(shaderProgram, "lightColour");
        GLuint lightPos = glGetUniformLocation(shaderProgram, "lightPos");

        glUniform3fv(lightColour, 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
        glUniform3fv(lightPos, 1, glm::value_ptr(glm::vec3(0.0f, 30.0f, 0.0f)));

        glUseProgram(texturedShaderProgram);

        GLuint texturedColourLocation = glGetUniformLocation(texturedShaderProgram, "objectColour");
        GLuint texturedLightColour = glGetUniformLocation(texturedShaderProgram, "lightColour");
        GLuint texturedLightPos = glGetUniformLocation(texturedShaderProgram, "lightPos");

        glUniform3fv(texturedLightColour, 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
        glUniform3fv(texturedLightPos, 1, glm::value_ptr(glm::vec3(0.0f, 30.0f, 0.0f)));

        glUseProgram(shaderProgram);

        // Draw left leg
        mat4 legWorldMatrix = glm::rotate(mat4(1.0f), 5.0f * r, vec3(0.0f, 1.0f, 0.0f)) * translate(mat4(1.0f), (vec3(-1.0f + x, 0.5f + y, 0.0f + z)) * s) * scale(mat4(1.0f), (vec3(1.5f, 1.0f, 1.0f) * s)) ;
        setWorldMatrix(shaderProgram, legWorldMatrix);
        glUniform3fv(colourLocation, 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //Draw right leg
        legWorldMatrix = glm::rotate(mat4(1.0f), 5.0f * r, vec3(0.0f, 1.0f, 0.0f)) * translate(mat4(1.0f), (vec3(1.0f + x, 0.5f + y, 0.0f + z)) * s) * scale(mat4(1.0f), (vec3(1.5f, 1.0f, 1.0f) * s));
        setWorldMatrix(shaderProgram, legWorldMatrix);
        glUniform3fv(colourLocation, 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray(vaoSphere);

        //Draw lower body
        mat4 lowerBodyWorldMatrix = glm::rotate(mat4(1.0f), 5.0f * r, vec3(0.0f, 1.0f, 0.0f)) * translate(mat4(1.0f), (vec3(0.0f + x, 3.5f + y, 0.0f + z) * s)) * scale(mat4(1.0f), (vec3(3.0f, 3.0f, 3.0f)* s));
        setWorldMatrix(shaderProgram, lowerBodyWorldMatrix);
        glUniform3fv(colourLocation, 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 1261);

        //Draw upper body
        mat4 upperBodyWorldMatrix = glm::rotate(mat4(1.0f), 5.0f * r, vec3(0.0f, 1.0f, 0.0f)) * translate(mat4(1.0f), (vec3(0.0f + x, 6.5 + y, 0.0f + z) * s)) * scale(mat4(1.0f), (vec3(2.5f, 2.5f, 2.5f) * s));
        setWorldMatrix(shaderProgram, upperBodyWorldMatrix);
        glUniform3fv(colourLocation, 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 1261);  

        //Draw head
        mat4 headWorldMatrix = glm::rotate(mat4(1.0f), 5.0f * r, vec3(0.0f, 1.0f, 0.0f)) * translate(mat4(1.0f), (vec3(0.0f + x, 9.5f + y, 0.0f + z) * s)) * scale(mat4(1.0f), (vec3(2.0f, 2.0f, 2.0f) * s));
        setWorldMatrix(shaderProgram, headWorldMatrix);
        glUniform3fv(colourLocation, 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 1261);

        glBindVertexArray(vao);

        //Draw left eye
        mat4 eyeWorldMatrix = glm::rotate(mat4(1.0f), 5.0f * r, vec3(0.0f, 1.0f, 0.0f)) * translate(mat4(1.0f), (vec3(-0.7f + x, 9.85f + y, 2.09f + z) * s)) * scale(mat4(1.0f), (vec3(0.35f, 0.35f, 0.35f) * s));
        setWorldMatrix(shaderProgram, eyeWorldMatrix);
        glUniform3fv(colourLocation, 1, glm::value_ptr(glm::vec3(0.0f, 0.0f, 0.0f)));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //Draw right eye
        eyeWorldMatrix = glm::rotate(mat4(1.0f), 5.0f * r, vec3(0.0f, 1.0f, 0.0f)) * translate(mat4(1.0f), (vec3(0.7f + x, 9.85f + y, 2.09f + z) * s)) * scale(mat4(1.0f), (vec3(0.35f, 0.35f, 0.35f) * s));
        setWorldMatrix(shaderProgram, eyeWorldMatrix);
        glUniform3fv(colourLocation, 1, glm::value_ptr(glm::vec3(0.0f, 0.0f, 0.0f)));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //Draw mouth
        mat4 mouthWorldMatrix = glm::rotate(mat4(1.0f), 5.0f * r, vec3(0.0f, 1.0f, 0.0f)) * translate(mat4(1.0f), (vec3(0.0f + x, 9.2f + y, 2.085f + z) * s)) * scale(mat4(1.0f), (vec3(0.35f, 0.35f, 0.0f) * s));
        setWorldMatrix(shaderProgram, mouthWorldMatrix);
        glUniform3fv(colourLocation, 1, glm::value_ptr(glm::vec3(0.0f, 0.0f, 0.0f)));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //Draw left arm
        mat4 armWorldMatrix = glm::rotate(mat4(1.0f), 5.0f * r, vec3(0.0f, 1.0f, 0.0f)) * translate(mat4(1.0f), (vec3(-4.0f + x, 7.87f + y, 0.0f + z) * s)) * scale(mat4(1.0f), (vec3(6.0f, 0.4f, 1.0f) * s));
        setWorldMatrix(shaderProgram, armWorldMatrix);
        glUniform3fv(colourLocation, 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //Draw right arm
        armWorldMatrix = glm::rotate(mat4(1.0f), 5.0f * r, vec3(0.0f, 1.0f, 0.0f)) * translate(mat4(1.0f), (vec3(4.0f + x, 7.87f + y, 0.0f + z) * s)) * scale(mat4(1.0f), (vec3(6.0f, 0.4f, 1.0f) * s));
        setWorldMatrix(shaderProgram, armWorldMatrix);
        glUniform3fv(colourLocation, 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //Draw x-axis
        mat4 axisWorldMatrix = translate(mat4(1.0f), vec3(2.5f, 0.0f, 0.0f)) * scale(mat4(1.0f), vec3(5.0f, 0.1f, 0.1f));
        setWorldMatrix(shaderProgram, axisWorldMatrix);
        glUniform3fv(colourLocation, 1, glm::value_ptr(glm::vec3(1.0f, 0.0f, 0.0f)));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //Draw y-axis
        axisWorldMatrix = translate(mat4(1.0f), vec3(0.0f, 2.5f, 0.0f)) * scale(mat4(1.0f), vec3(0.1f, 5.0f, 0.1f));
        setWorldMatrix(shaderProgram, axisWorldMatrix);
        glUniform3fv(colourLocation, 1, glm::value_ptr(glm::vec3(0.0f, 1.0f, 0.0f)));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //Draw z-axis
        axisWorldMatrix = translate(mat4(1.0f), vec3(0.0f, 0.0f, 2.5f)) * scale(mat4(1.0f), vec3(0.1f, 0.1f, 5.0f));
        setWorldMatrix(shaderProgram, axisWorldMatrix);
        glUniform3fv(colourLocation, 1, glm::value_ptr(glm::vec3(0.0f, 0.0f, 1.0f)));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray(texturedCubeVAO);

        glUseProgram(texturedShaderProgram);

        glActiveTexture(GL_TEXTURE0);
        GLuint textureLocation = glGetUniformLocation(texturedShaderProgram, "textureSampler");

        if (texture == true) {
            glBindTexture(GL_TEXTURE_2D, snowTextureID);
            //Draw floor
            mat4 floorWorldMatrix = translate(mat4(1.0f), vec3(0.0f, 0.0f, 0.0f)) * scale(mat4(1.0f), vec3(100.0f, 0.0f, 100.0f));
            setWorldMatrix(texturedShaderProgram, floorWorldMatrix);
            glUniform3fv(texturedColourLocation, 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        else {
            glUseProgram(shaderProgram);
            //Draw floor
            mat4 floorWorldMatrix = translate(mat4(1.0f), vec3(0.0f, 0.0f, 0.0f)) * scale(mat4(1.0f), vec3(100.0f, 0.0f, 100.0f));
            setWorldMatrix(shaderProgram, floorWorldMatrix);
            glUniform3fv(colourLocation, 1, glm::value_ptr(glm::vec3(0.96f, 0.96f, 0.96f)));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glUseProgram(texturedShaderProgram);

        glUniform1i(textureLocation, 0);


        if (texture == true) {
            glBindTexture(GL_TEXTURE_2D, carrotTextureID);
            //Draw nose
            mat4 noseWorldMatrix = glm::rotate(mat4(1.0f), 5.0f * r, vec3(0.0f, 1.0f, 0.0f)) * translate(mat4(1.0f), (vec3(0.0f + x, 9.65f + y, 3.0f + z) * s)) * scale(mat4(1.0f), (vec3(0.35f, 0.35f, 2.0f) * s));
            setWorldMatrix(texturedShaderProgram, noseWorldMatrix);
            glUniform3fv(texturedColourLocation, 1, glm::value_ptr(glm::vec3(1.0f, 0.5f, 0.0f)));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        else {
            glUseProgram(shaderProgram);
            //Draw nose
            mat4 noseWorldMatrix = glm::rotate(mat4(1.0f), 5.0f * r, vec3(0.0f, 1.0f, 0.0f)) * translate(mat4(1.0f), (vec3(0.0f + x, 9.65f + y, 3.0f + z) * s)) * scale(mat4(1.0f), (vec3(0.35f, 0.35f, 2.0f) * s));
            setWorldMatrix(shaderProgram, noseWorldMatrix);
            glUniform3fv(colourLocation, 1, glm::value_ptr(glm::vec3(1.0f, 0.5f, 0.0f)));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glUseProgram(texturedShaderProgram);

        glUniform1i(textureLocation, 0);

        

        if (texture == true) {
            glBindTexture(GL_TEXTURE_2D, metalTextureID);
            //Draw hat
            mat4 hatWorldMatrix = glm::rotate(mat4(1.0f), 5.0f * r, vec3(0.0f, 1.0f, 0.0f)) * translate(mat4(1.0f), (vec3(0.0f + x, 11.75f + y, 0.0f + z) * s)) * scale(mat4(1.0f), (vec3(2.0f, 1.0f, 2.0f) * s));
            setWorldMatrix(texturedShaderProgram, hatWorldMatrix);
            glUniform3fv(texturedColourLocation, 1, glm::value_ptr(glm::vec3(0.70f, 0.0f, 0.0f)));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        else {
            glUseProgram(shaderProgram);
            //Draw hat
            mat4 hatWorldMatrix = glm::rotate(mat4(1.0f), 5.0f * r, vec3(0.0f, 1.0f, 0.0f)) * translate(mat4(1.0f), (vec3(0.0f + x, 11.75f + y, 0.0f + z) * s)) * scale(mat4(1.0f), (vec3(2.0f, 1.0f, 2.0f) * s));
            setWorldMatrix(shaderProgram, hatWorldMatrix);
            glUniform3fv(colourLocation, 1, glm::value_ptr(glm::vec3(0.70f, 0.0f, 0.0f)));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glUniform1i(textureLocation, 0);
       
        glBindVertexArray(0);

        // End Frame
        glfwSwapBuffers(window);
        glfwPollEvents();

        // Handle inputs
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

       double mousePosX, mousePosY;
        glfwGetCursorPos(window, &mousePosX, &mousePosY);

        double dx = mousePosX - lastMousePosX;
        double dy = mousePosY - lastMousePosY;

        lastMousePosX = mousePosX;
        lastMousePosY = mousePosY;

       
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
            const float cameraAngularSpeed = 0.5f;
            cameraZoom -= dy * cameraAngularSpeed * dt;
        }
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)
        {
            // Convert to spherical coordinates
            const float cameraAngularSpeed = 60.0f;
            cameraVerticalAngle -= dy * cameraAngularSpeed * dt;

            // Clamp vertical angle to [-85, 85] degrees
            cameraVerticalAngle = std::max(-85.0f, std::min(85.0f, cameraVerticalAngle));
            if (cameraHorizontalAngle > 360)
            {
                cameraHorizontalAngle -= 360;
            }
            else if (cameraHorizontalAngle < -360)
            {
                cameraHorizontalAngle += 360;
            }

            float phi = radians(cameraVerticalAngle);

            cameraLookAt = vec3(cosf(phi), sinf(phi), -cosf(phi));
            vec3 cameraSideVector = glm::cross(cameraLookAt, vec3(0.0f, 1.0f, 0.0f));

            glm::normalize(cameraSideVector);
        }

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
        {
            // Convert to spherical coordinates
            const float cameraAngularSpeed = 60.0f;
            cameraHorizontalAngle -= dx * cameraAngularSpeed * dt;

           // Clamp vertical angle to [-85, 85] degrees
            cameraVerticalAngle = std::max(-85.0f, std::min(85.0f, cameraVerticalAngle));
            if (cameraHorizontalAngle > 360)
            {
                cameraHorizontalAngle -= 360;
            }
            else if (cameraHorizontalAngle < -360)
            {
                cameraHorizontalAngle += 360;
            }

            float theta = radians(cameraHorizontalAngle);

            cameraLookAt = vec3(cosf(theta), 0, sinf(theta));
            vec3 cameraSideVector = glm::cross(cameraLookAt, vec3(0.0f, 1.0f, 0.0f));

            glm::normalize(cameraSideVector);
        }

        double dxKey = keyX - lastKeyX;
        double dyKey = keyY - lastKeyY;

        lastKeyX = keyX;
        lastKeyY = keyY;

        // Convert to spherical coordinates
        const float cameraAngularSpeed = 60.0f;
        cameraHorizontalAngle -= dxKey * cameraAngularSpeed * dt;
        cameraVerticalAngle -= dyKey * cameraAngularSpeed * dt;

        float theta = radians(cameraHorizontalAngle);
        float phi = radians(cameraVerticalAngle);

        cameraLookAt = vec3(cosf(phi) * cosf(theta), sinf(phi), -cosf(phi) * sinf(theta));
        vec3 cameraSideVector = glm::cross(cameraLookAt, vec3(0.0f, 1.0f, 0.0f));

        glm::normalize(cameraSideVector);


        if (glfwGetKey(window, GLFW_KEY_HOME) == GLFW_PRESS)
        {
            keyX = 0.0;
            keyY = 0.0;
            cameraHorizontalAngle = 90.0f;
            cameraVerticalAngle = 0.0f;
        }

        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            keyX -= 2.5;
        }

        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            keyX += 2.5;
        }

        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            keyY -= 2.5;
        }

        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            keyY += 2.5;
        }

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && ((glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))) // move olaf to the left
        {
            if (x >= -50)
                x -= 0.01;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && !((glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))) // move camera to the left
        {
           r += 0.001;
            
        }

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && ((glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))) // move olaf to the right
        {
            if (x <= 50)
                x += 0.01;
        }

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && !((glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))) // move camera to the right
        {
           r -= 0.001;
        }

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && ((glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))) // move olaf forwards
        {
            if (z >= -50)
                z -= 0.01;
        }

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && ((glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))) // move olaf backwards
        {
            if (z <= 50)
                z += 0.01;
        }

        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        {
            srand(time(NULL));

            float random = rand() % 51;
            x = random;

            random = rand() % 51;
            z = random;
        }

        if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }

        if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        }

        if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
        {
            s += 0.001;
        }

        if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
        {
            if (s > 0)
                s -= 0.001;
        }

        if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
        {
            if (texture == true) {
                texture = false;
            }
            else if (texture == false) {
                texture = true;
            }
        }

       
        mat4 viewMatrix = lookAt(cameraPosition, cameraPosition + cameraLookAt, cameraUp);

        mat4 projectionMatrix = glm::perspective(70.0f + cameraZoom,            // field of view in degrees
            1024.0f / 768.0f,  // aspect ratio
            0.01f, 100.0f);   // near and far (near > 0)

        setViewMatrix(shaderProgram, viewMatrix);
        setViewMatrix(texturedShaderProgram, viewMatrix);

        setProjectionMatrix(shaderProgram, projectionMatrix);
        setProjectionMatrix(texturedShaderProgram, projectionMatrix);
    }


    // Shutdown GLFW
    glfwTerminate();

    return 0;
}

const char* getVertexShaderSource()
{
    return
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;"
        "layout(location = 1) in vec3 aNormal;"
        "layout (location = 2) in vec3 aColor;"
        ""
        "uniform mat4 worldMatrix;"
        "uniform mat4 viewMatrix = mat4(1.0);"  // default value for view matrix (identity)
        "uniform mat4 projectionMatrix = mat4(1.0);"
        ""
        "uniform vec3 lightPos;"
        ""
        "out vec3 vertexColor;"
        "out vec3 Normal;"
        "out vec3 FragPos;"
        "out vec3 LightPos;"
        "void main()"
        "{"
        "   vertexColor = aColor;"
        "   mat4 modelViewProjection = projectionMatrix * viewMatrix * worldMatrix;"
        "   gl_Position = modelViewProjection * vec4(aPos.x, aPos.y, aPos.z, 1.0);"
        "   FragPos = vec3(viewMatrix * worldMatrix * vec4(aPos, 1.0));"
        "   Normal = mat3(transpose(inverse(viewMatrix * worldMatrix))) * aNormal;"
        "   LightPos = vec3(viewMatrix * vec4(lightPos, 1.0)); "
        "}";
}

const char* getFragmentShaderSource()
{
    return
        "#version 330 core\n"
        "uniform vec3 lightColour;"
        "uniform vec3 objectColour;"
        "in vec3 vertexColor;"
        "in vec3 FragPos;"
        "in vec3 LightPos;"
        "in vec3 Normal;"
        "out vec4 FragColor;"
        "void main()"
        "{"
        "   float ambientStrength = 0.7;"
        "   vec3 ambient = ambientStrength * lightColour;"
        "   vec3 norm = normalize(Normal);"
        "   vec3 lightDir = normalize(LightPos - FragPos);"
        "   float diff = max(dot(norm, lightDir), 0.0);"
        "   vec3 diffuse = diff * lightColour;"
        "   float specularStrength = 0.9;"
        "   vec3 viewDir = normalize(-FragPos);"
        "   vec3 reflectDir = reflect(-lightDir, norm);"
        "   float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);"
        "   vec3 specular = specularStrength * spec * lightColour;"
        "   vec3 result = (ambient + diffuse + specular) * objectColour;"
        "   FragColor = vec4(result, 1.0); "
        "}";
}

const char* getTexturedVertexShaderSource()
{
    // For now, you use a string for your shader code, in the assignment, shaders will be stored in .glsl files
    return
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;"
        "layout (location = 1) in vec3 aColor;"
        "layout (location = 2) in vec2 aUV;"
        "layout (location = 3) in vec3 aNormal;"
        ""
        "uniform mat4 worldMatrix;"
        "uniform mat4 viewMatrix = mat4(1.0);"  // default value for view matrix (identity)
        "uniform mat4 projectionMatrix = mat4(1.0);"
        ""
        "uniform vec3 lightPos;"
        ""
        "out vec3 vertexColor;"
        "out vec3 Normal;"
        "out vec3 FragPos;"
        "out vec3 LightPos;"
        "out vec2 vertexUV;"
        ""
        "void main()"
        "{"
        "   vertexColor = aColor;"
        "   mat4 modelViewProjection = projectionMatrix * viewMatrix * worldMatrix;"
        "   gl_Position = modelViewProjection * vec4(aPos.x, aPos.y, aPos.z, 1.0);"
        "   vertexUV = aUV;"
        "   FragPos = vec3(viewMatrix * worldMatrix * vec4(aPos, 1.0));"
        "   Normal = mat3(transpose(inverse(viewMatrix * worldMatrix))) * aNormal;"
        "   LightPos = vec3(viewMatrix * vec4(lightPos, 1.0)); "
        "}";
}

const char* getTexturedFragmentShaderSource()
{
    return
        "#version 330 core\n"
        "uniform vec3 lightColour;"
        "uniform vec3 objectColour;"
        "in vec2 vertexUV;"
        "uniform sampler2D textureSampler;"
        "in vec3 vertexColor;"
        "in vec3 FragPos;"
        "in vec3 LightPos;"
        "in vec3 Normal;"
        "out vec4 FragColor;"
        "void main()"
        "{"
        "   vec4 textureColor = texture( textureSampler, vertexUV );"
        "   float ambientStrength = 0.7;"
        "   vec3 ambient = ambientStrength * lightColour;"
        "   vec3 norm = normalize(Normal);"
        "   vec3 lightDir = normalize(LightPos - FragPos);"
        "   float diff = max(dot(norm, lightDir), 0.0);"
        "   vec3 diffuse = diff * lightColour;"
        "   float specularStrength = 0.9;"
        "   vec3 viewDir = normalize(-FragPos);"
        "   vec3 reflectDir = reflect(-lightDir, norm);"
        "   float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);"
        "   vec3 specular = specularStrength * spec * lightColour;"
        "   vec3 result = (ambient + diffuse + specular) * objectColour;"
        "   FragColor = textureColor * vec4(result, 1.0f);"
        "}";
}

int compileAndLinkShaders(const char* vertexShaderSource, const char* fragmentShaderSource)
{
    // compile and link shader program
    // return shader program id
    // ------------------------------------

    // vertex shader
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // fragment shader
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // link shaders
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

GLuint loadTexture(const char* filename)
{
    // Step1 Create and bind textures
    GLuint textureId = 0;
    glGenTextures(1, &textureId);
    assert(textureId != 0);


    glBindTexture(GL_TEXTURE_2D, textureId);

    // Step2 Set filter parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Step3 Load Textures with dimension data
    int width, height, nrChannels;
    unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);
    if (!data)
    {
        std::cerr << "Error::Texture could not load texture file:" << filename << std::endl;
        return 0;
    }

    // Step4 Upload the texture to the PU
    GLenum format = 0;
    if (nrChannels == 1)
        format = GL_RED;
    else if (nrChannels == 3)
        format = GL_RGB;
    else if (nrChannels == 4)
        format = GL_RGBA;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height,
        0, format, GL_UNSIGNED_BYTE, data);

    // Step5 Free resources
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);
    return textureId;
}


int createVertexArrayObject()
{
    // Cube model
    vec3 vertexArray[] = {  // position,   normal,         colour                               
        vec3(-0.5f,-0.5f,-0.5f), vec3(-0.5f,-0.5f,-0.5f), vec3(1.0f, 1.0f, 1.0f), //left - red
        vec3(-0.5f,-0.5f, 0.5f), vec3(-0.5f,-0.5f, 0.5f), vec3(1.0f, 1.0f, 1.0f),
        vec3(-0.5f, 0.5f, 0.5f), vec3(-0.5f, 0.5f, 0.5f), vec3(1.0f, 1.0f, 1.0f),

        vec3(-0.5f,-0.5f,-0.5f), vec3(-0.5f,-0.5f,-0.5f), vec3(1.0f, 1.0f, 1.0f),
        vec3(-0.5f, 0.5f, 0.5f), vec3(-0.5f, 0.5f, 0.5f), vec3(1.0f, 1.0f, 1.0f),
        vec3(-0.5f, 0.5f,-0.5f), vec3(-0.5f, 0.5f,-0.5f), vec3(1.0f, 1.0f, 1.0f),

        vec3(0.5f, 0.5f,-0.5f), vec3(0.5f, 0.5f,-0.5f), vec3(1.0f, 1.0f, 1.0f),
        vec3(-0.5f,-0.5f,-0.5f), vec3(-0.5f,-0.5f,-0.5f), vec3(1.0f, 1.0f, 1.0f),
        vec3(-0.5f, 0.5f,-0.5f), vec3(-0.5f, 0.5f,-0.5f), vec3(1.0f, 1.0f, 1.0f),

        vec3(0.5f, 0.5f,-0.5f), vec3(0.5f, 0.5f,-0.5f), vec3(1.0f, 1.0f, 1.0f),
        vec3(0.5f,-0.5f,-0.5f), vec3(0.5f,-0.5f,-0.5f), vec3(1.0f, 1.0f, 1.0f),
        vec3(-0.5f,-0.5f,-0.5f), vec3(-0.5f,-0.5f,-0.5f), vec3(1.0f, 1.0f, 1.0f),

        vec3(0.5f,-0.5f, 0.5f), vec3(0.5f,-0.5f, 0.5f), vec3(1.0f, 1.0f, 1.0f),
        vec3(-0.5f,-0.5f,-0.5f), vec3(-0.5f,-0.5f,-0.5f), vec3(1.0f, 1.0f, 1.0f),
        vec3(0.5f,-0.5f,-0.5f), vec3(0.5f,-0.5f,-0.5f), vec3(1.0f, 1.0f, 1.0f),

        vec3(0.5f,-0.5f, 0.5f), vec3(0.5f,-0.5f, 0.5f), vec3(1.0f, 1.0f, 1.0f),
        vec3(-0.5f,-0.5f, 0.5f), vec3(-0.5f,-0.5f, 0.5f), vec3(1.0f, 1.0f, 1.0f),
        vec3(-0.5f,-0.5f,-0.5f), vec3(-0.5f,-0.5f,-0.5f), vec3(1.0f, 1.0f, 1.0f),

        vec3(-0.5f, 0.5f, 0.5f), vec3(-0.5f, 0.5f, 0.5f), vec3(1.0f, 1.0f, 1.0f),
        vec3(-0.5f,-0.5f, 0.5f), vec3(-0.5f,-0.5f, 0.5f), vec3(1.0f, 1.0f, 1.0f),
        vec3(0.5f,-0.5f, 0.5f), vec3(0.5f,-0.5f, 0.5f), vec3(1.0f, 1.0f, 1.0f),

        vec3(0.5f, 0.5f, 0.5f), vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 1.0f, 1.0f),
        vec3(-0.5f, 0.5f, 0.5f), vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 1.0f, 1.0f),
        vec3(0.5f,-0.5f, 0.5f), vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 1.0f, 1.0f),

        vec3(0.5f, 0.5f, 0.5f), vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 1.0f, 1.0f),
        vec3(0.5f,-0.5f,-0.5f), vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 1.0f, 1.0f),
        vec3(0.5f, 0.5f,-0.5f), vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 1.0f, 1.0f),

        vec3(0.5f,-0.5f,-0.5f), vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 1.0f, 1.0f),
        vec3(0.5f, 0.5f, 0.5f), vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 1.0f, 1.0f),
        vec3(0.5f,-0.5f, 0.5f), vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 1.0f, 1.0f),

        vec3(0.5f, 0.5f, 0.5f), vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 1.0f, 1.0f),
        vec3(0.5f, 0.5f,-0.5f), vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 1.0f, 1.0f),
        vec3(-0.5f, 0.5f,-0.5f), vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 1.0f, 1.0f),

        vec3(0.5f, 0.5f, 0.5f), vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 1.0f, 1.0f),
        vec3(-0.5f, 0.5f,-0.5f), vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 1.0f, 1.0f),
        vec3(-0.5f, 0.5f, 0.5f), vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 1.0f, 1.0f),
    };


    // Create a vertex array
    GLuint vertexArrayObject;
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);


    // Upload Vertex Buffer to the GPU, keep a reference to it (vertexBufferObject)
    GLuint vertexBufferObject;
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexArray), vertexArray, GL_STATIC_DRAW);

    glVertexAttribPointer(0,                   // attribute 0 matches aPos in Vertex Shader
        3,                   // size
        GL_FLOAT,            // type
        GL_FALSE,            // normalized?
        3 * sizeof(vec3), // stride - each vertex contain 2 vec3 (position, colour)
        (void*)0             // array buffer offset
    );
    glEnableVertexAttribArray(0);


    glVertexAttribPointer(1,                            // attribute 1 matches aColor in Vertex Shader
        3,
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(vec3),
        (void*)sizeof(vec3)      // colour is offseted a vec3 (comes after position)
    );
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2,                            // attribute 1 matches aColor in Vertex Shader
        3,
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(vec3),
        (void*)(2 * sizeof(vec3))      // colour is offseted a vec3 (comes after position)
    );
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBindVertexArray(0);

    return vertexArrayObject;
}

int createTexturedCubeVertexArrayObject()
{
    // Create a vertex array
    GLuint vertexArrayObject;
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);

    // Upload Vertex Buffer to the GPU, keep a reference to it (vertexBufferObject)
    GLuint vertexBufferObject;
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texturedCubeVertexArray), texturedCubeVertexArray, GL_STATIC_DRAW);

    glVertexAttribPointer(0,                   // attribute 0 matches aPos in Vertex Shader
        3,                   // size
        GL_FLOAT,            // type
        GL_FALSE,            // normalized?
        sizeof(TexturedColoredVertex), // stride - each vertex contain 2 vec3 (position, colour)
        (void*)0             // array buffer offset
    );
    glEnableVertexAttribArray(0);


    glVertexAttribPointer(1,                            // attribute 1 matches aColor in Vertex Shader
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(TexturedColoredVertex),
        (void*)sizeof(vec3)      // colour is offseted a vec3 (comes after position)
    );
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2,                            // attribute 2 matches aUV in Vertex Shader
        2,
        GL_FLOAT,
        GL_FALSE,
        sizeof(TexturedColoredVertex),
        (void*)(2 * sizeof(vec3))      // uv is offseted by 2 vec3 (comes after position and colour)
    );
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3,                            // attribute 2 matches aUV in Vertex Shader
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(TexturedColoredVertex),
        (void*)((2 * sizeof(vec3)) + sizeof(vec2))       // normal is offseted by 2 vec3 + vec2 (comes after position and colour and uv)
    );
    glEnableVertexAttribArray(3);

    return vertexArrayObject;
}

int createVertexArrayObjectforSpheres()
{
    Vertex vertexBuffer[] = {
        // position,                                    normal,                              color
        { vec3(0.000000, 0.000000, -1.000000), vec3(0.000000, 0.000000, -1.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.173648, 0.000000, -0.984808), vec3(0.173648, 0.000000, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.171010, 0.030154, -0.984808), vec3(0.171010, 0.030154, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.342020, 0.000000, -0.939693), vec3(0.342020, 0.000000, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.336824, 0.059391, -0.939693), vec3(0.336824, 0.059391, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.500000, 0.000000, -0.866025), vec3(0.500000, 0.000000, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.492404, 0.086824, -0.866025), vec3(0.492404, 0.086824, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.642788, 0.000000, -0.766044), vec3(0.642788, 0.000000, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.633022, 0.111619, -0.766044), vec3(0.633022, 0.111619, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.766044, 0.000000, -0.642788), vec3(0.766044, 0.000000, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.754407, 0.133022, -0.642788), vec3(0.754407, 0.133022, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.866025, 0.000000, -0.500000), vec3(0.866025, 0.000000, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.852869, 0.150384, -0.500000), vec3(0.852869, 0.150384, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.939693, 0.000000, -0.342020), vec3(0.939693, 0.000000, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.925417, 0.163176, -0.342020), vec3(0.925417, 0.163176, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.984808, 0.000000, -0.173648), vec3(0.984808, 0.000000, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.969846, 0.171010, -0.173648), vec3(0.969846, 0.171010, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(1.000000, 0.000000, 0.000000), vec3(1.000000, 0.000000, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.984808, 0.173648, 0.000000), vec3(0.984808, 0.173648, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.984808, 0.000000, 0.173648), vec3(0.984808, 0.000000, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.969846, 0.171010, 0.173648), vec3(0.969846, 0.171010, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.939693, 0.000000, 0.342020), vec3(0.939693, 0.000000, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.925417, 0.163176, 0.342020), vec3(0.925417, 0.163176, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.866025, 0.000000, 0.500000), vec3(0.866025, 0.000000, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.852869, 0.150384, 0.500000), vec3(0.852869, 0.150384, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.766044, 0.000000, 0.642788), vec3(0.766044, 0.000000, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.754407, 0.133022, 0.642788), vec3(0.754407, 0.133022, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.642788, 0.000000, 0.766044), vec3(0.642788, 0.000000, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.633022, 0.111619, 0.766044), vec3(0.633022, 0.111619, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.500000, 0.000000, 0.866025), vec3(0.500000, 0.000000, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.492404, 0.086824, 0.866025), vec3(0.492404, 0.086824, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.342020, 0.000000, 0.939693), vec3(0.342020, 0.000000, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.336824, 0.059391, 0.939693), vec3(0.336824, 0.059391, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.173648, 0.000000, 0.984808), vec3(0.173648, 0.000000, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.171010, 0.030154, 0.984808), vec3(0.171010, 0.030154, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.000000, 1.000000), vec3(0.000000, 0.000000, 1.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.171010, 0.030154, 0.984808), vec3(0.171010, 0.030154, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.163176, 0.059391, 0.984808), vec3(0.163176, 0.059391, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.336824, 0.059391, 0.939693), vec3(0.336824, 0.059391, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.321394, 0.116978, 0.939693), vec3(0.321394, 0.116978, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.492404, 0.086824, 0.866025), vec3(0.492404, 0.086824, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.469846, 0.171010, 0.866025), vec3(0.469846, 0.171010, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.633022, 0.111619, 0.766044), vec3(0.633022, 0.111619, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.604023, 0.219846, 0.766044), vec3(0.604023, 0.219846, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.754407, 0.133022, 0.642788), vec3(0.754407, 0.133022, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.719846, 0.262003, 0.642788), vec3(0.719846, 0.262003, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.852869, 0.150384, 0.500000), vec3(0.852869, 0.150384, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.813798, 0.296198, 0.500000), vec3(0.813798, 0.296198, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.925417, 0.163176, 0.342020), vec3(0.925417, 0.163176, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.883022, 0.321394, 0.342020), vec3(0.883022, 0.321394, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.969846, 0.171010, 0.173648), vec3(0.969846, 0.171010, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.925417, 0.336824, 0.173648), vec3(0.925417, 0.336824, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.984808, 0.173648, 0.000000), vec3(0.984808, 0.173648, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.939693, 0.342020, 0.000000), vec3(0.939693, 0.342020, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.969846, 0.171010, -0.173648), vec3(0.969846, 0.171010, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.925417, 0.336824, -0.173648), vec3(0.925417, 0.336824, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.925417, 0.163176, -0.342020), vec3(0.925417, 0.163176, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.883022, 0.321394, -0.342020), vec3(0.883022, 0.321394, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.852869, 0.150384, -0.500000), vec3(0.852869, 0.150384, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.813798, 0.296198, -0.500000), vec3(0.813798, 0.296198, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.754407, 0.133022, -0.642788), vec3(0.754407, 0.133022, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.719846, 0.262003, -0.642788), vec3(0.719846, 0.262003, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.633022, 0.111619, -0.766044), vec3(0.633022, 0.111619, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.604023, 0.219846, -0.766044), vec3(0.604023, 0.219846, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.492404, 0.086824, -0.866025), vec3(0.492404, 0.086824, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.469846, 0.171010, -0.866025), vec3(0.469846, 0.171010, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.336824, 0.059391, -0.939693), vec3(0.336824, 0.059391, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.321394, 0.116978, -0.939693), vec3(0.321394, 0.116978, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.171010, 0.030154, -0.984808), vec3(0.171010, 0.030154, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.163176, 0.059391, -0.984808), vec3(0.163176, 0.059391, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.000000, -1.000000), vec3(0.000000, 0.000000, -1.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.163176, 0.059391, -0.984808), vec3(0.163176, 0.059391, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.150384, 0.086824, -0.984808), vec3(0.150384, 0.086824, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.321394, 0.116978, -0.939693), vec3(0.321394, 0.116978, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.296198, 0.171010, -0.939693), vec3(0.296198, 0.171010, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.469846, 0.171010, -0.866025), vec3(0.469846, 0.171010, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.433013, 0.250000, -0.866025), vec3(0.433013, 0.250000, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.604023, 0.219846, -0.766044), vec3(0.604023, 0.219846, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.556670, 0.321394, -0.766044), vec3(0.556670, 0.321394, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.719846, 0.262003, -0.642788), vec3(0.719846, 0.262003, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.663414, 0.383022, -0.642788), vec3(0.663414, 0.383022, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.813798, 0.296198, -0.500000), vec3(0.813798, 0.296198, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.750000, 0.433013, -0.500000), vec3(0.750000, 0.433013, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.883022, 0.321394, -0.342020), vec3(0.883022, 0.321394, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.813798, 0.469846, -0.342020), vec3(0.813798, 0.469846, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.925417, 0.336824, -0.173648), vec3(0.925417, 0.336824, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.852869, 0.492404, -0.173648), vec3(0.852869, 0.492404, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.939693, 0.342020, 0.000000), vec3(0.939693, 0.342020, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.866025, 0.500000, 0.000000), vec3(0.866025, 0.500000, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.925417, 0.336824, 0.173648), vec3(0.925417, 0.336824, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.852869, 0.492404, 0.173648), vec3(0.852869, 0.492404, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.883022, 0.321394, 0.342020), vec3(0.883022, 0.321394, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.813798, 0.469846, 0.342020), vec3(0.813798, 0.469846, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.813798, 0.296198, 0.500000), vec3(0.813798, 0.296198, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.750000, 0.433013, 0.500000), vec3(0.750000, 0.433013, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.719846, 0.262003, 0.642788), vec3(0.719846, 0.262003, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.663414, 0.383022, 0.642788), vec3(0.663414, 0.383022, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.604023, 0.219846, 0.766044), vec3(0.604023, 0.219846, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.556670, 0.321394, 0.766044), vec3(0.556670, 0.321394, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.469846, 0.171010, 0.866025), vec3(0.469846, 0.171010, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.433013, 0.250000, 0.866025), vec3(0.433013, 0.250000, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.321394, 0.116978, 0.939693), vec3(0.321394, 0.116978, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.296198, 0.171010, 0.939693), vec3(0.296198, 0.171010, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.163176, 0.059391, 0.984808), vec3(0.163176, 0.059391, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.150384, 0.086824, 0.984808), vec3(0.150384, 0.086824, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.000000, 1.000000), vec3(0.000000, 0.000000, 1.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.150384, 0.086824, 0.984808), vec3(0.150384, 0.086824, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.133022, 0.111619, 0.984808), vec3(0.133022, 0.111619, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.296198, 0.171010, 0.939693), vec3(0.296198, 0.171010, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.262003, 0.219846, 0.939693), vec3(0.262003, 0.219846, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.433013, 0.250000, 0.866025), vec3(0.433013, 0.250000, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.383022, 0.321394, 0.866025), vec3(0.383022, 0.321394, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.556670, 0.321394, 0.766044), vec3(0.556670, 0.321394, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.492404, 0.413176, 0.766044), vec3(0.492404, 0.413176, 0.766045), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.663414, 0.383022, 0.642788), vec3(0.663414, 0.383022, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.586824, 0.492404, 0.642788), vec3(0.586824, 0.492404, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.750000, 0.433013, 0.500000), vec3(0.750000, 0.433013, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.663414, 0.556670, 0.500000), vec3(0.663414, 0.556670, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.813798, 0.469846, 0.342020), vec3(0.813798, 0.469846, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.719846, 0.604023, 0.342020), vec3(0.719846, 0.604023, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.852869, 0.492404, 0.173648), vec3(0.852869, 0.492404, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.754407, 0.633022, 0.173648), vec3(0.754407, 0.633022, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.866025, 0.500000, 0.000000), vec3(0.866025, 0.500000, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.766044, 0.642788, 0.000000), vec3(0.766044, 0.642788, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.852869, 0.492404, -0.173648), vec3(0.852869, 0.492404, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.754407, 0.633022, -0.173648), vec3(0.754407, 0.633022, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.813798, 0.469846, -0.342020), vec3(0.813798, 0.469846, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.719846, 0.604023, -0.342020), vec3(0.719846, 0.604023, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.750000, 0.433013, -0.500000), vec3(0.750000, 0.433013, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.663414, 0.556670, -0.500000), vec3(0.663414, 0.556670, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.663414, 0.383022, -0.642788), vec3(0.663414, 0.383022, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.586824, 0.492404, -0.642788), vec3(0.586824, 0.492404, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.556670, 0.321394, -0.766044), vec3(0.556670, 0.321394, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.492404, 0.413176, -0.766044), vec3(0.492404, 0.413176, -0.766045), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.433013, 0.250000, -0.866025), vec3(0.433013, 0.250000, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.383022, 0.321394, -0.866025), vec3(0.383022, 0.321394, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.296198, 0.171010, -0.939693), vec3(0.296198, 0.171010, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.262003, 0.219846, -0.939693), vec3(0.262003, 0.219846, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.150384, 0.086824, -0.984808), vec3(0.150384, 0.086824, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.133022, 0.111619, -0.984808), vec3(0.133022, 0.111619, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.000000, -1.000000), vec3(0.000000, 0.000000, -1.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.133022, 0.111619, -0.984808), vec3(0.133022, 0.111619, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.111619, 0.133022, -0.984808), vec3(0.111619, 0.133022, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.262003, 0.219846, -0.939693), vec3(0.262003, 0.219846, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.219846, 0.262003, -0.939693), vec3(0.219846, 0.262003, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.383022, 0.321394, -0.866025), vec3(0.383022, 0.321394, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.321394, 0.383022, -0.866025), vec3(0.321394, 0.383022, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.492404, 0.413176, -0.766044), vec3(0.492404, 0.413176, -0.766045), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.413176, 0.492404, -0.766044), vec3(0.413176, 0.492404, -0.766045), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.586824, 0.492404, -0.642788), vec3(0.586824, 0.492404, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.492404, 0.586824, -0.642788), vec3(0.492404, 0.586824, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.663414, 0.556670, -0.500000), vec3(0.663414, 0.556670, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.556670, 0.663414, -0.500000), vec3(0.556670, 0.663414, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.719846, 0.604023, -0.342020), vec3(0.719846, 0.604023, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.604023, 0.719846, -0.342020), vec3(0.604023, 0.719846, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.754407, 0.633022, -0.173648), vec3(0.754407, 0.633022, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.633022, 0.754407, -0.173648), vec3(0.633022, 0.754407, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.766044, 0.642788, 0.000000), vec3(0.766044, 0.642788, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.642788, 0.766044, 0.000000), vec3(0.642788, 0.766044, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.754407, 0.633022, 0.173648), vec3(0.754407, 0.633022, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.633022, 0.754407, 0.173648), vec3(0.633022, 0.754407, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.719846, 0.604023, 0.342020), vec3(0.719846, 0.604023, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.604023, 0.719846, 0.342020), vec3(0.604023, 0.719846, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.663414, 0.556670, 0.500000), vec3(0.663414, 0.556670, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.556670, 0.663414, 0.500000), vec3(0.556670, 0.663414, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.586824, 0.492404, 0.642788), vec3(0.586824, 0.492404, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.492404, 0.586824, 0.642788), vec3(0.492404, 0.586824, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.492404, 0.413176, 0.766044), vec3(0.492404, 0.413176, 0.766045), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.413176, 0.492404, 0.766044), vec3(0.413176, 0.492404, 0.766045), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.383022, 0.321394, 0.866025), vec3(0.383022, 0.321394, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.321394, 0.383022, 0.866025), vec3(0.321394, 0.383022, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.262003, 0.219846, 0.939693), vec3(0.262003, 0.219846, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.219846, 0.262003, 0.939693), vec3(0.219846, 0.262003, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.133022, 0.111619, 0.984808), vec3(0.133022, 0.111619, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.111619, 0.133022, 0.984808), vec3(0.111619, 0.133022, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.000000, 1.000000), vec3(0.000000, 0.000000, 1.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.111619, 0.133022, 0.984808), vec3(0.111619, 0.133022, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.086824, 0.150384, 0.984808), vec3(0.086824, 0.150384, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.219846, 0.262003, 0.939693), vec3(0.219846, 0.262003, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.171010, 0.296198, 0.939693), vec3(0.171010, 0.296198, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.321394, 0.383022, 0.866025), vec3(0.321394, 0.383022, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.250000, 0.433013, 0.866025), vec3(0.250000, 0.433013, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.413176, 0.492404, 0.766044), vec3(0.413176, 0.492404, 0.766045), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.321394, 0.556670, 0.766044), vec3(0.321394, 0.556670, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.492404, 0.586824, 0.642788), vec3(0.492404, 0.586824, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.383022, 0.663414, 0.642788), vec3(0.383022, 0.663414, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.556670, 0.663414, 0.500000), vec3(0.556670, 0.663414, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.433013, 0.750000, 0.500000), vec3(0.433013, 0.750000, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.604023, 0.719846, 0.342020), vec3(0.604023, 0.719846, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.469846, 0.813798, 0.342020), vec3(0.469846, 0.813798, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.633022, 0.754407, 0.173648), vec3(0.633022, 0.754407, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.492404, 0.852869, 0.173648), vec3(0.492404, 0.852869, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.642788, 0.766044, 0.000000), vec3(0.642788, 0.766044, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.500000, 0.866025, 0.000000), vec3(0.500000, 0.866025, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.633022, 0.754407, -0.173648), vec3(0.633022, 0.754407, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.492404, 0.852869, -0.173648), vec3(0.492404, 0.852869, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.604023, 0.719846, -0.342020), vec3(0.604023, 0.719846, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.469846, 0.813798, -0.342020), vec3(0.469846, 0.813798, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.556670, 0.663414, -0.500000), vec3(0.556670, 0.663414, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.433013, 0.750000, -0.500000), vec3(0.433013, 0.750000, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.492404, 0.586824, -0.642788), vec3(0.492404, 0.586824, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.383022, 0.663414, -0.642788), vec3(0.383022, 0.663414, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.413176, 0.492404, -0.766044), vec3(0.413176, 0.492404, -0.766045), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.321394, 0.556670, -0.766044), vec3(0.321394, 0.556670, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.321394, 0.383022, -0.866025), vec3(0.321394, 0.383022, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.250000, 0.433013, -0.866025), vec3(0.250000, 0.433013, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.219846, 0.262003, -0.939693), vec3(0.219846, 0.262003, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.171010, 0.296198, -0.939693), vec3(0.171010, 0.296198, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.111619, 0.133022, -0.984808), vec3(0.111619, 0.133022, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.086824, 0.150384, -0.984808), vec3(0.086824, 0.150384, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.000000, -1.000000), vec3(0.000000, 0.000000, -1.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.086824, 0.150384, -0.984808), vec3(0.086824, 0.150384, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.059391, 0.163176, -0.984808), vec3(0.059391, 0.163176, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.171010, 0.296198, -0.939693), vec3(0.171010, 0.296198, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.116978, 0.321394, -0.939693), vec3(0.116978, 0.321394, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.250000, 0.433013, -0.866025), vec3(0.250000, 0.433013, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.171010, 0.469846, -0.866025), vec3(0.171010, 0.469846, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.321394, 0.556670, -0.766044), vec3(0.321394, 0.556670, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.219846, 0.604023, -0.766044), vec3(0.219846, 0.604023, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.383022, 0.663414, -0.642788), vec3(0.383022, 0.663414, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.262003, 0.719846, -0.642788), vec3(0.262003, 0.719846, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.433013, 0.750000, -0.500000), vec3(0.433013, 0.750000, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.296198, 0.813798, -0.500000), vec3(0.296198, 0.813798, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.469846, 0.813798, -0.342020), vec3(0.469846, 0.813798, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.321394, 0.883022, -0.342020), vec3(0.321394, 0.883022, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.492404, 0.852869, -0.173648), vec3(0.492404, 0.852869, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.336824, 0.925417, -0.173648), vec3(0.336824, 0.925417, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.500000, 0.866025, 0.000000), vec3(0.500000, 0.866025, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.342020, 0.939693, 0.000000), vec3(0.342020, 0.939693, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.492404, 0.852869, 0.173648), vec3(0.492404, 0.852869, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.336824, 0.925417, 0.173648), vec3(0.336824, 0.925417, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.469846, 0.813798, 0.342020), vec3(0.469846, 0.813798, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.321394, 0.883022, 0.342020), vec3(0.321394, 0.883022, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.433013, 0.750000, 0.500000), vec3(0.433013, 0.750000, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.296198, 0.813798, 0.500000), vec3(0.296198, 0.813798, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.383022, 0.663414, 0.642788), vec3(0.383022, 0.663414, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.262003, 0.719846, 0.642788), vec3(0.262003, 0.719846, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.321394, 0.556670, 0.766044), vec3(0.321394, 0.556670, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.219846, 0.604023, 0.766044), vec3(0.219846, 0.604023, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.250000, 0.433013, 0.866025), vec3(0.250000, 0.433013, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.171010, 0.469846, 0.866025), vec3(0.171010, 0.469846, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.171010, 0.296198, 0.939693), vec3(0.171010, 0.296198, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.116978, 0.321394, 0.939693), vec3(0.116978, 0.321394, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.086824, 0.150384, 0.984808), vec3(0.086824, 0.150384, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.059391, 0.163176, 0.984808), vec3(0.059391, 0.163176, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.000000, 1.000000), vec3(0.000000, 0.000000, 1.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.059391, 0.163176, 0.984808), vec3(0.059391, 0.163176, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.030154, 0.171010, 0.984808), vec3(0.030154, 0.171010, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.116978, 0.321394, 0.939693), vec3(0.116978, 0.321394, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.059391, 0.336824, 0.939693), vec3(0.059391, 0.336824, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.171010, 0.469846, 0.866025), vec3(0.171010, 0.469846, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.086824, 0.492404, 0.866025), vec3(0.086824, 0.492404, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.219846, 0.604023, 0.766044), vec3(0.219846, 0.604023, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.111619, 0.633022, 0.766044), vec3(0.111619, 0.633022, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.262003, 0.719846, 0.642788), vec3(0.262003, 0.719846, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.133022, 0.754407, 0.642788), vec3(0.133022, 0.754407, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.296198, 0.813798, 0.500000), vec3(0.296198, 0.813798, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.150384, 0.852869, 0.500000), vec3(0.150384, 0.852869, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.321394, 0.883022, 0.342020), vec3(0.321394, 0.883022, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.163176, 0.925417, 0.342020), vec3(0.163176, 0.925417, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.336824, 0.925417, 0.173648), vec3(0.336824, 0.925417, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.171010, 0.969846, 0.173648), vec3(0.171010, 0.969846, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.342020, 0.939693, 0.000000), vec3(0.342020, 0.939693, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.173648, 0.984808, 0.000000), vec3(0.173648, 0.984808, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.336824, 0.925417, -0.173648), vec3(0.336824, 0.925417, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.171010, 0.969846, -0.173648), vec3(0.171010, 0.969846, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.321394, 0.883022, -0.342020), vec3(0.321394, 0.883022, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.163176, 0.925417, -0.342020), vec3(0.163176, 0.925417, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.296198, 0.813798, -0.500000), vec3(0.296198, 0.813798, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.150384, 0.852869, -0.500000), vec3(0.150384, 0.852869, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.262003, 0.719846, -0.642788), vec3(0.262003, 0.719846, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.133022, 0.754407, -0.642788), vec3(0.133022, 0.754407, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.219846, 0.604023, -0.766044), vec3(0.219846, 0.604023, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.111619, 0.633022, -0.766044), vec3(0.111619, 0.633022, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.171010, 0.469846, -0.866025), vec3(0.171010, 0.469846, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.086824, 0.492404, -0.866025), vec3(0.086824, 0.492404, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.116978, 0.321394, -0.939693), vec3(0.116978, 0.321394, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.059391, 0.336824, -0.939693), vec3(0.059391, 0.336824, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.059391, 0.163176, -0.984808), vec3(0.059391, 0.163176, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.030154, 0.171010, -0.984808), vec3(0.030154, 0.171010, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.000000, -1.000000), vec3(0.000000, 0.000000, -1.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.030154, 0.171010, -0.984808), vec3(0.030154, 0.171010, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.173648, -0.984808), vec3(0.000000, 0.173648, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.059391, 0.336824, -0.939693), vec3(0.059391, 0.336824, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.342020, -0.939693), vec3(0.000000, 0.342020, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.086824, 0.492404, -0.866025), vec3(0.086824, 0.492404, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.500000, -0.866025), vec3(0.000000, 0.500000, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.111619, 0.633022, -0.766044), vec3(0.111619, 0.633022, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.642788, -0.766044), vec3(0.000000, 0.642788, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.133022, 0.754407, -0.642788), vec3(0.133022, 0.754407, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.766044, -0.642788), vec3(0.000000, 0.766044, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.150384, 0.852869, -0.500000), vec3(0.150384, 0.852869, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.866025, -0.500000), vec3(0.000000, 0.866025, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.163176, 0.925417, -0.342020), vec3(0.163176, 0.925417, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.939693, -0.342020), vec3(0.000000, 0.939693, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.171010, 0.969846, -0.173648), vec3(0.171010, 0.969846, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.984808, -0.173648), vec3(0.000000, 0.984808, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.173648, 0.984808, 0.000000), vec3(0.173648, 0.984808, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 1.000000, 0.000000), vec3(0.000000, 1.000000, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.171010, 0.969846, 0.173648), vec3(0.171010, 0.969846, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.984808, 0.173648), vec3(0.000000, 0.984808, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.163176, 0.925417, 0.342020), vec3(0.163176, 0.925417, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.939693, 0.342020), vec3(0.000000, 0.939693, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.150384, 0.852869, 0.500000), vec3(0.150384, 0.852869, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.866025, 0.500000), vec3(0.000000, 0.866025, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.133022, 0.754407, 0.642788), vec3(0.133022, 0.754407, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.766044, 0.642788), vec3(0.000000, 0.766044, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.111619, 0.633022, 0.766044), vec3(0.111619, 0.633022, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.642788, 0.766044), vec3(0.000000, 0.642788, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.086824, 0.492404, 0.866025), vec3(0.086824, 0.492404, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.500000, 0.866025), vec3(0.000000, 0.500000, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.059391, 0.336824, 0.939693), vec3(0.059391, 0.336824, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.342020, 0.939693), vec3(0.000000, 0.342020, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.030154, 0.171010, 0.984808), vec3(0.030154, 0.171010, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.173648, 0.984808), vec3(0.000000, 0.173648, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.000000, 1.000000), vec3(0.000000, 0.000000, 1.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.173648, 0.984808), vec3(0.000000, 0.173648, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.030154, 0.171010, 0.984808), vec3(-0.030154, 0.171010, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.342020, 0.939693), vec3(0.000000, 0.342020, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.059391, 0.336824, 0.939693), vec3(-0.059391, 0.336824, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.500000, 0.866025), vec3(0.000000, 0.500000, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.086824, 0.492404, 0.866025), vec3(-0.086824, 0.492404, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.642788, 0.766044), vec3(0.000000, 0.642788, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.111619, 0.633022, 0.766044), vec3(-0.111619, 0.633022, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.766044, 0.642788), vec3(0.000000, 0.766044, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.133022, 0.754407, 0.642788), vec3(-0.133022, 0.754407, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.866025, 0.500000), vec3(0.000000, 0.866025, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.150384, 0.852869, 0.500000), vec3(-0.150384, 0.852869, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.939693, 0.342020), vec3(0.000000, 0.939693, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.163176, 0.925417, 0.342020), vec3(-0.163176, 0.925417, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.984808, 0.173648), vec3(0.000000, 0.984808, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.171010, 0.969846, 0.173648), vec3(-0.171010, 0.969846, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 1.000000, 0.000000), vec3(0.000000, 1.000000, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.173648, 0.984808, 0.000000), vec3(-0.173648, 0.984808, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.984808, -0.173648), vec3(0.000000, 0.984808, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.171010, 0.969846, -0.173648), vec3(-0.171010, 0.969846, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.939693, -0.342020), vec3(0.000000, 0.939693, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.163176, 0.925417, -0.342020), vec3(-0.163176, 0.925417, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.866025, -0.500000), vec3(0.000000, 0.866025, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.150384, 0.852869, -0.500000), vec3(-0.150384, 0.852869, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.766044, -0.642788), vec3(0.000000, 0.766044, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.133022, 0.754407, -0.642788), vec3(-0.133022, 0.754407, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.642788, -0.766044), vec3(0.000000, 0.642788, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.111619, 0.633022, -0.766044), vec3(-0.111619, 0.633022, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.500000, -0.866025), vec3(0.000000, 0.500000, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.086824, 0.492404, -0.866025), vec3(-0.086824, 0.492404, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.342020, -0.939693), vec3(0.000000, 0.342020, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.059391, 0.336824, -0.939693), vec3(-0.059391, 0.336824, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.173648, -0.984808), vec3(0.000000, 0.173648, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.030154, 0.171010, -0.984808), vec3(-0.030154, 0.171010, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.000000, -1.000000), vec3(0.000000, 0.000000, -1.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.030154, 0.171010, -0.984808), vec3(-0.030154, 0.171010, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.059391, 0.163176, -0.984808), vec3(-0.059391, 0.163176, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.059391, 0.336824, -0.939693), vec3(-0.059391, 0.336824, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.116978, 0.321394, -0.939693), vec3(-0.116978, 0.321394, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.086824, 0.492404, -0.866025), vec3(-0.086824, 0.492404, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.171010, 0.469846, -0.866025), vec3(-0.171010, 0.469846, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.111619, 0.633022, -0.766044), vec3(-0.111619, 0.633022, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.219846, 0.604023, -0.766044), vec3(-0.219846, 0.604023, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.133022, 0.754407, -0.642788), vec3(-0.133022, 0.754407, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.262003, 0.719846, -0.642788), vec3(-0.262003, 0.719846, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.150384, 0.852869, -0.500000), vec3(-0.150384, 0.852869, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.296198, 0.813798, -0.500000), vec3(-0.296198, 0.813798, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.163176, 0.925417, -0.342020), vec3(-0.163176, 0.925417, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.321394, 0.883022, -0.342020), vec3(-0.321394, 0.883022, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.171010, 0.969846, -0.173648), vec3(-0.171010, 0.969846, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.336824, 0.925417, -0.173648), vec3(-0.336824, 0.925417, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.173648, 0.984808, 0.000000), vec3(-0.173648, 0.984808, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.342020, 0.939693, 0.000000), vec3(-0.342020, 0.939693, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.171010, 0.969846, 0.173648), vec3(-0.171010, 0.969846, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.336824, 0.925417, 0.173648), vec3(-0.336824, 0.925417, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.163176, 0.925417, 0.342020), vec3(-0.163176, 0.925417, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.321394, 0.883022, 0.342020), vec3(-0.321394, 0.883022, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.150384, 0.852869, 0.500000), vec3(-0.150384, 0.852869, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.296198, 0.813798, 0.500000), vec3(-0.296198, 0.813798, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.133022, 0.754407, 0.642788), vec3(-0.133022, 0.754407, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.262003, 0.719846, 0.642788), vec3(-0.262003, 0.719846, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.111619, 0.633022, 0.766044), vec3(-0.111619, 0.633022, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.219846, 0.604023, 0.766044), vec3(-0.219846, 0.604023, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.086824, 0.492404, 0.866025), vec3(-0.086824, 0.492404, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.171010, 0.469846, 0.866025), vec3(-0.171010, 0.469846, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.059391, 0.336824, 0.939693), vec3(-0.059391, 0.336824, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.116978, 0.321394, 0.939693), vec3(-0.116978, 0.321394, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.030154, 0.171010, 0.984808), vec3(-0.030154, 0.171010, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.059391, 0.163176, 0.984808), vec3(-0.059391, 0.163176, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.000000, 1.000000), vec3(0.000000, 0.000000, 1.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.059391, 0.163176, 0.984808), vec3(-0.059391, 0.163176, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.086824, 0.150384, 0.984808), vec3(-0.086824, 0.150384, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.116978, 0.321394, 0.939693), vec3(-0.116978, 0.321394, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.171010, 0.296198, 0.939693), vec3(-0.171010, 0.296198, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.171010, 0.469846, 0.866025), vec3(-0.171010, 0.469846, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.250000, 0.433013, 0.866025), vec3(-0.250000, 0.433013, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.219846, 0.604023, 0.766044), vec3(-0.219846, 0.604023, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.321394, 0.556670, 0.766044), vec3(-0.321394, 0.556670, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.262003, 0.719846, 0.642788), vec3(-0.262003, 0.719846, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.383022, 0.663414, 0.642788), vec3(-0.383022, 0.663414, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.296198, 0.813798, 0.500000), vec3(-0.296198, 0.813798, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.433013, 0.750000, 0.500000), vec3(-0.433013, 0.750000, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.321394, 0.883022, 0.342020), vec3(-0.321394, 0.883022, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.469846, 0.813798, 0.342020), vec3(-0.469846, 0.813798, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.336824, 0.925417, 0.173648), vec3(-0.336824, 0.925417, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.492404, 0.852869, 0.173648), vec3(-0.492404, 0.852869, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.342020, 0.939693, 0.000000), vec3(-0.342020, 0.939693, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.500000, 0.866025, 0.000000), vec3(-0.500000, 0.866025, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.336824, 0.925417, -0.173648), vec3(-0.336824, 0.925417, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.492404, 0.852869, -0.173648), vec3(-0.492404, 0.852869, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.321394, 0.883022, -0.342020), vec3(-0.321394, 0.883022, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.469846, 0.813798, -0.342020), vec3(-0.469846, 0.813798, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.296198, 0.813798, -0.500000), vec3(-0.296198, 0.813798, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.433013, 0.750000, -0.500000), vec3(-0.433013, 0.750000, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.262003, 0.719846, -0.642788), vec3(-0.262003, 0.719846, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.383022, 0.663414, -0.642788), vec3(-0.383022, 0.663414, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.219846, 0.604023, -0.766044), vec3(-0.219846, 0.604023, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.321394, 0.556670, -0.766044), vec3(-0.321394, 0.556670, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.171010, 0.469846, -0.866025), vec3(-0.171010, 0.469846, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.250000, 0.433013, -0.866025), vec3(-0.250000, 0.433013, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.116978, 0.321394, -0.939693), vec3(-0.116978, 0.321394, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.171010, 0.296198, -0.939693), vec3(-0.171010, 0.296198, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.059391, 0.163176, -0.984808), vec3(-0.059391, 0.163176, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.086824, 0.150384, -0.984808), vec3(-0.086824, 0.150384, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.000000, -1.000000), vec3(0.000000, 0.000000, -1.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.086824, 0.150384, -0.984808), vec3(-0.086824, 0.150384, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.111619, 0.133022, -0.984808), vec3(-0.111619, 0.133022, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.171010, 0.296198, -0.939693), vec3(-0.171010, 0.296198, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.219846, 0.262003, -0.939693), vec3(-0.219846, 0.262003, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.250000, 0.433013, -0.866025), vec3(-0.250000, 0.433013, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.321394, 0.383022, -0.866025), vec3(-0.321394, 0.383022, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.321394, 0.556670, -0.766044), vec3(-0.321394, 0.556670, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.413176, 0.492404, -0.766044), vec3(-0.413176, 0.492404, -0.766045), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.383022, 0.663414, -0.642788), vec3(-0.383022, 0.663414, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.492404, 0.586824, -0.642788), vec3(-0.492404, 0.586824, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.433013, 0.750000, -0.500000), vec3(-0.433013, 0.750000, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.556670, 0.663414, -0.500000), vec3(-0.556670, 0.663414, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.469846, 0.813798, -0.342020), vec3(-0.469846, 0.813798, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.604023, 0.719846, -0.342020), vec3(-0.604023, 0.719846, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.492404, 0.852869, -0.173648), vec3(-0.492404, 0.852869, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.633022, 0.754407, -0.173648), vec3(-0.633022, 0.754407, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.500000, 0.866025, 0.000000), vec3(-0.500000, 0.866025, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.642788, 0.766044, 0.000000), vec3(-0.642788, 0.766044, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.492404, 0.852869, 0.173648), vec3(-0.492404, 0.852869, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.633022, 0.754407, 0.173648), vec3(-0.633022, 0.754407, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.469846, 0.813798, 0.342020), vec3(-0.469846, 0.813798, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.604023, 0.719846, 0.342020), vec3(-0.604023, 0.719846, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.433013, 0.750000, 0.500000), vec3(-0.433013, 0.750000, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.556670, 0.663414, 0.500000), vec3(-0.556670, 0.663414, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.383022, 0.663414, 0.642788), vec3(-0.383022, 0.663414, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.492404, 0.586824, 0.642788), vec3(-0.492404, 0.586824, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.321394, 0.556670, 0.766044), vec3(-0.321394, 0.556670, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.413176, 0.492404, 0.766044), vec3(-0.413176, 0.492404, 0.766045), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.250000, 0.433013, 0.866025), vec3(-0.250000, 0.433013, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.321394, 0.383022, 0.866025), vec3(-0.321394, 0.383022, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.171010, 0.296198, 0.939693), vec3(-0.171010, 0.296198, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.219846, 0.262003, 0.939693), vec3(-0.219846, 0.262003, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.086824, 0.150384, 0.984808), vec3(-0.086824, 0.150384, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.111619, 0.133022, 0.984808), vec3(-0.111619, 0.133022, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.000000, 1.000000), vec3(0.000000, 0.000000, 1.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.111619, 0.133022, 0.984808), vec3(-0.111619, 0.133022, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.133022, 0.111619, 0.984808), vec3(-0.133022, 0.111619, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.219846, 0.262003, 0.939693), vec3(-0.219846, 0.262003, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.262003, 0.219846, 0.939693), vec3(-0.262003, 0.219846, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.321394, 0.383022, 0.866025), vec3(-0.321394, 0.383022, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.383022, 0.321394, 0.866025), vec3(-0.383022, 0.321394, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.413176, 0.492404, 0.766044), vec3(-0.413176, 0.492404, 0.766045), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.492404, 0.413176, 0.766044), vec3(-0.492404, 0.413176, 0.766045), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.492404, 0.586824, 0.642788), vec3(-0.492404, 0.586824, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.586824, 0.492404, 0.642788), vec3(-0.586824, 0.492404, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.556670, 0.663414, 0.500000), vec3(-0.556670, 0.663414, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.663414, 0.556670, 0.500000), vec3(-0.663414, 0.556670, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.604023, 0.719846, 0.342020), vec3(-0.604023, 0.719846, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.719846, 0.604023, 0.342020), vec3(-0.719846, 0.604023, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.633022, 0.754407, 0.173648), vec3(-0.633022, 0.754407, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.754407, 0.633022, 0.173648), vec3(-0.754407, 0.633022, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.642788, 0.766044, 0.000000), vec3(-0.642788, 0.766044, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.766044, 0.642788, 0.000000), vec3(-0.766044, 0.642788, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.633022, 0.754407, -0.173648), vec3(-0.633022, 0.754407, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.754407, 0.633022, -0.173648), vec3(-0.754407, 0.633022, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.604023, 0.719846, -0.342020), vec3(-0.604023, 0.719846, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.719846, 0.604023, -0.342020), vec3(-0.719846, 0.604023, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.556670, 0.663414, -0.500000), vec3(-0.556670, 0.663414, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.663414, 0.556670, -0.500000), vec3(-0.663414, 0.556670, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.492404, 0.586824, -0.642788), vec3(-0.492404, 0.586824, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.586824, 0.492404, -0.642788), vec3(-0.586824, 0.492404, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.413176, 0.492404, -0.766044), vec3(-0.413176, 0.492404, -0.766045), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.492404, 0.413176, -0.766044), vec3(-0.492404, 0.413176, -0.766045), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.321394, 0.383022, -0.866025), vec3(-0.321394, 0.383022, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.383022, 0.321394, -0.866025), vec3(-0.383022, 0.321394, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.219846, 0.262003, -0.939693), vec3(-0.219846, 0.262003, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.262003, 0.219846, -0.939693), vec3(-0.262003, 0.219846, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.111619, 0.133022, -0.984808), vec3(-0.111619, 0.133022, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.133022, 0.111619, -0.984808), vec3(-0.133022, 0.111619, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.000000, -1.000000), vec3(0.000000, 0.000000, -1.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.133022, 0.111619, -0.984808), vec3(-0.133022, 0.111619, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.150384, 0.086824, -0.984808), vec3(-0.150384, 0.086824, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.262003, 0.219846, -0.939693), vec3(-0.262003, 0.219846, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.296198, 0.171010, -0.939693), vec3(-0.296198, 0.171010, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.383022, 0.321394, -0.866025), vec3(-0.383022, 0.321394, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.433013, 0.250000, -0.866025), vec3(-0.433013, 0.250000, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.492404, 0.413176, -0.766044), vec3(-0.492404, 0.413176, -0.766045), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.556670, 0.321394, -0.766044), vec3(-0.556670, 0.321394, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.586824, 0.492404, -0.642788), vec3(-0.586824, 0.492404, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.663414, 0.383022, -0.642788), vec3(-0.663414, 0.383022, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.663414, 0.556670, -0.500000), vec3(-0.663414, 0.556670, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.750000, 0.433013, -0.500000), vec3(-0.750000, 0.433013, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.719846, 0.604023, -0.342020), vec3(-0.719846, 0.604023, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.813798, 0.469846, -0.342020), vec3(-0.813798, 0.469846, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.754407, 0.633022, -0.173648), vec3(-0.754407, 0.633022, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.852869, 0.492404, -0.173648), vec3(-0.852869, 0.492404, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.766044, 0.642788, 0.000000), vec3(-0.766044, 0.642788, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.866025, 0.500000, 0.000000), vec3(-0.866025, 0.500000, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.754407, 0.633022, 0.173648), vec3(-0.754407, 0.633022, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.852869, 0.492404, 0.173648), vec3(-0.852869, 0.492404, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.719846, 0.604023, 0.342020), vec3(-0.719846, 0.604023, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.813798, 0.469846, 0.342020), vec3(-0.813798, 0.469846, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.663414, 0.556670, 0.500000), vec3(-0.663414, 0.556670, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.750000, 0.433013, 0.500000), vec3(-0.750000, 0.433013, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.586824, 0.492404, 0.642788), vec3(-0.586824, 0.492404, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.663414, 0.383022, 0.642788), vec3(-0.663414, 0.383022, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.492404, 0.413176, 0.766044), vec3(-0.492404, 0.413176, 0.766045), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.556670, 0.321394, 0.766044), vec3(-0.556670, 0.321394, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.383022, 0.321394, 0.866025), vec3(-0.383022, 0.321394, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.433013, 0.250000, 0.866025), vec3(-0.433013, 0.250000, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.262003, 0.219846, 0.939693), vec3(-0.262003, 0.219846, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.296198, 0.171010, 0.939693), vec3(-0.296198, 0.171010, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.133022, 0.111619, 0.984808), vec3(-0.133022, 0.111619, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.150384, 0.086824, 0.984808), vec3(-0.150384, 0.086824, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.000000, 1.000000), vec3(0.000000, 0.000000, 1.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.150384, 0.086824, 0.984808), vec3(-0.150384, 0.086824, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.163176, 0.059391, 0.984808), vec3(-0.163176, 0.059391, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.296198, 0.171010, 0.939693), vec3(-0.296198, 0.171010, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.321394, 0.116978, 0.939693), vec3(-0.321394, 0.116978, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.433013, 0.250000, 0.866025), vec3(-0.433013, 0.250000, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.469846, 0.171010, 0.866025), vec3(-0.469846, 0.171010, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.556670, 0.321394, 0.766044), vec3(-0.556670, 0.321394, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.604023, 0.219846, 0.766044), vec3(-0.604023, 0.219846, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.663414, 0.383022, 0.642788), vec3(-0.663414, 0.383022, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.719846, 0.262003, 0.642788), vec3(-0.719846, 0.262003, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.750000, 0.433013, 0.500000), vec3(-0.750000, 0.433013, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.813798, 0.296198, 0.500000), vec3(-0.813798, 0.296198, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.813798, 0.469846, 0.342020), vec3(-0.813798, 0.469846, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.883022, 0.321394, 0.342020), vec3(-0.883022, 0.321394, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.852869, 0.492404, 0.173648), vec3(-0.852869, 0.492404, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.925417, 0.336824, 0.173648), vec3(-0.925417, 0.336824, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.866025, 0.500000, 0.000000), vec3(-0.866025, 0.500000, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.939693, 0.342020, 0.000000), vec3(-0.939693, 0.342020, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.852869, 0.492404, -0.173648), vec3(-0.852869, 0.492404, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.925417, 0.336824, -0.173648), vec3(-0.925417, 0.336824, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.813798, 0.469846, -0.342020), vec3(-0.813798, 0.469846, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.883022, 0.321394, -0.342020), vec3(-0.883022, 0.321394, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.750000, 0.433013, -0.500000), vec3(-0.750000, 0.433013, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.813798, 0.296198, -0.500000), vec3(-0.813798, 0.296198, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.663414, 0.383022, -0.642788), vec3(-0.663414, 0.383022, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.719846, 0.262003, -0.642788), vec3(-0.719846, 0.262003, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.556670, 0.321394, -0.766044), vec3(-0.556670, 0.321394, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.604023, 0.219846, -0.766044), vec3(-0.604023, 0.219846, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.433013, 0.250000, -0.866025), vec3(-0.433013, 0.250000, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.469846, 0.171010, -0.866025), vec3(-0.469846, 0.171010, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.296198, 0.171010, -0.939693), vec3(-0.296198, 0.171010, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.321394, 0.116978, -0.939693), vec3(-0.321394, 0.116978, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.150384, 0.086824, -0.984808), vec3(-0.150384, 0.086824, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.163176, 0.059391, -0.984808), vec3(-0.163176, 0.059391, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.000000, -1.000000), vec3(0.000000, 0.000000, -1.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.163176, 0.059391, -0.984808), vec3(-0.163176, 0.059391, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.171010, 0.030154, -0.984808), vec3(-0.171010, 0.030154, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.321394, 0.116978, -0.939693), vec3(-0.321394, 0.116978, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.336824, 0.059391, -0.939693), vec3(-0.336824, 0.059391, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.469846, 0.171010, -0.866025), vec3(-0.469846, 0.171010, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.492404, 0.086824, -0.866025), vec3(-0.492404, 0.086824, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.604023, 0.219846, -0.766044), vec3(-0.604023, 0.219846, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.633022, 0.111619, -0.766044), vec3(-0.633022, 0.111619, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.719846, 0.262003, -0.642788), vec3(-0.719846, 0.262003, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.754407, 0.133022, -0.642788), vec3(-0.754407, 0.133022, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.813798, 0.296198, -0.500000), vec3(-0.813798, 0.296198, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.852869, 0.150384, -0.500000), vec3(-0.852869, 0.150384, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.883022, 0.321394, -0.342020), vec3(-0.883022, 0.321394, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.925417, 0.163176, -0.342020), vec3(-0.925417, 0.163176, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.925417, 0.336824, -0.173648), vec3(-0.925417, 0.336824, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.969846, 0.171010, -0.173648), vec3(-0.969846, 0.171010, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.939693, 0.342020, 0.000000), vec3(-0.939693, 0.342020, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.984808, 0.173648, 0.000000), vec3(-0.984808, 0.173648, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.925417, 0.336824, 0.173648), vec3(-0.925417, 0.336824, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.969846, 0.171010, 0.173648), vec3(-0.969846, 0.171010, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.883022, 0.321394, 0.342020), vec3(-0.883022, 0.321394, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.925417, 0.163176, 0.342020), vec3(-0.925417, 0.163176, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.813798, 0.296198, 0.500000), vec3(-0.813798, 0.296198, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.852869, 0.150384, 0.500000), vec3(-0.852869, 0.150384, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.719846, 0.262003, 0.642788), vec3(-0.719846, 0.262003, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.754407, 0.133022, 0.642788), vec3(-0.754407, 0.133022, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.604023, 0.219846, 0.766044), vec3(-0.604023, 0.219846, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.633022, 0.111619, 0.766044), vec3(-0.633022, 0.111619, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.469846, 0.171010, 0.866025), vec3(-0.469846, 0.171010, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.492404, 0.086824, 0.866025), vec3(-0.492404, 0.086824, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.321394, 0.116978, 0.939693), vec3(-0.321394, 0.116978, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.336824, 0.059391, 0.939693), vec3(-0.336824, 0.059391, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.163176, 0.059391, 0.984808), vec3(-0.163176, 0.059391, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.171010, 0.030154, 0.984808), vec3(-0.171010, 0.030154, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.000000, 1.000000), vec3(0.000000, 0.000000, 1.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.171010, 0.030154, 0.984808), vec3(-0.171010, 0.030154, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.173648, 0.000000, 0.984808), vec3(-0.173648, 0.000000, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.336824, 0.059391, 0.939693), vec3(-0.336824, 0.059391, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.342020, 0.000000, 0.939693), vec3(-0.342020, 0.000000, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.492404, 0.086824, 0.866025), vec3(-0.492404, 0.086824, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.500000, 0.000000, 0.866025), vec3(-0.500000, 0.000000, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.633022, 0.111619, 0.766044), vec3(-0.633022, 0.111619, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.642788, 0.000000, 0.766044), vec3(-0.642788, 0.000000, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.754407, 0.133022, 0.642788), vec3(-0.754407, 0.133022, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.766044, 0.000000, 0.642788), vec3(-0.766044, 0.000000, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.852869, 0.150384, 0.500000), vec3(-0.852869, 0.150384, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.866025, 0.000000, 0.500000), vec3(-0.866025, 0.000000, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.925417, 0.163176, 0.342020), vec3(-0.925417, 0.163176, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.939693, 0.000000, 0.342020), vec3(-0.939693, 0.000000, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.969846, 0.171010, 0.173648), vec3(-0.969846, 0.171010, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.984808, 0.000000, 0.173648), vec3(-0.984808, 0.000000, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.984808, 0.173648, 0.000000), vec3(-0.984808, 0.173648, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-1.000000, 0.000000, 0.000000), vec3(-1.000000, 0.000000, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.969846, 0.171010, -0.173648), vec3(-0.969846, 0.171010, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.984808, 0.000000, -0.173648), vec3(-0.984808, 0.000000, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.925417, 0.163176, -0.342020), vec3(-0.925417, 0.163176, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.939693, 0.000000, -0.342020), vec3(-0.939693, 0.000000, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.852869, 0.150384, -0.500000), vec3(-0.852869, 0.150384, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.866025, 0.000000, -0.500000), vec3(-0.866025, 0.000000, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.754407, 0.133022, -0.642788), vec3(-0.754407, 0.133022, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.766044, 0.000000, -0.642788), vec3(-0.766044, 0.000000, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.633022, 0.111619, -0.766044), vec3(-0.633022, 0.111619, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.642788, 0.000000, -0.766044), vec3(-0.642788, 0.000000, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.492404, 0.086824, -0.866025), vec3(-0.492404, 0.086824, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.500000, 0.000000, -0.866025), vec3(-0.500000, 0.000000, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.336824, 0.059391, -0.939693), vec3(-0.336824, 0.059391, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.342020, 0.000000, -0.939693), vec3(-0.342020, 0.000000, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.171010, 0.030154, -0.984808), vec3(-0.171010, 0.030154, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.173648, 0.000000, -0.984808), vec3(-0.173648, 0.000000, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.000000, -1.000000), vec3(0.000000, 0.000000, -1.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.173648, 0.000000, -0.984808), vec3(-0.173648, 0.000000, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.171010, -0.030154, -0.984808), vec3(-0.171010, -0.030154, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.342020, 0.000000, -0.939693), vec3(-0.342020, 0.000000, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.336824, -0.059391, -0.939693), vec3(-0.336824, -0.059391, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.500000, 0.000000, -0.866025), vec3(-0.500000, 0.000000, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.492404, -0.086824, -0.866025), vec3(-0.492404, -0.086824, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.642788, 0.000000, -0.766044), vec3(-0.642788, 0.000000, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.633022, -0.111619, -0.766044), vec3(-0.633022, -0.111619, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.766044, 0.000000, -0.642788), vec3(-0.766044, 0.000000, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.754407, -0.133022, -0.642788), vec3(-0.754407, -0.133022, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.866025, 0.000000, -0.500000), vec3(-0.866025, 0.000000, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.852869, -0.150384, -0.500000), vec3(-0.852869, -0.150384, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.939693, 0.000000, -0.342020), vec3(-0.939693, 0.000000, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.925417, -0.163176, -0.342020), vec3(-0.925417, -0.163176, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.984808, 0.000000, -0.173648), vec3(-0.984808, 0.000000, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.969846, -0.171010, -0.173648), vec3(-0.969846, -0.171010, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-1.000000, 0.000000, 0.000000), vec3(-1.000000, 0.000000, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.984808, -0.173648, 0.000000), vec3(-0.984808, -0.173648, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.984808, 0.000000, 0.173648), vec3(-0.984808, 0.000000, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.969846, -0.171010, 0.173648), vec3(-0.969846, -0.171010, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.939693, 0.000000, 0.342020), vec3(-0.939693, 0.000000, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.925417, -0.163176, 0.342020), vec3(-0.925417, -0.163176, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.866025, 0.000000, 0.500000), vec3(-0.866025, 0.000000, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.852869, -0.150384, 0.500000), vec3(-0.852869, -0.150384, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.766044, 0.000000, 0.642788), vec3(-0.766044, 0.000000, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.754407, -0.133022, 0.642788), vec3(-0.754407, -0.133022, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.642788, 0.000000, 0.766044), vec3(-0.642788, 0.000000, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.633022, -0.111619, 0.766044), vec3(-0.633022, -0.111619, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.500000, 0.000000, 0.866025), vec3(-0.500000, 0.000000, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.492404, -0.086824, 0.866025), vec3(-0.492404, -0.086824, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.342020, 0.000000, 0.939693), vec3(-0.342020, 0.000000, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.336824, -0.059391, 0.939693), vec3(-0.336824, -0.059391, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.173648, 0.000000, 0.984808), vec3(-0.173648, 0.000000, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.171010, -0.030154, 0.984808), vec3(-0.171010, -0.030154, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.000000, 1.000000), vec3(0.000000, 0.000000, 1.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.171010, -0.030154, 0.984808), vec3(-0.171010, -0.030154, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.163176, -0.059391, 0.984808), vec3(-0.163176, -0.059391, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.336824, -0.059391, 0.939693), vec3(-0.336824, -0.059391, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.321394, -0.116978, 0.939693), vec3(-0.321394, -0.116978, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.492404, -0.086824, 0.866025), vec3(-0.492404, -0.086824, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.469846, -0.171010, 0.866025), vec3(-0.469846, -0.171010, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.633022, -0.111619, 0.766044), vec3(-0.633022, -0.111619, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.604023, -0.219846, 0.766044), vec3(-0.604023, -0.219846, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.754407, -0.133022, 0.642788), vec3(-0.754407, -0.133022, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.719846, -0.262003, 0.642788), vec3(-0.719846, -0.262003, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.852869, -0.150384, 0.500000), vec3(-0.852869, -0.150384, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.813798, -0.296198, 0.500000), vec3(-0.813798, -0.296198, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.925417, -0.163176, 0.342020), vec3(-0.925417, -0.163176, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.883022, -0.321394, 0.342020), vec3(-0.883022, -0.321394, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.969846, -0.171010, 0.173648), vec3(-0.969846, -0.171010, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.925417, -0.336824, 0.173648), vec3(-0.925417, -0.336824, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.984808, -0.173648, 0.000000), vec3(-0.984808, -0.173648, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.939693, -0.342020, 0.000000), vec3(-0.939693, -0.342020, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.969846, -0.171010, -0.173648), vec3(-0.969846, -0.171010, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.925417, -0.336824, -0.173648), vec3(-0.925417, -0.336824, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.925417, -0.163176, -0.342020), vec3(-0.925417, -0.163176, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.883022, -0.321394, -0.342020), vec3(-0.883022, -0.321394, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.852869, -0.150384, -0.500000), vec3(-0.852869, -0.150384, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.813798, -0.296198, -0.500000), vec3(-0.813798, -0.296198, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.754407, -0.133022, -0.642788), vec3(-0.754407, -0.133022, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.719846, -0.262003, -0.642788), vec3(-0.719846, -0.262003, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.633022, -0.111619, -0.766044), vec3(-0.633022, -0.111619, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.604023, -0.219846, -0.766044), vec3(-0.604023, -0.219846, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.492404, -0.086824, -0.866025), vec3(-0.492404, -0.086824, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.469846, -0.171010, -0.866025), vec3(-0.469846, -0.171010, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.336824, -0.059391, -0.939693), vec3(-0.336824, -0.059391, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.321394, -0.116978, -0.939693), vec3(-0.321394, -0.116978, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.171010, -0.030154, -0.984808), vec3(-0.171010, -0.030154, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.163176, -0.059391, -0.984808), vec3(-0.163176, -0.059391, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.000000, -1.000000), vec3(0.000000, 0.000000, -1.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.163176, -0.059391, -0.984808), vec3(-0.163176, -0.059391, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.150384, -0.086824, -0.984808), vec3(-0.150384, -0.086824, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.321394, -0.116978, -0.939693), vec3(-0.321394, -0.116978, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.296198, -0.171010, -0.939693), vec3(-0.296198, -0.171010, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.469846, -0.171010, -0.866025), vec3(-0.469846, -0.171010, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.433013, -0.250000, -0.866025), vec3(-0.433013, -0.250000, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.604023, -0.219846, -0.766044), vec3(-0.604023, -0.219846, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.556670, -0.321394, -0.766044), vec3(-0.556670, -0.321394, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.719846, -0.262003, -0.642788), vec3(-0.719846, -0.262003, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.663414, -0.383022, -0.642788), vec3(-0.663414, -0.383022, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.813798, -0.296198, -0.500000), vec3(-0.813798, -0.296198, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.750000, -0.433013, -0.500000), vec3(-0.750000, -0.433013, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.883022, -0.321394, -0.342020), vec3(-0.883022, -0.321394, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.813798, -0.469846, -0.342020), vec3(-0.813798, -0.469846, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.925417, -0.336824, -0.173648), vec3(-0.925417, -0.336824, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.852869, -0.492404, -0.173648), vec3(-0.852869, -0.492404, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.939693, -0.342020, 0.000000), vec3(-0.939693, -0.342020, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.866025, -0.500000, 0.000000), vec3(-0.866025, -0.500000, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.925417, -0.336824, 0.173648), vec3(-0.925417, -0.336824, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.852869, -0.492404, 0.173648), vec3(-0.852869, -0.492404, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.883022, -0.321394, 0.342020), vec3(-0.883022, -0.321394, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.813798, -0.469846, 0.342020), vec3(-0.813798, -0.469846, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.813798, -0.296198, 0.500000), vec3(-0.813798, -0.296198, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.750000, -0.433013, 0.500000), vec3(-0.750000, -0.433013, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.719846, -0.262003, 0.642788), vec3(-0.719846, -0.262003, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.663414, -0.383022, 0.642788), vec3(-0.663414, -0.383022, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.604023, -0.219846, 0.766044), vec3(-0.604023, -0.219846, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.556670, -0.321394, 0.766044), vec3(-0.556670, -0.321394, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.469846, -0.171010, 0.866025), vec3(-0.469846, -0.171010, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.433013, -0.250000, 0.866025), vec3(-0.433013, -0.250000, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.321394, -0.116978, 0.939693), vec3(-0.321394, -0.116978, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.296198, -0.171010, 0.939693), vec3(-0.296198, -0.171010, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.163176, -0.059391, 0.984808), vec3(-0.163176, -0.059391, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.150384, -0.086824, 0.984808), vec3(-0.150384, -0.086824, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.000000, 1.000000), vec3(0.000000, 0.000000, 1.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.150384, -0.086824, 0.984808), vec3(-0.150384, -0.086824, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.133022, -0.111619, 0.984808), vec3(-0.133022, -0.111619, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.296198, -0.171010, 0.939693), vec3(-0.296198, -0.171010, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.262003, -0.219846, 0.939693), vec3(-0.262003, -0.219846, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.433013, -0.250000, 0.866025), vec3(-0.433013, -0.250000, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.383022, -0.321394, 0.866025), vec3(-0.383022, -0.321394, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.556670, -0.321394, 0.766044), vec3(-0.556670, -0.321394, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.492404, -0.413176, 0.766044), vec3(-0.492404, -0.413176, 0.766045), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.663414, -0.383022, 0.642788), vec3(-0.663414, -0.383022, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.586824, -0.492404, 0.642788), vec3(-0.586824, -0.492404, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.750000, -0.433013, 0.500000), vec3(-0.750000, -0.433013, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.663414, -0.556670, 0.500000), vec3(-0.663414, -0.556670, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.813798, -0.469846, 0.342020), vec3(-0.813798, -0.469846, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.719846, -0.604023, 0.342020), vec3(-0.719846, -0.604023, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.852869, -0.492404, 0.173648), vec3(-0.852869, -0.492404, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.754407, -0.633022, 0.173648), vec3(-0.754407, -0.633022, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.866025, -0.500000, 0.000000), vec3(-0.866025, -0.500000, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.766044, -0.642788, 0.000000), vec3(-0.766044, -0.642788, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.852869, -0.492404, -0.173648), vec3(-0.852869, -0.492404, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.754407, -0.633022, -0.173648), vec3(-0.754407, -0.633022, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.813798, -0.469846, -0.342020), vec3(-0.813798, -0.469846, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.719846, -0.604023, -0.342020), vec3(-0.719846, -0.604023, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.750000, -0.433013, -0.500000), vec3(-0.750000, -0.433013, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.663414, -0.556670, -0.500000), vec3(-0.663414, -0.556670, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.663414, -0.383022, -0.642788), vec3(-0.663414, -0.383022, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.586824, -0.492404, -0.642788), vec3(-0.586824, -0.492404, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.556670, -0.321394, -0.766044), vec3(-0.556670, -0.321394, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.492404, -0.413176, -0.766044), vec3(-0.492404, -0.413176, -0.766045), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.433013, -0.250000, -0.866025), vec3(-0.433013, -0.250000, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.383022, -0.321394, -0.866025), vec3(-0.383022, -0.321394, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.296198, -0.171010, -0.939693), vec3(-0.296198, -0.171010, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.262003, -0.219846, -0.939693), vec3(-0.262003, -0.219846, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.150384, -0.086824, -0.984808), vec3(-0.150384, -0.086824, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.133022, -0.111619, -0.984808), vec3(-0.133022, -0.111619, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.000000, -1.000000), vec3(0.000000, 0.000000, -1.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.133022, -0.111619, -0.984808), vec3(-0.133022, -0.111619, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.111619, -0.133022, -0.984808), vec3(-0.111619, -0.133022, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.262003, -0.219846, -0.939693), vec3(-0.262003, -0.219846, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.219846, -0.262003, -0.939693), vec3(-0.219846, -0.262003, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.383022, -0.321394, -0.866025), vec3(-0.383022, -0.321394, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.321394, -0.383022, -0.866025), vec3(-0.321394, -0.383022, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.492404, -0.413176, -0.766044), vec3(-0.492404, -0.413176, -0.766045), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.413176, -0.492404, -0.766044), vec3(-0.413176, -0.492404, -0.766045), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.586824, -0.492404, -0.642788), vec3(-0.586824, -0.492404, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.492404, -0.586824, -0.642788), vec3(-0.492404, -0.586824, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.663414, -0.556670, -0.500000), vec3(-0.663414, -0.556670, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.556670, -0.663414, -0.500000), vec3(-0.556670, -0.663414, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.719846, -0.604023, -0.342020), vec3(-0.719846, -0.604023, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.604023, -0.719846, -0.342020), vec3(-0.604023, -0.719846, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.754407, -0.633022, -0.173648), vec3(-0.754407, -0.633022, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.633022, -0.754407, -0.173648), vec3(-0.633022, -0.754407, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.766044, -0.642788, 0.000000), vec3(-0.766044, -0.642788, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.642788, -0.766044, 0.000000), vec3(-0.642788, -0.766044, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.754407, -0.633022, 0.173648), vec3(-0.754407, -0.633022, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.633022, -0.754407, 0.173648), vec3(-0.633022, -0.754407, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.719846, -0.604023, 0.342020), vec3(-0.719846, -0.604023, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.604023, -0.719846, 0.342020), vec3(-0.604023, -0.719846, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.663414, -0.556670, 0.500000), vec3(-0.663414, -0.556670, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.556670, -0.663414, 0.500000), vec3(-0.556670, -0.663414, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.586824, -0.492404, 0.642788), vec3(-0.586824, -0.492404, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.492404, -0.586824, 0.642788), vec3(-0.492404, -0.586824, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.492404, -0.413176, 0.766044), vec3(-0.492404, -0.413176, 0.766045), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.413176, -0.492404, 0.766044), vec3(-0.413176, -0.492404, 0.766045), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.383022, -0.321394, 0.866025), vec3(-0.383022, -0.321394, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.321394, -0.383022, 0.866025), vec3(-0.321394, -0.383022, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.262003, -0.219846, 0.939693), vec3(-0.262003, -0.219846, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.219846, -0.262003, 0.939693), vec3(-0.219846, -0.262003, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.133022, -0.111619, 0.984808), vec3(-0.133022, -0.111619, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.111619, -0.133022, 0.984808), vec3(-0.111619, -0.133022, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.000000, 1.000000), vec3(0.000000, 0.000000, 1.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.111619, -0.133022, 0.984808), vec3(-0.111619, -0.133022, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.086824, -0.150384, 0.984808), vec3(-0.086824, -0.150384, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.219846, -0.262003, 0.939693), vec3(-0.219846, -0.262003, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.171010, -0.296198, 0.939693), vec3(-0.171010, -0.296198, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.321394, -0.383022, 0.866025), vec3(-0.321394, -0.383022, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.250000, -0.433013, 0.866025), vec3(-0.250000, -0.433013, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.413176, -0.492404, 0.766044), vec3(-0.413176, -0.492404, 0.766045), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.321394, -0.556670, 0.766044), vec3(-0.321394, -0.556670, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.492404, -0.586824, 0.642788), vec3(-0.492404, -0.586824, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.383022, -0.663414, 0.642788), vec3(-0.383022, -0.663414, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.556670, -0.663414, 0.500000), vec3(-0.556670, -0.663414, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.433013, -0.750000, 0.500000), vec3(-0.433013, -0.750000, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.604023, -0.719846, 0.342020), vec3(-0.604023, -0.719846, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.469846, -0.813798, 0.342020), vec3(-0.469846, -0.813798, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.633022, -0.754407, 0.173648), vec3(-0.633022, -0.754407, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.492404, -0.852869, 0.173648), vec3(-0.492404, -0.852869, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.642788, -0.766044, 0.000000), vec3(-0.642788, -0.766044, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.500000, -0.866025, 0.000000), vec3(-0.500000, -0.866025, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.633022, -0.754407, -0.173648), vec3(-0.633022, -0.754407, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.492404, -0.852869, -0.173648), vec3(-0.492404, -0.852869, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.604023, -0.719846, -0.342020), vec3(-0.604023, -0.719846, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.469846, -0.813798, -0.342020), vec3(-0.469846, -0.813798, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.556670, -0.663414, -0.500000), vec3(-0.556670, -0.663414, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.433013, -0.750000, -0.500000), vec3(-0.433013, -0.750000, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.492404, -0.586824, -0.642788), vec3(-0.492404, -0.586824, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.383022, -0.663414, -0.642788), vec3(-0.383022, -0.663414, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.413176, -0.492404, -0.766044), vec3(-0.413176, -0.492404, -0.766045), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.321394, -0.556670, -0.766044), vec3(-0.321394, -0.556670, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.321394, -0.383022, -0.866025), vec3(-0.321394, -0.383022, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.250000, -0.433013, -0.866025), vec3(-0.250000, -0.433013, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.219846, -0.262003, -0.939693), vec3(-0.219846, -0.262003, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.171010, -0.296198, -0.939693), vec3(-0.171010, -0.296198, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.111619, -0.133022, -0.984808), vec3(-0.111619, -0.133022, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.086824, -0.150384, -0.984808), vec3(-0.086824, -0.150384, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.000000, -1.000000), vec3(0.000000, 0.000000, -1.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.086824, -0.150384, -0.984808), vec3(-0.086824, -0.150384, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.059391, -0.163176, -0.984808), vec3(-0.059391, -0.163176, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.171010, -0.296198, -0.939693), vec3(-0.171010, -0.296198, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.116978, -0.321394, -0.939693), vec3(-0.116978, -0.321394, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.250000, -0.433013, -0.866025), vec3(-0.250000, -0.433013, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.171010, -0.469846, -0.866025), vec3(-0.171010, -0.469846, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.321394, -0.556670, -0.766044), vec3(-0.321394, -0.556670, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.219846, -0.604023, -0.766044), vec3(-0.219846, -0.604023, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.383022, -0.663414, -0.642788), vec3(-0.383022, -0.663414, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.262003, -0.719846, -0.642788), vec3(-0.262003, -0.719846, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.433013, -0.750000, -0.500000), vec3(-0.433013, -0.750000, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.296198, -0.813798, -0.500000), vec3(-0.296198, -0.813798, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.469846, -0.813798, -0.342020), vec3(-0.469846, -0.813798, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.321394, -0.883022, -0.342020), vec3(-0.321394, -0.883022, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.492404, -0.852869, -0.173648), vec3(-0.492404, -0.852869, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.336824, -0.925417, -0.173648), vec3(-0.336824, -0.925417, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.500000, -0.866025, 0.000000), vec3(-0.500000, -0.866025, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.342020, -0.939693, 0.000000), vec3(-0.342020, -0.939693, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.492404, -0.852869, 0.173648), vec3(-0.492404, -0.852869, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.336824, -0.925417, 0.173648), vec3(-0.336824, -0.925417, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.469846, -0.813798, 0.342020), vec3(-0.469846, -0.813798, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.321394, -0.883022, 0.342020), vec3(-0.321394, -0.883022, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.433013, -0.750000, 0.500000), vec3(-0.433013, -0.750000, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.296198, -0.813798, 0.500000), vec3(-0.296198, -0.813798, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.383022, -0.663414, 0.642788), vec3(-0.383022, -0.663414, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.262003, -0.719846, 0.642788), vec3(-0.262003, -0.719846, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.321394, -0.556670, 0.766044), vec3(-0.321394, -0.556670, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.219846, -0.604023, 0.766044), vec3(-0.219846, -0.604023, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.250000, -0.433013, 0.866025), vec3(-0.250000, -0.433013, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.171010, -0.469846, 0.866025), vec3(-0.171010, -0.469846, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.171010, -0.296198, 0.939693), vec3(-0.171010, -0.296198, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.116978, -0.321394, 0.939693), vec3(-0.116978, -0.321394, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.086824, -0.150384, 0.984808), vec3(-0.086824, -0.150384, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.059391, -0.163176, 0.984808), vec3(-0.059391, -0.163176, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.000000, 1.000000), vec3(0.000000, 0.000000, 1.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.059391, -0.163176, 0.984808), vec3(-0.059391, -0.163176, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.030154, -0.171010, 0.984808), vec3(-0.030154, -0.171010, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.116978, -0.321394, 0.939693), vec3(-0.116978, -0.321394, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.059391, -0.336824, 0.939693), vec3(-0.059391, -0.336824, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.171010, -0.469846, 0.866025), vec3(-0.171010, -0.469846, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.086824, -0.492404, 0.866025), vec3(-0.086824, -0.492404, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.219846, -0.604023, 0.766044), vec3(-0.219846, -0.604023, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.111619, -0.633022, 0.766044), vec3(-0.111619, -0.633022, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.262003, -0.719846, 0.642788), vec3(-0.262003, -0.719846, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.133022, -0.754407, 0.642788), vec3(-0.133022, -0.754407, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.296198, -0.813798, 0.500000), vec3(-0.296198, -0.813798, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.150384, -0.852869, 0.500000), vec3(-0.150384, -0.852869, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.321394, -0.883022, 0.342020), vec3(-0.321394, -0.883022, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.163176, -0.925417, 0.342020), vec3(-0.163176, -0.925417, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.336824, -0.925417, 0.173648), vec3(-0.336824, -0.925417, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.171010, -0.969846, 0.173648), vec3(-0.171010, -0.969846, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.342020, -0.939693, 0.000000), vec3(-0.342020, -0.939693, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.173648, -0.984808, 0.000000), vec3(-0.173648, -0.984808, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.336824, -0.925417, -0.173648), vec3(-0.336824, -0.925417, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.171010, -0.969846, -0.173648), vec3(-0.171010, -0.969846, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.321394, -0.883022, -0.342020), vec3(-0.321394, -0.883022, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.163176, -0.925417, -0.342020), vec3(-0.163176, -0.925417, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.296198, -0.813798, -0.500000), vec3(-0.296198, -0.813798, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.150384, -0.852869, -0.500000), vec3(-0.150384, -0.852869, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.262003, -0.719846, -0.642788), vec3(-0.262003, -0.719846, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.133022, -0.754407, -0.642788), vec3(-0.133022, -0.754407, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.219846, -0.604023, -0.766044), vec3(-0.219846, -0.604023, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.111619, -0.633022, -0.766044), vec3(-0.111619, -0.633022, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.171010, -0.469846, -0.866025), vec3(-0.171010, -0.469846, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.086824, -0.492404, -0.866025), vec3(-0.086824, -0.492404, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.116978, -0.321394, -0.939693), vec3(-0.116978, -0.321394, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.059391, -0.336824, -0.939693), vec3(-0.059391, -0.336824, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.059391, -0.163176, -0.984808), vec3(-0.059391, -0.163176, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.030154, -0.171010, -0.984808), vec3(-0.030154, -0.171010, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.000000, -1.000000), vec3(0.000000, 0.000000, -1.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.030154, -0.171010, -0.984808), vec3(-0.030154, -0.171010, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.000000, -0.173648, -0.984808), vec3(-0.000000, -0.173648, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.059391, -0.336824, -0.939693), vec3(-0.059391, -0.336824, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.000000, -0.342020, -0.939693), vec3(-0.000000, -0.342020, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.086824, -0.492404, -0.866025), vec3(-0.086824, -0.492404, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.000000, -0.500000, -0.866025), vec3(-0.000000, -0.500000, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.111619, -0.633022, -0.766044), vec3(-0.111619, -0.633022, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.000000, -0.642788, -0.766044), vec3(-0.000000, -0.642788, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.133022, -0.754407, -0.642788), vec3(-0.133022, -0.754407, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.000000, -0.766044, -0.642788), vec3(-0.000000, -0.766044, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.150384, -0.852869, -0.500000), vec3(-0.150384, -0.852869, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.000000, -0.866025, -0.500000), vec3(-0.000000, -0.866025, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.163176, -0.925417, -0.342020), vec3(-0.163176, -0.925417, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.000000, -0.939693, -0.342020), vec3(-0.000000, -0.939693, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.171010, -0.969846, -0.173648), vec3(-0.171010, -0.969846, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.000000, -0.984808, -0.173648), vec3(-0.000000, -0.984808, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.173648, -0.984808, 0.000000), vec3(-0.173648, -0.984808, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.000000, -1.000000, 0.000000), vec3(-0.000000, -1.000000, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.171010, -0.969846, 0.173648), vec3(-0.171010, -0.969846, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.000000, -0.984808, 0.173648), vec3(-0.000000, -0.984808, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.163176, -0.925417, 0.342020), vec3(-0.163176, -0.925417, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.000000, -0.939693, 0.342020), vec3(-0.000000, -0.939693, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.150384, -0.852869, 0.500000), vec3(-0.150384, -0.852869, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.000000, -0.866025, 0.500000), vec3(-0.000000, -0.866025, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.133022, -0.754407, 0.642788), vec3(-0.133022, -0.754407, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.000000, -0.766044, 0.642788), vec3(-0.000000, -0.766044, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.111619, -0.633022, 0.766044), vec3(-0.111619, -0.633022, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.000000, -0.642788, 0.766044), vec3(-0.000000, -0.642788, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.086824, -0.492404, 0.866025), vec3(-0.086824, -0.492404, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.000000, -0.500000, 0.866025), vec3(-0.000000, -0.500000, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.059391, -0.336824, 0.939693), vec3(-0.059391, -0.336824, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.000000, -0.342020, 0.939693), vec3(-0.000000, -0.342020, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.030154, -0.171010, 0.984808), vec3(-0.030154, -0.171010, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.000000, -0.173648, 0.984808), vec3(-0.000000, -0.173648, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.000000, 1.000000), vec3(0.000000, 0.000000, 1.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.000000, -0.173648, 0.984808), vec3(-0.000000, -0.173648, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.030154, -0.171010, 0.984808), vec3(0.030154, -0.171010, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.000000, -0.342020, 0.939693), vec3(-0.000000, -0.342020, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.059391, -0.336824, 0.939693), vec3(0.059391, -0.336824, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.000000, -0.500000, 0.866025), vec3(-0.000000, -0.500000, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.086824, -0.492404, 0.866025), vec3(0.086824, -0.492404, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.000000, -0.642788, 0.766044), vec3(-0.000000, -0.642788, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.111619, -0.633022, 0.766044), vec3(0.111619, -0.633022, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.000000, -0.766044, 0.642788), vec3(-0.000000, -0.766044, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.133022, -0.754407, 0.642788), vec3(0.133022, -0.754407, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.000000, -0.866025, 0.500000), vec3(-0.000000, -0.866025, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.150384, -0.852869, 0.500000), vec3(0.150384, -0.852869, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.000000, -0.939693, 0.342020), vec3(-0.000000, -0.939693, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.163176, -0.925417, 0.342020), vec3(0.163176, -0.925417, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.000000, -0.984808, 0.173648), vec3(-0.000000, -0.984808, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.171010, -0.969846, 0.173648), vec3(0.171010, -0.969846, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.000000, -1.000000, 0.000000), vec3(-0.000000, -1.000000, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.173648, -0.984808, 0.000000), vec3(0.173648, -0.984808, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.000000, -0.984808, -0.173648), vec3(-0.000000, -0.984808, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.171010, -0.969846, -0.173648), vec3(0.171010, -0.969846, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.000000, -0.939693, -0.342020), vec3(-0.000000, -0.939693, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.163176, -0.925417, -0.342020), vec3(0.163176, -0.925417, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.000000, -0.866025, -0.500000), vec3(-0.000000, -0.866025, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.150384, -0.852869, -0.500000), vec3(0.150384, -0.852869, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.000000, -0.766044, -0.642788), vec3(-0.000000, -0.766044, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.133022, -0.754407, -0.642788), vec3(0.133022, -0.754407, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.000000, -0.642788, -0.766044), vec3(-0.000000, -0.642788, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.111619, -0.633022, -0.766044), vec3(0.111619, -0.633022, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.000000, -0.500000, -0.866025), vec3(-0.000000, -0.500000, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.086824, -0.492404, -0.866025), vec3(0.086824, -0.492404, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.000000, -0.342020, -0.939693), vec3(-0.000000, -0.342020, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.059391, -0.336824, -0.939693), vec3(0.059391, -0.336824, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(-0.000000, -0.173648, -0.984808), vec3(-0.000000, -0.173648, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.030154, -0.171010, -0.984808), vec3(0.030154, -0.171010, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.000000, -1.000000), vec3(0.000000, 0.000000, -1.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.030154, -0.171010, -0.984808), vec3(0.030154, -0.171010, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.059391, -0.163176, -0.984808), vec3(0.059391, -0.163176, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.059391, -0.336824, -0.939693), vec3(0.059391, -0.336824, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.116978, -0.321394, -0.939693), vec3(0.116978, -0.321394, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.086824, -0.492404, -0.866025), vec3(0.086824, -0.492404, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.171010, -0.469846, -0.866025), vec3(0.171010, -0.469846, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.111619, -0.633022, -0.766044), vec3(0.111619, -0.633022, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.219846, -0.604023, -0.766044), vec3(0.219846, -0.604023, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.133022, -0.754407, -0.642788), vec3(0.133022, -0.754407, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.262003, -0.719846, -0.642788), vec3(0.262003, -0.719846, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.150384, -0.852869, -0.500000), vec3(0.150384, -0.852869, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.296198, -0.813798, -0.500000), vec3(0.296198, -0.813798, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.163176, -0.925417, -0.342020), vec3(0.163176, -0.925417, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.321394, -0.883022, -0.342020), vec3(0.321394, -0.883022, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.171010, -0.969846, -0.173648), vec3(0.171010, -0.969846, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.336824, -0.925417, -0.173648), vec3(0.336824, -0.925417, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.173648, -0.984808, 0.000000), vec3(0.173648, -0.984808, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.342020, -0.939693, 0.000000), vec3(0.342020, -0.939693, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.171010, -0.969846, 0.173648), vec3(0.171010, -0.969846, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.336824, -0.925417, 0.173648), vec3(0.336824, -0.925417, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.163176, -0.925417, 0.342020), vec3(0.163176, -0.925417, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.321394, -0.883022, 0.342020), vec3(0.321394, -0.883022, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.150384, -0.852869, 0.500000), vec3(0.150384, -0.852869, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.296198, -0.813798, 0.500000), vec3(0.296198, -0.813798, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.133022, -0.754407, 0.642788), vec3(0.133022, -0.754407, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.262003, -0.719846, 0.642788), vec3(0.262003, -0.719846, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.111619, -0.633022, 0.766044), vec3(0.111619, -0.633022, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.219846, -0.604023, 0.766044), vec3(0.219846, -0.604023, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.086824, -0.492404, 0.866025), vec3(0.086824, -0.492404, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.171010, -0.469846, 0.866025), vec3(0.171010, -0.469846, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.059391, -0.336824, 0.939693), vec3(0.059391, -0.336824, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.116978, -0.321394, 0.939693), vec3(0.116978, -0.321394, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.030154, -0.171010, 0.984808), vec3(0.030154, -0.171010, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.059391, -0.163176, 0.984808), vec3(0.059391, -0.163176, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.000000, 1.000000), vec3(0.000000, 0.000000, 1.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.059391, -0.163176, 0.984808), vec3(0.059391, -0.163176, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.086824, -0.150384, 0.984808), vec3(0.086824, -0.150384, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.116978, -0.321394, 0.939693), vec3(0.116978, -0.321394, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.171010, -0.296198, 0.939693), vec3(0.171010, -0.296198, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.171010, -0.469846, 0.866025), vec3(0.171010, -0.469846, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.250000, -0.433013, 0.866025), vec3(0.250000, -0.433013, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.219846, -0.604023, 0.766044), vec3(0.219846, -0.604023, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.321394, -0.556670, 0.766044), vec3(0.321394, -0.556670, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.262003, -0.719846, 0.642788), vec3(0.262003, -0.719846, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.383022, -0.663414, 0.642788), vec3(0.383022, -0.663414, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.296198, -0.813798, 0.500000), vec3(0.296198, -0.813798, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.433013, -0.750000, 0.500000), vec3(0.433013, -0.750000, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.321394, -0.883022, 0.342020), vec3(0.321394, -0.883022, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.469846, -0.813798, 0.342020), vec3(0.469846, -0.813798, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.336824, -0.925417, 0.173648), vec3(0.336824, -0.925417, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.492404, -0.852869, 0.173648), vec3(0.492404, -0.852869, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.342020, -0.939693, 0.000000), vec3(0.342020, -0.939693, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.500000, -0.866025, 0.000000), vec3(0.500000, -0.866025, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.336824, -0.925417, -0.173648), vec3(0.336824, -0.925417, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.492404, -0.852869, -0.173648), vec3(0.492404, -0.852869, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.321394, -0.883022, -0.342020), vec3(0.321394, -0.883022, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.469846, -0.813798, -0.342020), vec3(0.469846, -0.813798, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.296198, -0.813798, -0.500000), vec3(0.296198, -0.813798, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.433013, -0.750000, -0.500000), vec3(0.433013, -0.750000, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.262003, -0.719846, -0.642788), vec3(0.262003, -0.719846, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.383022, -0.663414, -0.642788), vec3(0.383022, -0.663414, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.219846, -0.604023, -0.766044), vec3(0.219846, -0.604023, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.321394, -0.556670, -0.766044), vec3(0.321394, -0.556670, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.171010, -0.469846, -0.866025), vec3(0.171010, -0.469846, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.250000, -0.433013, -0.866025), vec3(0.250000, -0.433013, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.116978, -0.321394, -0.939693), vec3(0.116978, -0.321394, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.171010, -0.296198, -0.939693), vec3(0.171010, -0.296198, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.059391, -0.163176, -0.984808), vec3(0.059391, -0.163176, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.086824, -0.150384, -0.984808), vec3(0.086824, -0.150384, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.000000, -1.000000), vec3(0.000000, 0.000000, -1.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.086824, -0.150384, -0.984808), vec3(0.086824, -0.150384, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.111619, -0.133022, -0.984808), vec3(0.111619, -0.133022, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.171010, -0.296198, -0.939693), vec3(0.171010, -0.296198, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.219846, -0.262003, -0.939693), vec3(0.219846, -0.262003, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.250000, -0.433013, -0.866025), vec3(0.250000, -0.433013, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.321394, -0.383022, -0.866025), vec3(0.321394, -0.383022, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.321394, -0.556670, -0.766044), vec3(0.321394, -0.556670, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.413176, -0.492404, -0.766044), vec3(0.413176, -0.492404, -0.766045), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.383022, -0.663414, -0.642788), vec3(0.383022, -0.663414, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.492404, -0.586824, -0.642788), vec3(0.492404, -0.586824, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.433013, -0.750000, -0.500000), vec3(0.433013, -0.750000, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.556670, -0.663414, -0.500000), vec3(0.556670, -0.663414, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.469846, -0.813798, -0.342020), vec3(0.469846, -0.813798, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.604023, -0.719846, -0.342020), vec3(0.604023, -0.719846, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.492404, -0.852869, -0.173648), vec3(0.492404, -0.852869, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.633022, -0.754407, -0.173648), vec3(0.633022, -0.754407, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.500000, -0.866025, 0.000000), vec3(0.500000, -0.866025, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.642788, -0.766044, 0.000000), vec3(0.642788, -0.766044, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.492404, -0.852869, 0.173648), vec3(0.492404, -0.852869, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.633022, -0.754407, 0.173648), vec3(0.633022, -0.754407, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.469846, -0.813798, 0.342020), vec3(0.469846, -0.813798, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.604023, -0.719846, 0.342020), vec3(0.604023, -0.719846, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.433013, -0.750000, 0.500000), vec3(0.433013, -0.750000, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.556670, -0.663414, 0.500000), vec3(0.556670, -0.663414, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.383022, -0.663414, 0.642788), vec3(0.383022, -0.663414, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.492404, -0.586824, 0.642788), vec3(0.492404, -0.586824, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.321394, -0.556670, 0.766044), vec3(0.321394, -0.556670, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.413176, -0.492404, 0.766044), vec3(0.413176, -0.492404, 0.766045), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.250000, -0.433013, 0.866025), vec3(0.250000, -0.433013, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.321394, -0.383022, 0.866025), vec3(0.321394, -0.383022, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.171010, -0.296198, 0.939693), vec3(0.171010, -0.296198, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.219846, -0.262003, 0.939693), vec3(0.219846, -0.262003, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.086824, -0.150384, 0.984808), vec3(0.086824, -0.150384, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.111619, -0.133022, 0.984808), vec3(0.111619, -0.133022, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.000000, 1.000000), vec3(0.000000, 0.000000, 1.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.111619, -0.133022, 0.984808), vec3(0.111619, -0.133022, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.133022, -0.111619, 0.984808), vec3(0.133022, -0.111619, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.219846, -0.262003, 0.939693), vec3(0.219846, -0.262003, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.262003, -0.219846, 0.939693), vec3(0.262003, -0.219846, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.321394, -0.383022, 0.866025), vec3(0.321394, -0.383022, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.383022, -0.321394, 0.866025), vec3(0.383022, -0.321394, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.413176, -0.492404, 0.766044), vec3(0.413176, -0.492404, 0.766045), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.492404, -0.413176, 0.766044), vec3(0.492404, -0.413176, 0.766045), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.492404, -0.586824, 0.642788), vec3(0.492404, -0.586824, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.586824, -0.492404, 0.642788), vec3(0.586824, -0.492404, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.556670, -0.663414, 0.500000), vec3(0.556670, -0.663414, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.663414, -0.556670, 0.500000), vec3(0.663414, -0.556670, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.604023, -0.719846, 0.342020), vec3(0.604023, -0.719846, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.719846, -0.604023, 0.342020), vec3(0.719846, -0.604023, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.633022, -0.754407, 0.173648), vec3(0.633022, -0.754407, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.754407, -0.633022, 0.173648), vec3(0.754407, -0.633022, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.642788, -0.766044, 0.000000), vec3(0.642788, -0.766044, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.766044, -0.642788, 0.000000), vec3(0.766044, -0.642788, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.633022, -0.754407, -0.173648), vec3(0.633022, -0.754407, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.754407, -0.633022, -0.173648), vec3(0.754407, -0.633022, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.604023, -0.719846, -0.342020), vec3(0.604023, -0.719846, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.719846, -0.604023, -0.342020), vec3(0.719846, -0.604023, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.556670, -0.663414, -0.500000), vec3(0.556670, -0.663414, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.663414, -0.556670, -0.500000), vec3(0.663414, -0.556670, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.492404, -0.586824, -0.642788), vec3(0.492404, -0.586824, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.586824, -0.492404, -0.642788), vec3(0.586824, -0.492404, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.413176, -0.492404, -0.766044), vec3(0.413176, -0.492404, -0.766045), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.492404, -0.413176, -0.766044), vec3(0.492404, -0.413176, -0.766045), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.321394, -0.383022, -0.866025), vec3(0.321394, -0.383022, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.383022, -0.321394, -0.866025), vec3(0.383022, -0.321394, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.219846, -0.262003, -0.939693), vec3(0.219846, -0.262003, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.262003, -0.219846, -0.939693), vec3(0.262003, -0.219846, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.111619, -0.133022, -0.984808), vec3(0.111619, -0.133022, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.133022, -0.111619, -0.984808), vec3(0.133022, -0.111619, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.000000, -1.000000), vec3(0.000000, 0.000000, -1.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.133022, -0.111619, -0.984808), vec3(0.133022, -0.111619, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.150384, -0.086824, -0.984808), vec3(0.150384, -0.086824, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.262003, -0.219846, -0.939693), vec3(0.262003, -0.219846, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.296198, -0.171010, -0.939693), vec3(0.296198, -0.171010, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.383022, -0.321394, -0.866025), vec3(0.383022, -0.321394, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.433013, -0.250000, -0.866025), vec3(0.433013, -0.250000, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.492404, -0.413176, -0.766044), vec3(0.492404, -0.413176, -0.766045), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.556670, -0.321394, -0.766044), vec3(0.556670, -0.321394, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.586824, -0.492404, -0.642788), vec3(0.586824, -0.492404, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.663414, -0.383022, -0.642788), vec3(0.663414, -0.383022, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.663414, -0.556670, -0.500000), vec3(0.663414, -0.556670, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.750000, -0.433013, -0.500000), vec3(0.750000, -0.433013, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.719846, -0.604023, -0.342020), vec3(0.719846, -0.604023, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.813798, -0.469846, -0.342020), vec3(0.813798, -0.469846, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.754407, -0.633022, -0.173648), vec3(0.754407, -0.633022, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.852869, -0.492404, -0.173648), vec3(0.852869, -0.492404, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.766044, -0.642788, 0.000000), vec3(0.766044, -0.642788, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.866025, -0.500000, 0.000000), vec3(0.866025, -0.500000, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.754407, -0.633022, 0.173648), vec3(0.754407, -0.633022, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.852869, -0.492404, 0.173648), vec3(0.852869, -0.492404, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.719846, -0.604023, 0.342020), vec3(0.719846, -0.604023, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.813798, -0.469846, 0.342020), vec3(0.813798, -0.469846, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.663414, -0.556670, 0.500000), vec3(0.663414, -0.556670, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.750000, -0.433013, 0.500000), vec3(0.750000, -0.433013, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.586824, -0.492404, 0.642788), vec3(0.586824, -0.492404, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.663414, -0.383022, 0.642788), vec3(0.663414, -0.383022, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.492404, -0.413176, 0.766044), vec3(0.492404, -0.413176, 0.766045), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.556670, -0.321394, 0.766044), vec3(0.556670, -0.321394, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.383022, -0.321394, 0.866025), vec3(0.383022, -0.321394, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.433013, -0.250000, 0.866025), vec3(0.433013, -0.250000, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.262003, -0.219846, 0.939693), vec3(0.262003, -0.219846, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.296198, -0.171010, 0.939693), vec3(0.296198, -0.171010, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.133022, -0.111619, 0.984808), vec3(0.133022, -0.111619, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.150384, -0.086824, 0.984808), vec3(0.150384, -0.086824, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.000000, 1.000000), vec3(0.000000, 0.000000, 1.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.150384, -0.086824, 0.984808), vec3(0.150384, -0.086824, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.163176, -0.059391, 0.984808), vec3(0.163176, -0.059391, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.296198, -0.171010, 0.939693), vec3(0.296198, -0.171010, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.321394, -0.116978, 0.939693), vec3(0.321394, -0.116978, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.433013, -0.250000, 0.866025), vec3(0.433013, -0.250000, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.469846, -0.171010, 0.866025), vec3(0.469846, -0.171010, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.556670, -0.321394, 0.766044), vec3(0.556670, -0.321394, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.604023, -0.219846, 0.766044), vec3(0.604023, -0.219846, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.663414, -0.383022, 0.642788), vec3(0.663414, -0.383022, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.719846, -0.262003, 0.642788), vec3(0.719846, -0.262003, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.750000, -0.433013, 0.500000), vec3(0.750000, -0.433013, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.813798, -0.296198, 0.500000), vec3(0.813798, -0.296198, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.813798, -0.469846, 0.342020), vec3(0.813798, -0.469846, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.883022, -0.321394, 0.342020), vec3(0.883022, -0.321394, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.852869, -0.492404, 0.173648), vec3(0.852869, -0.492404, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.925417, -0.336824, 0.173648), vec3(0.925417, -0.336824, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.866025, -0.500000, 0.000000), vec3(0.866025, -0.500000, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.939693, -0.342020, 0.000000), vec3(0.939693, -0.342020, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.852869, -0.492404, -0.173648), vec3(0.852869, -0.492404, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.925417, -0.336824, -0.173648), vec3(0.925417, -0.336824, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.813798, -0.469846, -0.342020), vec3(0.813798, -0.469846, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.883022, -0.321394, -0.342020), vec3(0.883022, -0.321394, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.750000, -0.433013, -0.500000), vec3(0.750000, -0.433013, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.813798, -0.296198, -0.500000), vec3(0.813798, -0.296198, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.663414, -0.383022, -0.642788), vec3(0.663414, -0.383022, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.719846, -0.262003, -0.642788), vec3(0.719846, -0.262003, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.556670, -0.321394, -0.766044), vec3(0.556670, -0.321394, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.604023, -0.219846, -0.766044), vec3(0.604023, -0.219846, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.433013, -0.250000, -0.866025), vec3(0.433013, -0.250000, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.469846, -0.171010, -0.866025), vec3(0.469846, -0.171010, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.296198, -0.171010, -0.939693), vec3(0.296198, -0.171010, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.321394, -0.116978, -0.939693), vec3(0.321394, -0.116978, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.150384, -0.086824, -0.984808), vec3(0.150384, -0.086824, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.163176, -0.059391, -0.984808), vec3(0.163176, -0.059391, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.000000, -1.000000), vec3(0.000000, 0.000000, -1.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.163176, -0.059391, -0.984808), vec3(0.163176, -0.059391, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.171010, -0.030154, -0.984808), vec3(0.171010, -0.030154, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.321394, -0.116978, -0.939693), vec3(0.321394, -0.116978, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.336824, -0.059391, -0.939693), vec3(0.336824, -0.059391, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.469846, -0.171010, -0.866025), vec3(0.469846, -0.171010, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.492404, -0.086824, -0.866025), vec3(0.492404, -0.086824, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.604023, -0.219846, -0.766044), vec3(0.604023, -0.219846, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.633022, -0.111619, -0.766044), vec3(0.633022, -0.111619, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.719846, -0.262003, -0.642788), vec3(0.719846, -0.262003, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.754407, -0.133022, -0.642788), vec3(0.754407, -0.133022, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.813798, -0.296198, -0.500000), vec3(0.813798, -0.296198, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.852869, -0.150384, -0.500000), vec3(0.852869, -0.150384, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.883022, -0.321394, -0.342020), vec3(0.883022, -0.321394, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.925417, -0.163176, -0.342020), vec3(0.925417, -0.163176, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.925417, -0.336824, -0.173648), vec3(0.925417, -0.336824, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.969846, -0.171010, -0.173648), vec3(0.969846, -0.171010, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.939693, -0.342020, 0.000000), vec3(0.939693, -0.342020, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.984808, -0.173648, 0.000000), vec3(0.984808, -0.173648, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.925417, -0.336824, 0.173648), vec3(0.925417, -0.336824, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.969846, -0.171010, 0.173648), vec3(0.969846, -0.171010, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.883022, -0.321394, 0.342020), vec3(0.883022, -0.321394, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.925417, -0.163176, 0.342020), vec3(0.925417, -0.163176, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.813798, -0.296198, 0.500000), vec3(0.813798, -0.296198, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.852869, -0.150384, 0.500000), vec3(0.852869, -0.150384, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.719846, -0.262003, 0.642788), vec3(0.719846, -0.262003, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.754407, -0.133022, 0.642788), vec3(0.754407, -0.133022, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.604023, -0.219846, 0.766044), vec3(0.604023, -0.219846, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.633022, -0.111619, 0.766044), vec3(0.633022, -0.111619, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.469846, -0.171010, 0.866025), vec3(0.469846, -0.171010, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.492404, -0.086824, 0.866025), vec3(0.492404, -0.086824, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.321394, -0.116978, 0.939693), vec3(0.321394, -0.116978, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.336824, -0.059391, 0.939693), vec3(0.336824, -0.059391, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.163176, -0.059391, 0.984808), vec3(0.163176, -0.059391, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.171010, -0.030154, 0.984808), vec3(0.171010, -0.030154, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.000000, 1.000000), vec3(0.000000, 0.000000, 1.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.171010, -0.030154, 0.984808), vec3(0.171010, -0.030154, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.173648, -0.000000, 0.984808), vec3(0.173648, -0.000000, 0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.336824, -0.059391, 0.939693), vec3(0.336824, -0.059391, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.342020, -0.000000, 0.939693), vec3(0.342020, -0.000000, 0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.492404, -0.086824, 0.866025), vec3(0.492404, -0.086824, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.500000, -0.000000, 0.866025), vec3(0.500000, -0.000000, 0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.633022, -0.111619, 0.766044), vec3(0.633022, -0.111619, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.642788, -0.000000, 0.766044), vec3(0.642788, -0.000000, 0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.754407, -0.133022, 0.642788), vec3(0.754407, -0.133022, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.766044, -0.000000, 0.642788), vec3(0.766044, -0.000000, 0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.852869, -0.150384, 0.500000), vec3(0.852869, -0.150384, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.866025, -0.000000, 0.500000), vec3(0.866025, -0.000000, 0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.925417, -0.163176, 0.342020), vec3(0.925417, -0.163176, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.939693, -0.000000, 0.342020), vec3(0.939693, -0.000000, 0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.969846, -0.171010, 0.173648), vec3(0.969846, -0.171010, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.984808, -0.000000, 0.173648), vec3(0.984808, -0.000000, 0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.984808, -0.173648, 0.000000), vec3(0.984808, -0.173648, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(1.000000, -0.000000, 0.000000), vec3(1.000000, -0.000000, 0.000000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.969846, -0.171010, -0.173648), vec3(0.969846, -0.171010, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.984808, -0.000000, -0.173648), vec3(0.984808, -0.000000, -0.173648), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.925417, -0.163176, -0.342020), vec3(0.925417, -0.163176, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.939693, -0.000000, -0.342020), vec3(0.939693, -0.000000, -0.342020), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.852869, -0.150384, -0.500000), vec3(0.852869, -0.150384, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.866025, -0.000000, -0.500000), vec3(0.866025, -0.000000, -0.500000), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.754407, -0.133022, -0.642788), vec3(0.754407, -0.133022, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.766044, -0.000000, -0.642788), vec3(0.766044, -0.000000, -0.642788), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.633022, -0.111619, -0.766044), vec3(0.633022, -0.111619, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.642788, -0.000000, -0.766044), vec3(0.642788, -0.000000, -0.766044), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.492404, -0.086824, -0.866025), vec3(0.492404, -0.086824, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.500000, -0.000000, -0.866025), vec3(0.500000, -0.000000, -0.866025), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.336824, -0.059391, -0.939693), vec3(0.336824, -0.059391, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.342020, -0.000000, -0.939693), vec3(0.342020, -0.000000, -0.939693), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.171010, -0.030154, -0.984808), vec3(0.171010, -0.030154, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.173648, -0.000000, -0.984808), vec3(0.173648, -0.000000, -0.984808), vec3(1.0f, 0.05f, 0.05f) },
        { vec3(0.000000, 0.000000, -1.000000), vec3(0.000000, 0.000000, -1.000000), vec3(1.0f, 0.05f, 0.05f) },
    };

    GLuint vertexArrayObject;

    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);

    GLuint vertexBufferObject;
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBuffer), vertexBuffer, GL_STATIC_DRAW);


    // 1st attribute buffer : vertex Positions
    glVertexAttribPointer(0,              // attribute. No particular reason for 0, but must match the layout in the shader.
        3,              // size
        GL_FLOAT,       // type
        GL_FALSE,       // normalized?
        sizeof(Vertex), // stride
        (void*)0        // array buffer offset
    );
    glEnableVertexAttribArray(0);

    // 2nd attribute buffer : vertex normal
    glVertexAttribPointer(1,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        (void*)sizeof(vec3)    // Normal is Offseted by vec3 (see class Vertex)
    );
    glEnableVertexAttribArray(1);


    // 3rd attribute buffer : vertex color
    glVertexAttribPointer(2,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        (void*)(2 * sizeof(vec3)) // Color is Offseted by 2 vec3 (see class Vertex)
    );
    glEnableVertexAttribArray(2);

    return vertexArrayObject;
}

bool initContext() {     // Initialize GLFW and OpenGL version
    glfwInit();

#if defined(PLATFORM_OSX)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
    // On windows, we set OpenGL version to 2.1, to support more hardware
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#endif

    // Create Window and rendering context using GLFW, resolution is 800x600
    window = glfwCreateWindow(1024, 768, "COMP371 Winter 2020 Assignment 1", NULL, NULL);
    if (window == NULL)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);

    // @TODO 3 - Disable mouse cursor
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to create GLEW" << std::endl;
        glfwTerminate();
        return false;
    }
    return true;
}
