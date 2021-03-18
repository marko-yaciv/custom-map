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
#include <cmath>
#define COORD_COEFICIENT(v) pow(2,(v))
constexpr void type(ScreenPosition pos){
    switch(pos)
    {
        case TOP_LEFT:
            std::cout << "TOP_LEFT";
            break;
        case TOP_RIGHT:
            std::cout << "TOP_RIGHT";
            break;
        case BOTTOM_RIGHT:
            std::cout << "BOTTOM_RIGHT";
            break;
        case BOTTOM_LEFT:
            std::cout << "BOTTOM_LEFT";
            break;
    }
}
int Tile::s_tileCounter = 0;

Tile::Tile(const std::string& path, Coordinates coords, const std::string& token):
            m_position{coords}
{
    dwnloadFromWeb(path,coords, token);
}

Tile::Tile(ScreenPosition scPosition)
{
    specRenderAttribs(scPosition);
}

Tile::Tile():m_webPath(""), m_position{0}{}

Tile::Tile(const Tile&){}

Tile::~Tile(){}

void Tile::dwnloadFromWeb(const std::string& path, Coordinates coords, const std::string& token)
{
    m_position = {coords.m_zoom, coords.m_x, coords.m_y};
    std::string spos =  "/" + std::to_string(coords.m_zoom) + "/" +
                        std::to_string(coords.m_x) + "/" +
                        std::to_string(coords.m_y);
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

    //Just a big random number, because tiles
    // create very quickly and file always rewrites
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
    m_screenPos = scPosition;
    switch (scPosition)
    {
        case ScreenPosition::TOP_LEFT:
            m_vertices = {
                    -1.0f, 0.0f,  0.0f, 0.0f,
                     0.0f, 0.0f,  1.0f, 0.0f,
                     0.0f, 1.0f,  1.0f, 1.0f,
                    -1.0f, 1.0f,  0.0f, 1.0f

            };
            dwnloadFromWeb(tilesWebUrl,{1,0,0},tilesWebTokenUrl);
            break;
        case ScreenPosition::TOP_RIGHT:
            m_vertices = {
                    0.0f, 0.0f,  0.0f, 0.0f,
                    1.0f, 0.0f,  1.0f, 0.0f,
                    1.0f, 1.0f,  1.0f, 1.0f,
                    0.0f, 1.0f,  0.0f, 1.0f

            };
            dwnloadFromWeb(tilesWebUrl,{1,1,0},tilesWebTokenUrl);
            break;
        case ScreenPosition::BOTTOM_LEFT:
            m_vertices = {
                    -1.0f, -1.0f,  0.0f, 0.0f,
                     0.0f, -1.0f,  1.0f, 0.0f,
                     0.0f,  0.0f,  1.0f, 1.0f,
                    -1.0f,  0.0f,  0.0f, 1.0f
            };
            dwnloadFromWeb(tilesWebUrl,{1,0,1},tilesWebTokenUrl);
            break;
        case ScreenPosition::BOTTOM_RIGHT:
            m_vertices = {
                    0.0f, -1.0f,  0.0f, 0.0f,
                    1.0f, -1.0f,  1.0f, 0.0f,
                    1.0f,  0.0f,  1.0f, 1.0f,
                    0.0f,  0.0f,  0.0f, 1.0f
            };
            dwnloadFromWeb(tilesWebUrl,{1,1,1},tilesWebTokenUrl);
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
    m_VAO->addBuffer(*m_VBO, layout);
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
        m_filePath = path;
        m_texture.loadTexture(path);
     }
    m_texture.bind();
    m_shader.bind();
    m_shader.setUniform1i("u_texture",0);
}

void Tile::bindToDraw()
{

}
void Tile::draw()
{
    m_renderer.draw(*m_VAO,*m_IB,m_shader);
}
Tile::Coordinates Tile::getPositions() {
    return m_position;
}

void Tile::replace(const Tile& other)
{
    loadTileTexture(other.m_filePath);
    this->m_webPath = other.m_webPath;
    this->m_position = other.m_position;
}

void Tile::unbindFromDraw()
{
    m_VBO->unbind();
    m_VAO->unbind();
    m_IB->unbind();
    m_shader.unbind();
}


bool isMaxCoordinate(int coord, int zoom)
{
    return coord == zoom +
                    COORD_COEFICIENT(zoom);
}
bool isMinCoordinate(int coord)
{
    return coord == 0;
}
void Tile::operator++()
{
    if(!isMaxCoordinate(m_position.m_x, m_position.m_zoom))
        m_position.m_x += COORD_COEFICIENT(m_position.m_zoom - 1);
    if(!isMaxCoordinate(m_position.m_y, m_position.m_zoom))
        m_position.m_y += COORD_COEFICIENT(m_position.m_zoom - 1);
    ++m_position.m_zoom;
    dwnloadFromWeb(tilesWebUrl, m_position, tilesWebTokenUrl);
}

void Tile::operator--()
{
    if(m_position.m_zoom == 1)
        return;

    --m_position.m_zoom;
    if(!isMinCoordinate(m_position.m_x))
        m_position.m_x -= COORD_COEFICIENT(m_position.m_zoom - 1);
    if(!isMinCoordinate(m_position.m_y))
        m_position.m_y -= COORD_COEFICIENT(m_position.m_zoom - 1);
    dwnloadFromWeb(tilesWebUrl, m_position, tilesWebTokenUrl);
}

void Tile::moveUp()
{
    if(isMinCoordinate(m_position.m_y))
        return;

    --m_position.m_y;
    dwnloadFromWeb(tilesWebUrl, m_position, tilesWebTokenUrl);
}

void Tile::moveDown()
{
    if(isMaxCoordinate(m_position.m_y, m_position.m_zoom))
        return;

    ++m_position.m_y;
    dwnloadFromWeb(tilesWebUrl, m_position, tilesWebTokenUrl);
}

void Tile::moveLeft()
{
    if(isMinCoordinate(m_position.m_x))
        return;

    --m_position.m_x;
    dwnloadFromWeb(tilesWebUrl, m_position, tilesWebTokenUrl);
}

void Tile::moveRight()
{
    if(isMaxCoordinate(m_position.m_x, m_position.m_zoom))
        return;
    ++m_position.m_x;
    dwnloadFromWeb(tilesWebUrl, m_position, tilesWebTokenUrl);
}

void Tile::showInfo()
{
    type(m_screenPos);
    std:: cout << " - Z:" << m_position.m_zoom <<
               " X:" << m_position.m_x <<
               " Y:" << m_position.m_y << std::endl;
}

