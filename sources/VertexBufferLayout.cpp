//
// Created by Marko on 13.03.2021.
//
#include "VertexBufferLayout.h"

void VertexBufferLayout::push(unsigned int type, unsigned int count)
{
    m_elements.push_back({ type, count, GL_FALSE });
    m_stride += count * VertexBufferElement::getSizeOfType(type);
}
