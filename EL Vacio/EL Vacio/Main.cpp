#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"ShaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

//Se Define la version, se asignan las posiciones del atributo


int main()
{
    glfwInit();
    
    //Se dice la versión a usar de Open GL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    //Apuntador de tipo window para tener referencia de la ventana (Referencia)
    GLFWwindow* window = glfwCreateWindow(1000, 1000, "Window", NULL, NULL);


    double seconds = 1.0f;
    float scale;
    float scalePercent = 0.2f;
    float scaleGoal = 1.0f;

        GLfloat vertices[] =
        {
            0.5f, -0.5f * float(sqrt(3)) / 3 , 0.0f,        1.0f, 0.0f, 0.0f, //esquina inferior izquierda
            -0.5f, -0.5f * float(sqrt(3)) / 3 , 0.0f,       1.0f, 0.0f, 0.0f, //esquina inferior derecha
            0.0f, 0.5f * float(sqrt(3)) * 2 / 3 , 0.0f,     1.0f, 0.0f, 0.0f, //punta de la trifuerza
            0.5f / 2, 0.5f * float(sqrt(3)) / 6 , 0.0f,     1.0f, 0.0f, 0.0f, //esquina superior izquierda
            -0.5f / 2, 0.5f * float(sqrt(3)) / 6 , 0.0f,    1.0f, 0.0f, 0.0f, //esquina superior derecha
            0.0f, -0.5f * float(sqrt(3)) / 3 , 0.0f,        1.0f, 0.0f, 0.0f, //Base
        };

        GLuint indices[] =
        {
        0, 3, 5, // Triangulo inferior izq
        3, 2, 4, // Triangulo inferior der
        5, 4, 1, // Triangulo superior
        };



        //Crear un contexto para openGL
        glfwMakeContextCurrent(window);

        //Agregando el color, Se definen los colores de la pantalla
        gladLoadGL();  //Carga las funciones en la libreria de glad

        //Se Crean los Shaders
        Shader shaderProgram("default.vert", "default.frag");
        Shader InsShaderProgram("insDefault.vert", "insDefault.frag");

        VAO VAO1;
        VAO1.Bind();

        VBO VBO1(vertices, sizeof(vertices));
        EBO EBO1(indices, sizeof(indices));

        VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
        VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

        VAO1.Unbind();
        VBO1.Unbind();
        EBO1.Unbind();

        GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");


    while (!glfwWindowShouldClose(window))
    {
        GLfloat time = glfwGetTime() * seconds;

        //Asignacion de buffer
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shaderProgram.Activate();

        glUniform1f(uniID, 0.5f);
        VAO1.Bind();

        glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);

        glfwPollEvents();

    }
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();

    shaderProgram.Delete();

    
    glViewport(0, 0, 1000, 1000);
    glfwSwapBuffers(window);

    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
}