//
// Created by Marko on 12.03.2021.
//

#include "VertexArray.h"


VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1, &m_rendererID));
}

VertexArray::~VertexArray()
{
    GLCall(glDeleteVertexArrays(1, &m_rendererID));
}

void VertexArray::bind() const
{
    GLCall(glBindVertexArray(m_rendererID));
}
void VertexArray::unbind() const
{
    GLCall(glBindVertexArray(0));
}
void VertexArray::addBuffer(const VertexBuffer &vb,
                            const VertexBufferLayout &layout) {
    bind();
    vb.bind();
    unsigned int offset = 0;
    const auto& elements = layout.getElements();
    /*Tell array pointer how to find
     * each characteristic (element) of layout in VBO*/
    for (int i = 0; i < elements.size(); ++i)
    {
        const auto& element = elements[i];
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, element.count, element.type,
                element.normalised, layout.getStride(), (const void*)offset));

        offset += element.count * VertexBufferElement::getSizeOfType(element.type);
    }
}




