//
// Created by Marko on 17.03.2021.
//

#ifndef CUSTOM_MAP_TILE_H
#define CUSTOM_MAP_TILE_H
/*
 * Define this if you want to print debug info (Tiles coordinates):
#define SHOW_DEBUG_INFO
 */

#include <vector>
#include <string>
#include <memory>
#include "Renderer.h"
#include "Texture.h"

/*Constants to store url of the map*/
const std::string tilesWebUrl{"https://api.mapbox.com/styles/v1/mapbox/streets-v11/tiles/512"};
const std::string tilesWebTokenUrl{"?access_token=pk.eyJ1IjoibWFya28teWFjaXYiLCJhIjoiY2ttYnV3azA0MjV"
                                   "qZTJvbnh6OHdycXVlMSJ9.cnr7gV6c1DqVMpkpBmNaDQ"};

/*Keeps position of tile on the screen*/
enum ScreenPosition{
    TOP_LEFT = 0, TOP_RIGHT, BOTTOM_RIGHT, BOTTOM_LEFT
};

/*Represents tile of the map.
 * It hat it's position on the screen, specified by <ScreenPosition> enum*/
class Tile {
    /*Keeps coordinates of tile in the web to download*/
    typedef struct
    {
        int m_zoom;
        int m_x;
        int m_y;
    }Coordinates;
public:
    /*Calls dwnloadFromWeb*/
    Tile(const std::string& path, Coordinates coords, const std::string& token);
    Tile();
    Tile(const Tile&);
    Tile(ScreenPosition scPosition);
    ~Tile();

    inline ScreenPosition getScreenPosition(){ return m_screenPos;};
    Coordinates getPositions();
    std::string getPathToFile();

    /*Creates vertices to be added
     * to VBO and calls <addVerticesToGPU>*/
    void specRenderAttribs(ScreenPosition scPosition);
    /*Downloads tile with passed coordinates
     * from the web and writes it into file.
     * Path to photo will be stored in m_filePath*/
    void dwnloadFromWeb(const std::string& path, Coordinates coords, const std::string& token);
    /*Loads texture with give path. (If path is "", uses m_filePath variable).
     * Initialises m_texture field.*/
    void loadTileTexture(const std::string& path = "");
    /*binds VAO, IB and shader; draws figure*/
    void draw();
    /*Changes Texture of tile with <other>'s texture*/
    void replace(Tile& other);
    /*functions to reload new tile in proper direction*/
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    /*reloads new scaled tile */
    void operator++();
    void operator--();
    /*unbinds VAO, IB and shader;*/
    void unbindFromDraw();
/*Prints tale's coordinates*/
    void showInfo();

private:
    /*creates specific filename for the tile*/
    std::string getFilename();
    /*Creates VBO, VAO, IB and shader */
    void addVerticesToGPU();
private:
    /*URL of tile*/
    std::string m_webPath;
    /*path to file with tile's photo*/
    std::string m_filePath;

    /*Coordinates of tile in the web*/
    Coordinates m_position;
    ScreenPosition m_screenPos;

    /*VBO attributes*/
    std::vector<GLfloat> m_vertices;
    /*IndexBuffer(IB)*/
    std::vector<GLuint> m_indices;

    Texture m_texture;
    Shader m_shader;
    Renderer m_renderer;
    /*pointers to buffers and array to be
     * initialised in <addVerticesToGPU> call*/
    std::unique_ptr<VertexArray> m_VAO;
    std::unique_ptr<VertexBuffer> m_VBO;
    std::unique_ptr<IndexBuffer> m_IB;

};


#endif //CUSTOM_MAP_TILE_H
