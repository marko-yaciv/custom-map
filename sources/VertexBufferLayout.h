//
// Created by Marko on 12.03.2021.
//

#ifndef CUSTOM_MAP_VERTEXBUFFERLAYOUT_H
#define CUSTOM_MAP_VERTEXBUFFERLAYOUT__H

#include "utils/pch.h"
#include <vector>

/*Element of layout. Has it's type.
 * count (depends on .. of VBO (2D, 3D or 4D))
 * if this element should be normalised*/
struct VertexBufferElement{
    unsigned int type;
    unsigned int count;
    unsigned char normalised;

    static unsigned int getSizeOfType(unsigned int type){
        switch (type){
            case GL_FLOAT:
                return 4;
            case GL_UNSIGNED_INT:
                return 4;
            case GL_UNSIGNED_BYTE:
                return 1;
            default:
                return 0;
        }
    }
};

/*Representss VBO layout that keeps vector of
 * Elements and allows to add new element to layout*/
class VertexBufferLayout{
public:
    VertexBufferLayout()
        :m_stride(0){};
    void push(unsigned int type, unsigned int count);
    inline const std::vector<VertexBufferElement> getElements() const {return m_elements;}
    inline unsigned int getStride() const {return m_stride;}
private:
    std::vector<VertexBufferElement> m_elements;
    /*stride in bytes between elements*/
    unsigned int m_stride;
};

#endif //CUSTOM_MAP_VERTEXBUFFERLAYOUT_H
