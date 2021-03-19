//
// Created by Marko on 15.03.2021.
//

#ifndef CUSTOM_MAP_TEXTURE_H
#define CUSTOM_MAP_TEXTURE_H

#include "Renderer.h"
#include <string>

/*Represents texture in opengl.
 * Texture, here, means just a
 * loaded photo from the file*/
class Texture{
public:
    Texture();
    ~Texture();
    /*calls loadTexture*/
    Texture(const std::string& filepath);
    void deleteTexture();
    /*Creates openGl texture instance and
     * loads texture from given path to file */
    void loadTexture(const std::string& filepath);

    void bind(unsigned int slot = 0) const;
    void unbind() const;

    inline int getWidth() const {return m_width;}
    inline int getHeight() const {return m_height;}
private:
    void do_loadTexture();
private:
    unsigned int m_rendererID;
    std::string m_filePath;
    /*buffer of bytes to store the texture*/
    unsigned char* m_localBuffer;
    /*characteristics of texture*/
    int m_width, m_height, m_BPP;
};


#endif //CUSTOM_MAP_TEXTURE_H
