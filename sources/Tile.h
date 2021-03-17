//
// Created by Marko on 17.03.2021.
//

#ifndef CUSTOM_MAP_TILE_H
#define CUSTOM_MAP_TILE_H

#include <vector>
#include <string>
#include "VertexArray.h"
#include "Renderer.h"
#include "Texture.h"
#include "Shader.h"

enum class ScreenPosition{
    TOP_LEFT = 0, TOP_RIGHT, BOTTOM_RIGHT, BOTTOM_LEFT
};

class Tile {
public:
    Tile(const std::string& path);
    Tile();
    ~Tile();
    void dwnloadFromWeb(const std::string& path);
    void uploadToScreen();
    void specRenderAttribs(ScreenPosition scPosition);
    std::string getPathToFile();
private:
    std::string getFilename();
    void addVerticesToGPU();
private:
    std::string m_webPath;
    std::string m_filePath;
    typedef struct
    {
        unsigned m_zoom;
        unsigned m_x;
        unsigned m_y;
    }Coordinates;
    Coordinates position;

    std::vector<GLfloat> m_vertices;
    std::vector<GLuint> m_indices;

    Texture m_texture;
    Shader m_shader;
    static int s_tileCounter;
};


#endif //CUSTOM_MAP_TILE_H
