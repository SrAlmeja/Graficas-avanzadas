#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>



int LerningMain()
{
    //Esto inicializa GLFW
    glfwInit();

    //Le dice a GLFW que version de OpenGl estamos usando
    //Se utilizó la version de Opengl 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Le dice al GLFW que estamos usando el CoreProfile
    //Se refiere a que utilizamos las funciones modernas de este.
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLfloat vertices[] =
    {
        -0.5f, -0.5f * float(sqrt(3)) / 3,0.0f,
        0.5f, -0.5f * float(sqrt(3)) / 3,0.0f,
        0.0f, 0.5f * float(sqrt(3)) *2 / 3,0.0f
    };


    //Este es un apuntador
    //Crea un GLFWwindow de 800 x 800 pixeles (lo podemos nombrar como queramos en este caso "Window")
    GLFWwindow* window = glfwCreateWindow(800, 800, "Window", NULL, NULL);

    //Crear un contexto de tipo window para openGL
    glfwMakeContextCurrent(window);

    //Carga glad para que configure OpenGL
    gladLoadGL();

    //Especifica la vista de openGL en la ventana
    //Las cordenadas que se muestran indican que la pantalla va a ir de "x: 0" y "y: 0" a "x: 800" a "y: 800" 
    glViewport(0, 0, 800, 800);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, Null);



    //Especifica el color del fondo
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    //Limpia el "back Buffer" y le asigna el nuevo color
    glClear(GL_COLOR_BUFFER_BIT);
    // Intercambia el "Back Buffer" por el "front Buffer"
    glfwSwapBuffers(window);

    //Mantener la viva la ventana hasta que se cierre
    //Asignacion de buffer
    while (!glfwWindowShouldClose(window))
    {

        glfwPollEvents();
    }


    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}