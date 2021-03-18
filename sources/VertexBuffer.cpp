//
// Created by Marko on 11.03.2021.
//

#include "VertexBuffer.h"
#include "utils/pch.h"

VertexBuffer::VertexBuffer(const void *data, unsigned int size)
{
    setData(data,size);
}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_redererID));
}

void VertexBuffer::bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_redererID));
}

void VertexBuffer::unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

VertexBuffer::VertexBuffer():
    m_redererID(0)
{
    GLCall(glGenBuffers(1, &m_redererID));
}

void VertexBuffer::setData(const void *data, unsigned int size)
{
    GLCall(glGenBuffers(1, &m_redererID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_redererID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}
