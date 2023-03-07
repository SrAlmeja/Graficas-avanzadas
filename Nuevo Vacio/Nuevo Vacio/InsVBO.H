#ifndef INSVBO_CLASS_H
#define INSVBO_CLASS_H

#include<glad/glad.h>

class InsVBO
{
public:
    GLuint ID;

    // Constructor que genera un Elements Buffer Object y lo enlaza a los indices
    VBO(GLfloat* vertices, GLsizeiptr size);

    void Bind();
    void Unbind();
    void Delete();
};
#endif