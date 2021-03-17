//
// Created by Marko on 11.03.2021.
//

#ifndef CUSTOM_MAP_IndexBuffer_H
#define CUSTOM_MAP_IndexBuffer_H

class IndexBuffer{
public:
    IndexBuffer(const unsigned int* data, unsigned int count);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;

    inline unsigned int getCount() const {return m_count;}
private:
    unsigned int m_redererID;
    unsigned int m_count;
};


#endif //CUSTOM_MAP_IndexBuffer_H
