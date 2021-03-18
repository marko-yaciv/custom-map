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

void Renderer::draw(const VertexArray &vao, const IndexBuffer &ib,
                    Shader &shader) const
{
    shader.bind();
    vao.bind();
    ib.bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::clear()
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}
