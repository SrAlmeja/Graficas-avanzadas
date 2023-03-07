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
    float scale, scale2;
    float sizePercent = 0.2f;
    float NormalScale = 1.0f;

    glfwSetTime(0);

    GLfloat vertices[] =
    {
        0.5f, -0.5f * float(sqrt(3)) / 3 , 0.0f,        0.5f, 0.0f, 0.5f, //esquina inferior izquierda
        -0.5f, -0.5f * float(sqrt(3)) / 3 , 0.0f,       0.5f, 0.0f, 0.5f, //esquina inferior derecha
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3 , 0.0f,     1.0f, 0.0f, 0.0f, //punta de la trifuerza
        0.5f / 2, 0.5f * float(sqrt(3)) / 6 , 0.0f,     0.0f, 0.0f, 0.0f, //esquina superior izquierda
        -0.5f / 2, 0.5f * float(sqrt(3)) / 6 , 0.0f,    0.0f, 0.0f, 0.0f, //esquina superior derecha
        0.0f, -0.5f * float(sqrt(3)) / 3 , 0.0f,        1.0f, 0.0f, 1.0f, //Base
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
    Shader shaderProgram("D1.vert", "D1.frag");
    Shader InsideShaderProgram("D2.vert", "D2.frag");

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
    GLuint insideID = glGetUniformLocation(InsideShaderProgram.ID, "scale");


    while (!glfwWindowShouldClose(window))
    {
        GLfloat time = glfwGetTime() * (18.9f*seconds);
        GLfloat time2 = glfwGetTime() * (20.0f*seconds);

        //Asignacion de buffer
        glClearColor(0.01f, 0.05f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        scale = sin(time) * sizePercent + NormalScale;

        InsideShaderProgram.Activate();
        glUniform1f(insideID, (scale/3.5f));
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        scale2 = sin(time2) * sizePercent + NormalScale;
        
        shaderProgram.Activate();
        glUniform1f(uniID, scale2);
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        std::cout << scale << std::endl;

        glfwSwapBuffers(window);

        glfwPollEvents();

    }
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();

    shaderProgram.Delete();
    InsideShaderProgram.Delete();


    glViewport(0, 0, 1000, 1000);
    glfwSwapBuffers(window);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}