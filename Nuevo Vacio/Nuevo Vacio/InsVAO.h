#ifndef INSVAO_CLASS_H
#define INSVAO_CLASS_H

#include<glad/glad.h>
#include"VBO.h"

class ImsVAO
{
public:
    GLuint ID;

    // Constructor
    VAOIns();

    // Enlaza VBO a VAO usando un layout especifico
    void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr
        stride, void* offset);

    void Bind();
    void Unbind();
    void Delete();
};
#endif
