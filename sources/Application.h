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

/*Application class that rules game loop
 * and keyboard shortcuts for navigating map*/
class Application {
public:
    Application();
    ~Application();

    void initWindow();
    void start();
private:
    void createWindow();
    void configurePaintingSize();
    void startWindowLoop();

    /*Functions that will be called from
     * key_pressed callback function judging from pressed key*/
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
    /*vector of four tiles that will be
     * represented on the screen in one time*/
    static std::vector<Tile> map_level;
};


#endif //CUSTOM_MAP_APPLICATION_H
