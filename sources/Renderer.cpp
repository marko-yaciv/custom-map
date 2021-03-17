//
// Created by Marko on 12.03.2021.
//
#include "Renderer.h"
#include <iostream>

void GLClearError()
{
    while(glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* funcName, const char* file, int line)
{
    while(GLenum error = glGetError())
    {
        std::cout << "[Error] (" << error << "): " <<
                  funcName << " " << file << ": " << line << std::endl;
        return false;
    }
    return true;
}