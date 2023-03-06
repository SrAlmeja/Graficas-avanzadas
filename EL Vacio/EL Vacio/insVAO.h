#ifndef INSVAO_CLASS_H
#define INSVAO_CLASS_H

#include<glad/glad.h>
#include"insVBO.h"

class InsVAO
{
public:
    GLuint ID;

    // Constructor
    InsVAO();

    // Enlaza VBO a VAO usando un layout especifico
    void LinkinsVBO(InsVBO& InsVBO, GLuint layout);

    void Bind();
    void Unbind();
    void Delete();
};
#endif
