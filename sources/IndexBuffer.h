//
// Created by Marko on 11.03.2021.
//

#ifndef CUSTOM_MAP_IndexBuffer_H
#define CUSTOM_MAP_IndexBuffer_H

/*Represents Index buffer used in openGL to
 * specify order pf painting vertices*/
class IndexBuffer{
public:
    /*<data> argunment is an array
     * of unsigned integers(order num)*/
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
