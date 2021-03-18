//
// Created by Marko on 17.03.2021.
//

#ifndef CUSTOM_MAP_TILE_H
#define CUSTOM_MAP_TILE_H

#include <vector>
#include <string>
#include <memory>
#include "Renderer.h"
#include "Texture.h"


const std::string tilesWebUrl{"https://api.mapbox.com/styles/v1/mapbox/streets-v11/tiles/512"};
const std::string tilesWebTokenUrl{"?access_token=pk.eyJ1IjoibWFya28teWFjaXYiLCJhIjoiY2ttYnV3azA0MjVqZTJvbnh6OHdycXVlMSJ9.cnr7gV6c1DqVMpkpBmNaDQ"};

enum ScreenPosition{
    TOP_LEFT = 0, TOP_RIGHT, BOTTOM_RIGHT, BOTTOM_LEFT
};

class Tile {
    typedef struct
    {
        int m_zoom;
        int m_x;
        int m_y;
    }Coordinates;
public:
    Tile(const std::string& path, Coordinates coords, const std::string& token);
    Tile();
    Tile(const Tile&);
    Tile(ScreenPosition scPosition);
    ~Tile();

    inline ScreenPosition getScreenPosition(){ return m_screenPos;};
    Coordinates getPositions();
    std::string getPathToFile();

    void specRenderAttribs(ScreenPosition scPosition);
    void dwnloadFromWeb(const std::string& path, Coordinates coords, const std::string& token);
    void loadTileTexture(const std::string& path = "");

    void draw();
    void bindToDraw();
    void replace(const Tile& other);

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void operator++();
    void operator--();

    void showInfo();
    void unbindFromDraw();

private:
    std::string getFilename();
    void addVerticesToGPU();
private:
    std::string m_webPath;
    std::string m_filePath;

    Coordinates m_position;
    ScreenPosition m_screenPos;

    std::vector<GLfloat> m_vertices;
    std::vector<GLuint> m_indices;

    Texture m_texture;
    Shader m_shader;
    Renderer m_renderer;
    std::unique_ptr<VertexArray> m_VAO;
    std::unique_ptr<VertexBuffer> m_VBO;
    std::unique_ptr<IndexBuffer> m_IB;
    static int s_tileCounter;
};


#endif //CUSTOM_MAP_TILE_H
