#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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

int main(void)
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
	
	if(!gladLoadGL()){
		std::cout << "Can't load GLAD" << std::endl;
		return -1;
	}

    glfwSetWindowSizeCallback(window, glfwWindowResizeCallback);
    glfwSetKeyCallback(window, glfwKeyBoardCallBack);
	
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	
	glClearColor(0,1,0,1);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}