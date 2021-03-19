//
// Created by Marko on 10.03.2021.
//
#include <fstream>
#include "Application.h"

std::vector<Tile> Application::map_level(4);

Application::Application(){}

Application::~Application(){}

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
    //can scale window
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

}
void Application::createWindow()
{
    /* Create a windowed mode
     * window and its OpenGL context */
    window = glfwCreateWindow(800, 800, "Hello World", NULL, NULL);
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
    /*Configure four tiles and set
     * the initial position on the screen*/
    map_level[ScreenPosition::TOP_LEFT].specRenderAttribs(ScreenPosition::TOP_LEFT);
    map_level[ScreenPosition::TOP_RIGHT].specRenderAttribs(ScreenPosition::TOP_RIGHT);
    map_level[ScreenPosition::BOTTOM_LEFT].specRenderAttribs(ScreenPosition::BOTTOM_LEFT);
    map_level[ScreenPosition::BOTTOM_RIGHT].specRenderAttribs(ScreenPosition::BOTTOM_RIGHT);

    for(auto&tile : map_level)
    {
#ifdef SHOW_DEBUG_INFO
        tile.showInfo();
#endif
        tile.unbindFromDraw();
    }
#ifdef SHOW_DEBUG_INFO
    std::cout << std::endl;
#endif
    while(!glfwWindowShouldClose(window))
    {
        /*Check for window size and if it's changed,
         * reset new size of paining field*/
        configurePaintingSize();
        /*Check for pressed keys*/
        glfwPollEvents();
        /*calls glClear*/
        Renderer::clear();
        /*loop to refresh each tile*/
        for(auto&tile : map_level)
        {
            tile.loadTileTexture();
            tile.draw();
        }

        glfwSwapBuffers(window);
    }
    map_level.clear();
}

void Application::setKeysCallbacks()
{
    glfwSetKeyCallback(window, key_pressed);
}

void Application::key_pressed(GLFWwindow *window, int key, int scancode, int action, int mods)
{

    if(action == GLFW_PRESS)
    {
        switch (key)
        {
            case GLFW_KEY_KP_ADD:
                zoomIn();
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
        }
    }
}

void Application::zoomIn()
{
    for(auto&tile : map_level)
    {
            ++tile;
            tile.loadTileTexture();
#ifdef SHOW_DEBUG_INFO
            tile.showInfo();
#endif
    }
#ifdef SHOW_DEBUG_INFO
    std::cout << std::endl;
#endif
}

void Application::zoomOut()
{
    std::cout << std::endl;
    for(auto&tile : map_level)
    {
        --tile;
        tile.loadTileTexture();
#ifdef SHOW_DEBUG_INFO
        tile.showInfo();
#endif
    }
#ifdef SHOW_DEBUG_INFO
    std::cout << std::endl;
#endif
}

void Application::moveUp()
{
    map_level[ScreenPosition::BOTTOM_LEFT].replace(map_level[ScreenPosition::TOP_LEFT]);
    map_level[ScreenPosition::BOTTOM_RIGHT].replace(map_level[ScreenPosition::TOP_RIGHT]);

    for(auto&tile : map_level)
    {

        if(tile.getScreenPosition() == ScreenPosition::TOP_LEFT ||
                tile.getScreenPosition() == ScreenPosition::TOP_RIGHT)
        {
            tile.moveUp();
            tile.loadTileTexture();
        }
#ifdef SHOW_DEBUG_INFO
        tile.showInfo();
#endif
    }
#ifdef SHOW_DEBUG_INFO
    std::cout << std::endl;
#endif
}

void Application::moveDown()
{
    map_level[ScreenPosition::TOP_LEFT].replace(map_level[ScreenPosition::BOTTOM_LEFT]);
    map_level[ScreenPosition::TOP_RIGHT].replace(map_level[ScreenPosition::BOTTOM_RIGHT]);

    for(auto&tile : map_level)
    {

        if(tile.getScreenPosition() == ScreenPosition::BOTTOM_LEFT ||
           tile.getScreenPosition() == ScreenPosition::BOTTOM_RIGHT)
        {
            tile.moveDown();
            tile.loadTileTexture();
        }
#ifdef SHOW_DEBUG_INFO
        tile.showInfo();
#endif
    }
#ifdef SHOW_DEBUG_INFO
    std::cout << std::endl;
#endif
}

void Application::moveLeft()
{
    map_level[ScreenPosition::TOP_RIGHT].replace(map_level[ScreenPosition::TOP_LEFT]);
    map_level[ScreenPosition::BOTTOM_RIGHT].replace(map_level[ScreenPosition::BOTTOM_LEFT]);

    for(auto&tile : map_level)
    {
        if(tile.getScreenPosition() == ScreenPosition::TOP_LEFT ||
           tile.getScreenPosition() == ScreenPosition::BOTTOM_LEFT)
        {
            tile.moveLeft();
            tile.loadTileTexture();
        }
#ifdef SHOW_DEBUG_INFO
        tile.showInfo();
#endif
    }
#ifdef SHOW_DEBUG_INFO
    std::cout << std::endl;
#endif
}

void Application::moveRight()
{
    map_level[ScreenPosition::TOP_LEFT].replace(map_level[ScreenPosition::TOP_RIGHT]);
    map_level[ScreenPosition::BOTTOM_LEFT].replace(map_level[ScreenPosition::BOTTOM_RIGHT]);

    for(auto&tile : map_level)
    {

        if(tile.getScreenPosition() == ScreenPosition::TOP_RIGHT ||
           tile.getScreenPosition() == ScreenPosition::BOTTOM_RIGHT)
        {
            tile.moveRight();
            tile.loadTileTexture();
        }
#ifdef SHOW_DEBUG_INFO
        tile.showInfo();
#endif
    }
#ifdef SHOW_DEBUG_INFO
    std::cout << std::endl;
#endif
}
