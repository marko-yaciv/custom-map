//
// Created by Marko on 15.03.2021.
//

#include "Texture.h"
#include "utils/stb_image.h"


Texture::Texture():
        m_rendererID(0), m_filePath(""), m_localBuffer(nullptr),
        m_width(0), m_height(0), m_BPP(0){

}
Texture::Texture(const std::string &filepath):
            Texture()
{
    m_filePath = filepath;
    do_loadTexture();
}

Texture::~Texture()
{
    GLCall(glDeleteTextures(1, &m_rendererID));
}

void Texture::bind(unsigned int slot) const
{
    GLCall(glActiveTexture(GL_TEXTURE0 + slot))
    GLCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));
}

void Texture::unbind() const
{
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture::loadTexture(const std::string &filepath)
{
    m_filePath = filepath;
    do_loadTexture();
}

void Texture::do_loadTexture() 
{
    stbi_set_flip_vertically_on_load(1);
    m_localBuffer = stbi_load(m_filePath.c_str(), &m_width, &m_height, &m_BPP, 4);

    GLCall(glGenTextures(1,&m_rendererID));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer));
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));

    if(m_localBuffer)
    {
        stbi_image_free(m_localBuffer);
    }
}

