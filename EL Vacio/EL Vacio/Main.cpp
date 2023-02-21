#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

//Vertex shader de un triangulo
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos; \n"
"void main()\n"
"{\n"
"    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";



int main()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    //Fragment Shader
    const char* fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "    FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
        "}\n\0";

    GLfloat vertices[] =
    {
        -0.5f, -0.5f / float(sqrt(3)) / 3,0.0f,
        0.5f, -0.5f * float(sqrt(3)) / 3,0.0f,
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3,0.0f
    };

    
 
    
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

    //Referencia del vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glad_glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);


    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    //Shader Program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    //Eliminar los shader anteriores
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    GLuint VAO, VBO;

    //Generamos identificadores únicos
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    //Vinculamos el VAO/VBO con el contexto OpenGL
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //Configuta el Buffer con el tamaño el tipo de uso del buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //Configura los atributos de los vértices en el objeto VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    //Mantener la viva la ventana hasta que se cierre
    //Asignacion de buffer
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    //Limpieza de Buffer
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    
    //DESTRUIR VENTANA
    glfwDestroyWindow(window);

    glfwTerminate();
    return 0;
}