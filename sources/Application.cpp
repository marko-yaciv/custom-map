//
// Created by Marko on 10.03.2021.
//
#define COORD_INCREMENT(v) pow(2,(v-1))
#include <cstdarg>
#include <fstream>
#include <cmath>
#include "Application.h"
#include "Renderer.h"

std::vector<Tile> Application::map_level(4);
void Application::initWindow()
{
    if (!glfwInit())
    {
        throw "Init failed";
    }

    //Setting version of OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //setting profile for context
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //cannot scale window
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

}
void Application::createWindow()
{
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 640, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        throw "Failed to create window";
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(2);
    setKeysCallbacks();

    //set this to use the newest functionality
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
    {
        throw "Glew init problem";
    }
}

void Application::configurePaintingSize()
{
    /*configure size of painting window for openGL*/
    int width, height;
    /*get size from GLFW*/
    glfwGetFramebufferSize(window, &width, &height);
    /*notify openGL with window size to paint*/
    glViewport(0, 0, width, height);
}

void Application::start()
{
    try
    {
        createWindow();
        std::cout << glGetString(GL_VERSION) << std::endl;

        configurePaintingSize();
        startWindowLoop();

        glfwTerminate();
    }
    catch (const char* ex)
    {
        throw ex;
    }
}

void Application::startWindowLoop()
{
    map_level[ScreenPosition::TOP_LEFT].specRenderAttribs(ScreenPosition::TOP_LEFT);
    map_level[ScreenPosition::TOP_RIGHT].specRenderAttribs(ScreenPosition::TOP_RIGHT);
    map_level[ScreenPosition::BOTTOM_RIGHT].specRenderAttribs(ScreenPosition::BOTTOM_RIGHT);
    map_level[ScreenPosition::BOTTOM_LEFT].specRenderAttribs(ScreenPosition::BOTTOM_LEFT);

    int size = 512;
    map_level[ScreenPosition::TOP_LEFT].dwnloadFromWeb(tilesWebUrl +
    std::to_string(SIZE_OF_PICTURE), 1, 0, 0, tilesTokenUrl);
    map_level[ScreenPosition::TOP_RIGHT].dwnloadFromWeb(tilesWebUrl +
    std::to_string(SIZE_OF_PICTURE), 1, 1, 0, tilesTokenUrl);
    map_level[ScreenPosition::BOTTOM_LEFT].dwnloadFromWeb(tilesWebUrl +
    std::to_string(SIZE_OF_PICTURE), 1, 0, 1, tilesTokenUrl);
    map_level[ScreenPosition::BOTTOM_RIGHT].dwnloadFromWeb(tilesWebUrl +
    std::to_string(SIZE_OF_PICTURE), 1, 1, 1, tilesTokenUrl);
    //Tile test;
    //test.specRenderAttribs(ScreenPosition::TOP_LEFT);

    while(!glfwWindowShouldClose(window))
    {
        configurePaintingSize();
        glfwPollEvents();
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        for(auto&tile : map_level)
        {
            tile.loadTileTexture();
            tile.bindToDraw();
            tile.draw();
        }

        glfwSwapBuffers(window);
    }
}

void Application::setKeysCallbacks()
{
    glfwSetKeyCallback(window, key_pressed);
}

void Application::key_pressed(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_KP_ADD && action == GLFW_PRESS){
        zoomIn();
    }
    else if(key == GLFW_KEY_KP_SUBTRACT && action == GLFW_PRESS){
        zoomOut();
    }
    /*switch (key)
    {
        case GLFW_KEY_KP_ADD:
            break;
        case GLFW_KEY_KP_SUBTRACT:
            zoomOut();
            break;
        case GLFW_KEY_UP:
            moveUp();
            break;
        case GLFW_KEY_DOWN:
            moveDown();
            break;
        case GLFW_KEY_LEFT:
            moveLeft();
            break;
        case GLFW_KEY_RIGHT:
            moveRight();
            break;
        default:
            break;
    }*/
}

Application::Application()
{

}

void Application::zoomIn()
{
    for(auto&tile : map_level){
        auto pos = tile.getPositions();
        int z = pos.m_zoom + 1;
        tile.dwnloadFromWeb(tilesWebUrl + std::to_string(SIZE_OF_PICTURE),
                ++pos.m_zoom,
                pos.m_x + COORD_INCREMENT(pos.m_zoom),
                pos.m_y + COORD_INCREMENT(pos.m_zoom),tilesTokenUrl);
        tile.loadTileTexture();
        tile.bindToDraw();
    }
    std::cout << std::endl;
}

void Application::zoomOut()
{

    for(auto&tile : map_level){
        auto pos = tile.getPositions();
        --pos.m_zoom;
        pos.m_x -=  pow(2, pos.m_zoom);
        pos.m_y -=  pow(2, pos.m_zoom);

        tile.dwnloadFromWeb(tilesWebUrl + std::to_string(SIZE_OF_PICTURE),
                            --pos.m_zoom,
                            pos.m_x - COORD_INCREMENT(pos.m_zoom),
                            pos.m_y - COORD_INCREMENT(pos.m_zoom), tilesTokenUrl);
        tile.loadTileTexture();
        tile.bindToDraw();
    }
    std::cout << std::endl;
}

void Application::moveUp()
{
    /*auto pos = map_level[ScreenPosition::TOP_LEFT].getPositions();
    //replacing all fields under TOP_LEFT with fields under BOTTOM_LEFT
    map_level[ScreenPosition::TOP_LEFT].replace(map_level[ScreenPosition::BOTTOM_LEFT]);
    //move New value from under TOP_LEFT under key BOTTOM_LEFT
    map_level.try_emplace(ScreenPosition::BOTTOM_LEFT, map_level[ScreenPosition::TOP_LEFT]);
    //loading new tile for TOP_LEFT part
    map_level[ScreenPosition::TOP_LEFT].specRenderAttribs(ScreenPosition::TOP_LEFT);
    map_level[ScreenPosition::TOP_LEFT].dwnloadFromWeb(tilesWebUrl,pos.m_zoom,pos.m_x,pos.m_y - 1, tilesTokenUrl);


    pos = map_level[ScreenPosition::TOP_RIGHT].getPositions();
    map_level[ScreenPosition::TOP_RIGHT].replace(map_level[ScreenPosition::BOTTOM_RIGHT]);
    map_level.try_emplace(ScreenPosition::BOTTOM_RIGHT, map_level[ScreenPosition::TOP_RIGHT]);

    map_level[ScreenPosition::TOP_RIGHT].specRenderAttribs(ScreenPosition::TOP_RIGHT);
    map_level[ScreenPosition::TOP_RIGHT].dwnloadFromWeb(tilesWebUrl,pos.m_zoom,pos.m_x,pos.m_y - 1, tilesTokenUrl);*/
    for(auto&tile : map_level){
        auto pos = tile.getPositions();
        tile.dwnloadFromWeb(tilesWebUrl + std::to_string(SIZE_OF_PICTURE),
                                   pos.m_zoom,
                                   pos.m_x,
                                   pos.m_y + 1, tilesTokenUrl);
    }
    std::cout << std::endl;
}

void Application::moveDown()
{
    for(auto&tile : map_level){
        auto pos = tile.getPositions();
        tile.dwnloadFromWeb(tilesWebUrl + std::to_string(SIZE_OF_PICTURE),
                                   pos.m_zoom,
                                   pos.m_x,
                                   pos.m_y - 1, tilesTokenUrl);
    }
    std::cout << std::endl;
}

void Application::moveLeft()
{
    for(auto&tile : map_level){
        auto pos = tile.getPositions();
        tile.dwnloadFromWeb(tilesWebUrl + std::to_string(SIZE_OF_PICTURE),
                                   pos.m_zoom,
                                   pos.m_x - 1,
                                   pos.m_y, tilesTokenUrl);
    }
    std::cout << std::endl;
}

void Application::moveRight()
{
    for(auto&tile : map_level){
        auto pos = tile.getPositions();
        tile.dwnloadFromWeb(tilesWebUrl + std::to_string(SIZE_OF_PICTURE),
                                   pos.m_zoom,
                                   pos.m_x + 1,
                                   pos.m_y, tilesTokenUrl);
    }
    std::cout << std::endl;
}
