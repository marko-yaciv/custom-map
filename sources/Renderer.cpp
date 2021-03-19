//
// Created by Marko on 12.03.2021.
//
#include "Renderer.h"
#include <iostream>

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
