
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

int main()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    
    //Apuntador de tipo window para tener referencia de la ventana (Referencia)
    GLFWwindow* window = glfwCreateWindow(800, 800, "Window", NULL, NULL);

    //Crear un contexto para openGL
    glfwMakeContextCurrent(window);

    //Agregando el color
    gladLoadGL();
    //Cordenada inicio x,y -> final X,Y
    glViewport(0, 0, 800, 800);
    glClearColor(0.3f,0.6f,0.9f,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);


    //Mantener la viva la ventana hasta que se cierre
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
    }
    
    //DESTRUIR VENTANA
    glfwDestroyWindow(window);

    glfwTerminate();
    return 0;
}