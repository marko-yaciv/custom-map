//
// Created by Marko on 11.03.2021.
//

#ifndef CUSTOM_MAP_VERTEXBUFFER_H
#define CUSTOM_MAP_VERTEXBUFFER_H

/*Represents common Vertex Buffer Object(VBO)
 * that stores vertex attributes*/
class VertexBuffer{
public:
    VertexBuffer();
    /*calls setData*/
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    /*<data> attribute should be an array of attribs,
     * and <size> should be a size of that array IN BYTES*/
    void setData(const void* data, unsigned int size);

    void bind() const;
    void unbind() const;
private:
    unsigned int m_redererID;
};

#endif //CUSTOM_MAP_VERTEXBUFFER_H
