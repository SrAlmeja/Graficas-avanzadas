
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