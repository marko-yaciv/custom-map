//
// Created by Marko on 11.03.2021.
//

#ifndef CUSTOM_MAP_VERTEXBUFFER_H
#define CUSTOM_MAP_VERTEXBUFFER_H

class VertexBuffer{
public:
    VertexBuffer();
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void setData(const void* data, unsigned int size);
    void bind() const;
    void unbind() const;
private:
    unsigned int m_redererID;
};


#endif //CUSTOM_MAP_VERTEXBUFFER_H
