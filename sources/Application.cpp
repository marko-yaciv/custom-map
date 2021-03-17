//
// Created by Marko on 10.03.2021.
//
#include <cstdarg>
#include <fstream>
#include "Application.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Tile.h"
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
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
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
    std::vector<GLfloat> vertices {
            -1.0f, -1.0f, 0.0f, 0.0f,//0
             1.0f, -1.0f, 1.0f, 0.0f,//1
             1.0f,  1.0f, 1.0f, 1.0f,//2
            -1.0f,  1.0f, 0.0f, 1.0f,//3
    };

    std::vector<unsigned int> indices {
        0, 1, 2,
        2, 3, 0
    };
    VertexArray VAO;
    VertexBuffer VBO;
    VBO.setData(vertices.data(), vertices.size() * sizeof(GLfloat));

    VertexBufferLayout layout;
    layout.push(GL_FLOAT,2);
    layout.push(GL_FLOAT,2);
    VAO.addBuffer(VBO,layout);
    IndexBuffer ib(indices.data(), indices.size());

    Shader shaderProgram(R"(../../res/shaders/Base.shader)");
    shaderProgram.bind();

    Tile tile;
    tile.dwnloadFromWeb(tilesWebUrl + "1/1/1" + tilesTokenUrl);

    Texture currentTexture;
    currentTexture.loadTexture(tile.getPathToFile());
    currentTexture.bind();
    shaderProgram.setUniform1i("u_texture", 0);

    VAO.unbind();
    VBO.unbind();
    ib.unbind();
    shaderProgram.unbind();
    //currentTexture.unbind();
    while(!glfwWindowShouldClose(window))
    {
        configurePaintingSize();
        glfwPollEvents();
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        // Draw our first triangle
        shaderProgram.bind();
        VAO.bind();
        ib.bind();
        //shaderProgram.setUniform1i("u_texture", 0);

        GLCall(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr));

        glfwSwapBuffers(window);
    }
    VAO.unbind();
    VBO.unbind();
    ib.unbind();
    shaderProgram.unbind();
    //currentTexture.unbind();
}

void Application::setKeysCallbacks()
{
    glfwSetKeyCallback(window, key_pressed);
}

void Application::key_pressed(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    switch (key)
    {
        case GLFW_KEY_KP_ADD:

            break;
        case GLFW_KEY_KP_SUBTRACT:
            break;
        case GLFW_KEY_UP:
            break;
        case GLFW_KEY_DOWN:
            break;
        case GLFW_KEY_LEFT:
            break;
        case GLFW_KEY_RIGHT:
            break;
        default:
            break;
    }
}

Application::Application()
{

}

void* Realloc(void* ptr, size_t size)
{
    if(ptr)
        return realloc(ptr, size);
    else
        return malloc(size);
}

/*size_t Application::WriteMemoryCallback(char *ptr, size_t size, size_t nmemb)
{
    Tile tile;
    // Calculate the real size of the incoming buffer
    size_t realsize = size * nmemb;

    // (Re)Allocate memory for the buffer
    tile.m_buffer = (char*) Realloc(tile.m_buffer, tile.m_size + realsize);

    // Test if Buffer is initialized correctly & copy memory
    if (tile.m_buffer == NULL) {
        realsize = 0;
    }

    memcpy(&(tile.m_buffer[tile.m_size]), ptr, realsize);
    tile.m_size += realsize;

    std::ofstream os("tile.png",std::ios_base::app | std::ios_base::binary);
    os << tile.m_buffer;
    os.close();
    // return the real size of th.e buffer..
    return realsize;
}*/
