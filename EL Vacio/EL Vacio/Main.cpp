#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"ShaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Texture.h"

#include<stb/stb_image.h>


int main()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow* window = glfwCreateWindow(1000, 1000, "Window", NULL, NULL);

    glfwSetTime(0);

    GLfloat squareVertices[] =
    {//     Cordenadas      /       Color       /       TextCord    
     -0.4f, 0.01f, 0.0f,       1.0f, 0.0f, 0.0f,        0.0f, 0.0f,     // Esquina inferior izquierda
     -0.4f, 0.8f, 0.0f,        0.0f, 1.0f, 0.0f,        0.0f, 1.0f,     // Esquina superior Izquierda
     0.4f, 0.8f, 0.0f,         0.0f, 0.0f, 1.0f,        1.0f, 1.0f,     // Esquina Superior Derecha
     0.4f, 0.0f, 0.0f,        1.0f, 1.0f, 1.0f,        1.0f, 0.0f       // Esquina Superior Derecha
    };

    GLuint squareIndices[] =
    {
     0, 2, 1,
     0, 3, 2
    };

    glfwMakeContextCurrent(window);
    gladLoadGL();

    Texture luffy("Mario.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);

    glfwMakeContextCurrent(window);

    gladLoadGL();

 
    // Shader shaderProgram("D1.vert", "D1.frag");
    Shader InsideShaderProgram("CC.vert", "CC.frag");


    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(squareVertices, sizeof(squareVertices));
    EBO EBO1(squareIndices, sizeof(squareIndices));

    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    // GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");
    GLuint insideID = glGetUniformLocation(InsideShaderProgram.ID, "scale");

    GLuint tex0uni = glGetUniformLocation(InsideShaderProgram.ID, "tex0");

    GLuint randomColor = glGetUniformLocation(InsideShaderProgram.ID, "randomColor");

    InsideShaderProgram.Activate();

    luffy.texUnit(InsideShaderProgram, "randomColor", 0);

    glUniform1i(tex0uni, 0);


    while (!glfwWindowShouldClose(window))
    {
        float tValue = glfwGetTime();
        float red = 1;
        float green = 1;
        float blue = 1;

        glUniform1i(tex0uni, 0);
        glUniform3f(randomColor, red, green, blue);


        glClearColor(0.01f, 0.05f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        InsideShaderProgram.Activate();

        luffy.Bind();
       
        VAO1.Bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        glfwSwapBuffers(window);

        glfwPollEvents();

    }
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();

    // shaderProgram.Delete();
    InsideShaderProgram.Delete();


    glViewport(0, 0, 1024, 1024);
    glfwSwapBuffers(window);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}