#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Renderer/ShaderProgram.h"
#include "Resources/ResourceManager.h"
#include "Renderer/Texture2D.h"

GLfloat point[] = {
    0.0f,0.5f,0.0f,
    0.5f,-0.5f,0.0f,
    -0.5f,-0.5f,0.0f
};

GLfloat colors[] = {
    1.0f,0.0f,0.0f,
    0.0f,1.0f,0.0f,
    0.0f,0.0f,1.0f
};

GLfloat textureCoords[] = {
        0.5f,1.0f,
        1.0f,0.0f,
        0.0f,0.0f
};

int windowWidth = 640;
int windowHeight = 480;

void glfwWindowResizeCallback(GLFWwindow* window, int width, int height) {
    windowWidth = width;
    windowHeight = height;
    glViewport(0,0,windowWidth,windowHeight);
}

void glfwKeyBoardCallBack(GLFWwindow* window,int key,int scanmode,int action,int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window,GL_TRUE);
    }
}

int main(int argv, char** argc)
{
    {
        if (!glfwInit()) {
            std::cout << "Error init GLFW" << std::endl;
            return -1;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Battle City", nullptr, nullptr);
        if (!window)
        {
            glfwTerminate();
            std::cout << "Error init window!" << std::endl;
            return -1;
        }

        glfwMakeContextCurrent(window);

        if (!gladLoadGL()) {
            std::cout << "Can't load GLAD" << std::endl;
            return -1;
        }

        glfwSetWindowSizeCallback(window, glfwWindowResizeCallback);
        glfwSetKeyCallback(window, glfwKeyBoardCallBack);

        std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
        std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

        glClearColor(1, 1, 0, 1);


        ResourceManager resourceManager(argc[0]);

        auto pDefaultShaderProgram = resourceManager.LoadShaders("DefShaders", "res/shaders/vertex.vert", "res/shaders/fragment.frag");

        if (!pDefaultShaderProgram) {
            system("pause");
            return -1;
        }

        auto texture = resourceManager.LoadTexture("def","res/textures/map_16x16.png");

        GLuint pointsVbo = 0;
        glGenBuffers(1, &pointsVbo);
        glBindBuffer(GL_ARRAY_BUFFER, pointsVbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);

        GLuint colorsVbo = 0;
        glGenBuffers(1, &colorsVbo);
        glBindBuffer(GL_ARRAY_BUFFER, colorsVbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

        GLuint texture_vbo = 0;
        glGenBuffers(1, &texture_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, texture_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoords), textureCoords, GL_STATIC_DRAW);

        GLuint vao = 0;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, pointsVbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colorsVbo);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, texture_vbo);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

        pDefaultShaderProgram->use();
        pDefaultShaderProgram->setInt("def",0);

        while (!glfwWindowShouldClose(window))
        {
            glClear(GL_COLOR_BUFFER_BIT);

            pDefaultShaderProgram->use();
            glBindVertexArray(vao);
            texture->bind();
            glDrawArrays(GL_TRIANGLES, 0, 3);

            glfwSwapBuffers(window);

            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}