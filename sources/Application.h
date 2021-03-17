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

#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

typedef struct tile{
    char*m_buffer = nullptr;
    size_t m_size = 0;
}Tile;

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

    static size_t WriteMemoryCallback(char* ptr, size_t size, size_t nmemb);
    //button events
    void setKeysCallbacks();

    static void key_pressed(GLFWwindow* window, int key, int scancode, int action, int mods);
private:
    GLFWwindow * window;
};


#endif //CUSTOM_MAP_APPLICATION_H
