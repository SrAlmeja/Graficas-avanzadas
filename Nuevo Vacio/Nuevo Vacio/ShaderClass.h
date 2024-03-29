#pragma once
#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

std::string get_file_contents(const char* filename);

class Shader
{
public:
    GLuint ID;
    // Constructor que crea el Shader Program para 2 shaders diferentes
    Shader(const char* vertexFile, const char* fragmentFile);

    void Activate();
    void Delete();
};
#endif