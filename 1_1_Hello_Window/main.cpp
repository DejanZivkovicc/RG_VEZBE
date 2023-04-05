#include <iostream>
#include <cassert>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebufferSizeCallback(GLFWwindow* window, int width, int height){
    std::cout << width << ' ' << height << '\n';
}

int main() {
    // init
    // init glfw
    int glfwInitStatus = glfwInit();
    assert(glfwInitStatus == GLFW_TRUE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Kreiramo prozor
    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello Window!", nullptr, nullptr);
    if(window == nullptr){
        std::cout << "Failed to create a window!\n";
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    // Ucitavamo sve OpenGL funkcije
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD!\n";
        return -1;
    }

    // Petlja renderovanja
    while(!glfwWindowShouldClose(window)){
        // poll_events
        glfwPollEvents();
        //update
        //render
       // glfwSwapBuffers(window);
    }

    // deinit glfw
    glfwTerminate();

    return 0;
}
