#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

//Se Define la version, se asignan las posiciones del atributo

//Vertex shader de un triangulo
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos; \n"
"void main()\n"
"{\n"
"    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";


//Vertex Shader de triangulos interiores
const char* insVertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos; \n"
"void main()\n"
"{\n"
"    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

//Se definen los colores que se asignaran en cada frame de la escena

//Fragment Shader
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(1, 0, 0, 1);\n" // (Rojo, Verde, Azul, Alfa)
"}\n\0";

//Fragment Shader de triangulos interiores
const char* insFragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(0.5f, 0f, 0f, 1);\n"
"}\n\0";


int main()
{
    glfwInit();
    
    //Se dice la versión a usar de Open GL
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

    GLfloat insVertices[] =
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

    GLuint insIndices[] =
    {
    0, 1, 2, // Triangulo inferior izq
    3, 4, 5, // Triangulo inferior der
    6, 7, 8 // Triangulo superior
    };
    
    //Apuntador de tipo window para tener referencia de la ventana (Referencia)
    GLFWwindow* window = glfwCreateWindow(800, 800, "Window", NULL, NULL);

    //Crear un contexto para openGL
    glfwMakeContextCurrent(window);

    //Agregando el color, Se definen los colores de la pantalla
    gladLoadGL();  //Carga las funciones en la libreria de glad
    glViewport(0, 0, 800, 800);   //Define el tamaño de la pantalla de la siguiente manera: Cordenada inicio x,y -> final X,Y
    glClearColor(0.3f,0.6f,0.9f,1);  //Se especifica con que colores borrará el buffer de color
    glClear(GL_COLOR_BUFFER_BIT);  //Borra el buffer de color de la ventana de visualización
    glfwSwapBuffers(window);  //Intercambia los buffers de la ventana de visualizacion mostrando los graficos recien renderizados de OpenGL.

    //Referencia del vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glad_glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    //Shaders de triangulos interiores
    GLuint insVertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(insVertexShader, 1, &insVertexShaderSource, NULL);
    glCompileShader(insVertexShader);

    //Referencia de colores triangulo
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    //Referencia de colores triangulos interiores 
    GLuint insFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(insFragmentShader, 1, &insFragmentShaderSource, NULL);
    glCompileShader(insFragmentShader);

    //Shader Program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    GLuint insShaderProgram = glCreateProgram();
    glAttachShader(insShaderProgram, insVertexShader);
    glAttachShader(insShaderProgram, insFragmentShader);
    glLinkProgram(insShaderProgram);

    //Eliminar los shader anteriores
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(insVertexShader);
    glDeleteShader(insFragmentShader);


    GLuint VAO, VBO, EBO;
    GLuint insVAO, insVBO, insEBO;

    //Generamos identificadores únicos
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glGenVertexArrays(1, &insVAO);
    glGenBuffers(1, &insVBO);
    glGenBuffers(1, &insEBO);

    //Vinculamos el VAO/VBO con el contexto OpenGL
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    

    //Configuta el Buffer con el tamaño el tipo de uso del buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //Configura los atributos de los vértices en el objeto VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    //Triangulos interiores
     //Vinculamos el VAO/VBO con el contexto OpenGL
    glBindVertexArray(insVAO);
    glBindBuffer(GL_ARRAY_BUFFER, insVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(insVertices), insVertices, GL_STATIC_DRAW);


    //Configuta el Buffer con el tamaño el tipo de uso del buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, insEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(insIndices), insIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //Configura los atributos de los vértices en el objeto VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    //Mantener la viva la ventana hasta que se cierre
    //Asignacion de buffer
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        //Interior
        glUseProgram(insShaderProgram);
        glBindVertexArray(insVAO);
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        //Cierre de ventana
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    //Limpieza de Buffer
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &insVAO);
    glDeleteBuffers(1, &insVBO);
    glDeleteBuffers(1, &insEBO);
    glDeleteProgram(shaderProgram);
    glDeleteProgram(insShaderProgram);

    
    //DESTRUIR VENTANA
    glfwDestroyWindow(window);

    glfwTerminate();
}