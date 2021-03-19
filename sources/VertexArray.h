//
// Created by Marko on 12.03.2021.
//

#ifndef CUSTOM_MAP_VERTEXARRAY_H
#define CUSTOM_MAP_VERTEXARRAY_H

#include "utils/pch.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

/*Reresents standard Vertex Array Object (VAO)
 * to store VBOs with given layouts for them*/
class VertexBufferLayout;
class VertexArray {
public:
    VertexArray();
    ~VertexArray();

    void bind() const;
    void unbind() const;
    void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
private:
    unsigned int m_rendererID;
};

#endif //CUSTOM_MAP_VERTEXARRAY_H
