#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource = R"s(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 aColor;

    out vec4 outColor;

    void main(){
        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);
        outColor = vec4(aColor, 1.0f);
    }
)s";

const char* fragmentShaderSource = R"s(
    #version 330 core
    out vec4 FragColor;

    in vec4 outColor;
    void main(){
        FragColor = outColor;
    }
)s";

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main() {
    glfwInit();

    // Kreiramo prozor
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Shaders", nullptr, nullptr);
    if(window == nullptr){
        std::cout << "Failed to create GLFW window!\n";
        glfwTerminate();
        return -1;
    }

    // Postavi kontekst za renderovanje
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetKeyCallback(window, keyCallback);

    // Ucitamo OpenGL funkcije
    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD!\n" << std::endl;
        glfwTerminate();
        return -1;
    }

    int vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderId, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShaderId);

    int success;
    char infoLog[512] = {0};
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShaderId, 512, NULL, infolog);
        std::cout << "ERROR::VERTEX::SHADER: " << infoLog << '\n';
    }

    int fragmentSHaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentSHaderId, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentSHaderId);
    glGetShaderiv(fragmentSHaderId, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentSHaderId, 512, NULL, infoLog);
        std::cout << "ERROOR::FRAGMENT::SHADER: " << infoLog << '\n';
    }

    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShaderId);
    glAttachShader(shaderProgram, fragmentSHaderId);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::SHADER: " << infoLog << '\n';
    }

    float vertices[] = {
            //     x          y         z         R         G       B
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, //left
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, //right
            0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f // top
    };

    //VertexBufferObject
    unsigned VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (0));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClearColor(gRed, gGreen, gBlue, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        update(window);

        glUseProgram(shaderProgram);
#if 0
        // nadjemo njen identifikator
        int varId = glGetUniformLocation(shaderProgram, "outColor");
        // onda preko tog id-ja da postavimo vrednost uniform promenljive
        // glatka, periodicna, oscilijuca funkcija
        // sin R : [-1, 1] + 1 --> [0, 2] / 2

        float timeValue = glfwGetTime();
        float blueValue = (sin(timeValue*4.0f)*1.0f)/2.0f;

        glUniform4f(varId, 0.5f, 0.2f, blueValue, 1.0f);
#endif
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

    }

    glfwTerminate();

    return 0;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height){
    std::cout << width << ' ' << height << '\n';
}
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if(key == GLFW_KEY_R){
        if(action == GLFW_PRESS) {
            glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
            std::cout << "Rdown\n";
        }
        else if(action == GLFW_RELEASE){
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            std::cout << "Rup\n";
        }
    }
}
