#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"ShaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"


int main()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLfloat vertices[] =
    {
         -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,       // Esquina inferior izq
         0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,        // Esquina inferior derecha
         0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,   // Esquina superior
         -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,      // Interior izquierda
         0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,    // Interior derecha
         0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f        // Interior abajo
    };

    GLfloat insideVertex[] =
    {
         -0.45f, -0.45f * float(sqrt(3)) / 3, 0.0f,       // Esquina inferior izq
         -0.5f / 2, 0.5f * float(sqrt(1.5f)) / 6, 0.0f,      // Interior izquierda
         -0.05f, -0.45f * float(sqrt(3)) / 3, 0.0f,        // Interior abajo


         0.05f, -0.45f * float(sqrt(3)) / 3, 0.0f,        // Interior abajo
         0.45f, -0.45f * float(sqrt(3)) / 3, 0.0f,        // Esquina inferior derecha
         0.5f / 2, 0.5f * float(sqrt(1.5f)) / 6, 0.0f,   // Esquina superior

         -0.4f / 2, 0.6f * float(sqrt(3)) / 6, 0.0f,      // Interior izquierda
         0.0f, 0.45f * float(sqrt(3)) * 2 / 3, 0.0f,   // Esquina superior
         0.4f / 2, 0.6f * float(sqrt(3)) / 6, 0.0f,    // Interior derecha
    };

    GLuint indices[] =
    {
     0, 3, 5, // Triangulo inferior izq
     3, 2, 4, // Triangulo inferior der
     5, 4, 1 //  Triangulo superior
    };


    GLuint insideIndex[] =
    {
    0, 1, 2, // Triangulo inferior izq
    3, 4, 5, // Triangulo inferior der
    6, 7, 8 // Triangulo superior
    };

    //Apuntador de tipo window para tener referencia de la ventana (Referencia)
    GLFWwindow* window = glfwCreateWindow(800, 800, "Window", NULL, NULL);

    //Crear un contexto para openGL
    glfwMakeContextCurrent(window);

    //Agregando el color
    gladLoadGL();

    //Se crean Shaders
    Shader shaderProgram("default.vert", "default.frag");

    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    VAO1.LinkVBO(VBO1, 0);

    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    glViewport(0, 0, 800, 800);
    glfwSwapBuffers(window);

    //Mantener la viva la ventana hasta que se cierre
    //Asignacion de buffer
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(1, 0.5f, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.Activate();
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    //Limpieza de Buffer
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();

    shaderProgram.Delete();


    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}