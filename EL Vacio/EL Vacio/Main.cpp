#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"ShaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Texture.h"

#include<stb/stb_image.h>

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
    /*float scale, scale2;
    float sizePercent = 0.2f;
    float NormalScale = 1.0f;*/

    //Variables para textura
    int widthTx, heightTx, numCol; //Guardar colores y medidas


    glfwSetTime(0);

    GLfloat squareVertices[] =
    {
     -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
     -0.5f, 0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f
    };

    GLuint squareIndices[] =
    {
     0, 2, 1,
     0, 3, 2
    };

    //Se Convierte el objeto en textura
    //glGenTextures(1, &texture);

    glfwMakeContextCurrent(window);
    gladLoadGL();

    //Se crea la textura
    Texture luffy("chopper.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);



    //Crear un contexto para openGL
    glfwMakeContextCurrent(window);
    //Agregando el color, Se definen los colores de la pantalla
    gladLoadGL();  //Carga las funciones en la libreria de glad

    //Se Crean los Shaders
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


    while (!glfwWindowShouldClose(window))
    {
        /*GLfloat time = glfwGetTime() * (18.9f * seconds);
        GLfloat time2 = glfwGetTime() * (20.0f*seconds);*/
        GLfloat time = glfwGetTime() * seconds;

        //Asignacion de buffer
        glClearColor(0.01f, 0.05f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //scale = sin(time) * sizePercent + NormalScale;

        InsideShaderProgram.Activate();

        luffy.Bind();
        glUniform1i(tex0uni, 0);
        glUniform4f(randomColor, 1.0f, 0.0f, 0.0f, 1.0f);
        VAO1.Bind();

        //scale2 = sin(time2) * sizePercent + NormalScale;

        // shaderProgram.Activate();
        // glUniform1f(uniID, scale2);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //std::cout << scale << std::endl;

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