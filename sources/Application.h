//
// Created by Marko on 10.03.2021.
//

#ifndef CUSTOM_MAP_APPLICATION_H
#define CUSTOM_MAP_APPLICATION_H
//#define GLEW_STATIC
#include <iostream>
#include <cmath>
#include <vector>
#include <cstdarg>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include "Tile.h"
const std::string tilesWebUrl{"https://api.mapbox.com/styles/v1/mapbox/streets-v11/tiles/"};
const std::string tilesTokenUrl{"?access_token=pk.eyJ1IjoibWFya28teWFjaXYiLCJhIjoiY2ttYnV3azA0MjVqZTJvbnh6OHdycXVlMSJ9.cnr7gV6c1DqVMpkpBmNaDQ"};
const int SIZE_OF_PICTURE = 512;

class Application {
public:
    Application();
    ~Application() = default;

    void initWindow();
    void start();
private:
    void createWindow();
    void configurePaintingSize();
    void startWindowLoop();

    static void zoomIn();
    static void zoomOut();
    static void moveUp();
    static void moveDown();
    static void moveLeft();
    static void moveRight();

    //button events
    void setKeysCallbacks();

    static void key_pressed(GLFWwindow* window, int key, int scancode, int action, int mods);
private:
    GLFWwindow * window;
    static std::vector<Tile> map_level;
};


#endif //CUSTOM_MAP_APPLICATION_H
