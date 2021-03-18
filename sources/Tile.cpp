//
// Created by Marko on 17.03.2021.
//

#include "Tile.h"

#include <chrono>
#include <random>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <fstream>

int Tile::s_tileCounter = 0;
std::chrono::time_point<std::chrono::system_clock> start;

Tile::Tile(const std::string& path, int zoom, int x, int y, const std::string& token):
            m_position{zoom,x,y}
{
    dwnloadFromWeb(path,m_position.m_zoom,
            m_position.m_x,
            m_position.m_y, token);
}

Tile::Tile():
m_webPath(""), m_position{0}
{

}
Tile::Tile(const Tile&)
{

}
Tile::~Tile()
{

}

void Tile::dwnloadFromWeb(const std::string& path, int zoom, int x, int y, const std::string& token)
{
    std:: cout << "Z:" << zoom << " X:" << x << " Y:" << y << std::endl;
    m_position = {zoom, x, y};
    std::string spos =  "/" + std::to_string(zoom) + "/" +
                        std::to_string(x) + "/" +
                        std::to_string(y);
    m_webPath = path + spos + token;

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
    request.setOpt(new curlpp::options::Url(m_webPath));
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
    long long num = rand()%9999999999;
    file_specificator += std::to_string(num);
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
    screenPos = scPosition;
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
    m_VAO = std::make_unique<VertexArray>();
    m_VBO = std::make_unique<VertexBuffer>();
    m_VBO->setData(m_vertices.data(), m_vertices.size() * sizeof(GLfloat));

    VertexBufferLayout layout;
    layout.push(GL_FLOAT,2);
    layout.push(GL_FLOAT,2);
    m_VAO->addBuffer(*m_VBO,layout);
    m_IB = std::make_unique<IndexBuffer>(m_indices.data(), m_indices.size());

    m_shader.initialise(R"(../../res/shaders/Base.shader)");
    m_shader.bind();
}

void Tile::loadTileTexture(const std::string& path)
{
    if(path.empty())
    {
        m_texture.loadTexture(m_filePath);
    }
    else
     {
         m_texture.loadTexture(path);
     }
    m_texture.bind();
    m_shader.setUniform1i("u_texture",0);
}

Tile::Tile(ScreenPosition scPosition)
{
    specRenderAttribs(scPosition);
}

void Tile::bindToDraw()
{
    m_shader.bind();
    m_VAO->bind();
    m_IB->bind();
}
void Tile::draw()
{
    GLCall(glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr));
}
Tile::Coordinates Tile::getPositions() {
    return m_position;
}

void Tile::replace(const Tile& other)
{
    unbindFromDraw();
    this->m_vertices = other.m_vertices;
    this->m_indices = other.m_indices;
    this->m_shader = other.m_shader;
    this->m_texture = other.m_texture;
    this->m_filePath = other.m_filePath;
    this->m_webPath = other.m_webPath;
    this->m_position = other.m_position;
    this->m_VBO.release();
    this->m_VAO.release();
    this->m_IB.release();

    specRenderAttribs(screenPos);
}

void Tile::unbindFromDraw()
{
    m_VAO->unbind();
    m_IB->unbind();
    m_shader.unbind();
}

