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

    float tValue = glfwGetTime();
    float red = 1.0f;
    float green = 1.0f;
    float blue = 1.0f;


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow* window = glfwCreateWindow(1000, 1000, "Window", NULL, NULL);

    glfwSetTime(0);

    GLfloat squareVertices[] =
    {//     Cordenadas      /       Color       /       TextCord    
     -0.4f, -0.60f, 0.0f,     1.0f, 0.0f, 0.0f,    0.0f, 0.0f, // Lower left corner
    -0.4f,  0.00f, 0.0f,     0.0f, 1.0f, 0.0f,    0.0f, 1.0f, // Upper left corner
     0.4f,  0.00f, 0.0f,     0.0f, 0.0f, 1.0f,    1.0f, 1.0f, // Upper right corner
     0.4f, -0.60f, 0.0f,     1.0f, 1.0f, 1.0f,    1.0f, 0.0f  // Lower right corner
    };

    GLfloat squareVerticesMirror[] =
    {//     Cordenadas      /       Color       /       TextCord    
    -0.6f, 0.00f, 0.0f,     1.0f, 0.0f, 0.0f,    0.0f, 0.0f, // Lower left corner
    -0.35f, 0.60f, 0.0f,    0.0f, 1.0f, 0.0f,    0.0f, 1.0f, // Upper left corner
     0.35f, 0.60f, 0.0f,    0.0f, 0.0f, 1.0f,    1.0f, 1.0f, // Upper right corner
     0.6f, 0.00f, 0.0f,     1.0f, 1.0f, 1.0f,    1.0f, 0.0f  // Lower right corner
    };

    GLuint squareIndices[] =
    {
     0, 2, 1,
     0, 3, 2
    };

    glfwMakeContextCurrent(window);
    gladLoadGL();

    Texture Litch("litch.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);

    glfwMakeContextCurrent(window);

    gladLoadGL();


    // Shader shaderProgram("D1.vert", "D1.frag");
    Shader InsideShaderProgram("RE.vert", "RE.frag");

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

    GLuint VAO2, VBO2;
    
    glGenVertexArrays(1, &VAO2);
    glGenBuffers(1, &VBO2);

    glBindVertexArray(VAO2);

    glBindBuffer(GL_ARRAY_BUFFER, VBO2);

    VBO VBO2(squareVerticesMirror, sizeof(squareVerticesMirror));
    EBO EBO2(squareIndices, sizeof(squareIndices));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    VAO2.Unbind();
    VBO2.Unbind();
    EBO2.Unbind();

    // GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");
    GLuint insideID = glGetUniformLocation(InsideShaderProgram.ID, "scale");

    GLuint tex0uni = glGetUniformLocation(InsideShaderProgram.ID, "tex0");

    GLuint texAxis = glGetUniformLocation(InsideShaderProgram.ID, "mirrorAxis");

    InsideShaderProgram.Activate();

    glUniform1i(tex0uni, 0);
    Litch.Bind();

    while (!glfwWindowShouldClose(window))
    {

        glUniform1i(tex0uni, 0);


        glClearColor(0.01f, 0.05f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUniform1f(insideID, 0.05f);

        glUniform1f(texAxis, 0.0f);
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        glUniform1f(texAxis, 1.0f);
        VAO2.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        glfwSwapBuffers(window);

        glfwPollEvents();

    }
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();

    VAO2.Delete();
    VBO2.Delete();
    EBO2.Delete();

    // shaderProgram.Delete();
    InsideShaderProgram.Delete();


    glViewport(0, 0, 1024, 1024);
    glfwSwapBuffers(window);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}