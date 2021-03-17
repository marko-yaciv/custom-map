//
// Created by Marko on 17.03.2021.
//

#include "Tile.h"
#include "IndexBuffer.h"

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <fstream>

int Tile::s_tileCounter = 0;

Tile::Tile(const std::string &path):
    m_webPath(path), position{0}
{
    load(path);
}

Tile::Tile():
m_webPath(""), position{0}
{

}

Tile::~Tile()
{

}

void Tile::dwnloadFromWeb(const std::string &path)
{
    curlpp::Easy request;
    std::ofstream os;
    std::string filepath = getFilename();
    os.open(filepath, std::ios_base::binary);
    if(!os.is_open())
    {
        std::cout << "invaild path" << std::endl;
        return;
    }
    request.setOpt(new curlpp::options::WriteStream(&os));
    request.setOpt(new curlpp::options::Url(path));
    request.setOpt(new curlpp::options::SslVerifyPeer(false));
    request.perform();
    os.close();
}

void createFileNameSpecificator(std::string& file_specificator)
{
    time_t curent_time;
    time(&curent_time);
    tm current_date;
    localtime_s(&current_date, &curent_time);

    /*converting date to string*/
    char str[50];
    strftime(str, 50, "%Y-%m-%d_%H-%M-%S", &current_date);
    file_specificator = str;
}

std::string Tile::getFilename()
{
    std::string fileDate;
    createFileNameSpecificator(fileDate);
    std::string filename{ R"(loadedTiles\tile_)" +
                         fileDate + ".png"};
    m_filePath = filename;
    return filename;
}

std::string Tile::getPathToFile()
{
    return m_filePath;
}

void Tile::specRenderAttribs(ScreenPosition scPosition)
{
    switch (scPosition)
    {
        case ScreenPosition::TOP_LEFT:
            m_vertices = {
                    -1.0f, 0.0f,  0.0f, 0.5f,
                     0.0f, 0.0f,  0.5f, 0.5f,
                     0.0f, 1.0f,  0.5f, 1.0f,
                    -1.0f, 1.0f,  0.0f, 1.0f

            };
            break;
        case ScreenPosition::TOP_RIGHT:
            m_vertices = {
                    0.0f, 0.0f,  0.5f, 0.5f,
                    1.0f, 0.0f,  1.0f, 0.5f,
                    1.0f, 1.0f,  1.0f, 1.0f,
                    0.0f, 1.0f,  0.5f, 1.0f

            };
            break;
        case ScreenPosition::BOTTOM_LEFT:
            m_vertices = {
                    -1.0f, -1.0f,  0.0f, 0.0f,
                     0.0f, -1.0f,  0.5f, 0.0f,
                     0.0f,  0.0f,  0.5f, 0.5f,
                    -1.0f,  0.0f,  0.0f, 0.5f
            };
            break;
        case ScreenPosition::BOTTOM_RIGHT:
            m_vertices = {
                    0.0f, -1.0f,  0.5f, 0.0f,
                    1.0f, -1.0f,  1.0f, 0.0f,
                    1.0f,  0.0f,  1.0f, 0.5f,
                    0.0f,  0.0f,  0.5f, 0.5f
            };
            break;
        default:
            m_vertices = {
                    -1.0f, -1.0f,  0.0f, 0.0f,
                     1.0f, -1.0f,  1.0f, 0.0f,
                     1.0f,  1.0f,  1.0f, 1.0f,
                    -1.0f,  1.0f,  0.0f, 1.0f
            };
            break;
    }
    m_indices = {
            0, 1, 2,
            2, 3, 0
    };
    addVerticesToGPU();
}

void Tile::addVerticesToGPU()
{
    VertexArray VAO;
    VertexBuffer VBO;
    VBO.setData(m_vertices.data(), m_vertices.size() * sizeof(GLfloat));

    VertexBufferLayout layout;
    layout.push(GL_FLOAT,2);
    layout.push(GL_FLOAT,2);
    VAO.addBuffer(VBO,layout);
    IndexBuffer ib(m_indices.data(), m_indices.size());

    m_shader.parseFile(R"(../../res/shaders/Base.shader)");
    m_shader.bind();
}

void Tile::uploadToScreen()
{
    m_texture.loadTexture(m_filePath);
    m_texture.bind();
    m_shader.setUniform1i("u_texture",0);
}

