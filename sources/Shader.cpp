//
// Created by Marko on 12.03.2021.
//

#include "Shader.h"
#include <fstream>
#include <string>
#include <sstream>
#include "Renderer.h"

enum class ShaderType{
    NONE = -1, VERTEX = 0, FRAGMENT = 1
};

ShadersSources Shader::parseFile(const std::string &filename)
{
    std::ifstream stream(filename);
    std::string line;
    ShaderType type = ShaderType::NONE;
    std::stringstream ss[2];;

    while (getline(stream,line))
    {
        if(line.find("#shader") != std::string::npos)
        {
            if(line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        }
        else
        {
                ss[(int)type] << line << "\n";
        }
    }
    return {ss[0].str(), ss[1].str()};
}

Shader::Shader(const std::string &filePath)
            :m_filePath(filePath), m_rendererID(0)
{
    initialise(filePath);
}

Shader::Shader():
        m_filePath(""), m_rendererID(0)
{

}

void Shader::initialise(const std::string &filePath)
{
    if(m_rendererID != 0)
    {
        return;
    }
    m_filePath = filePath;
    ShadersSources programSources = parseFile(m_filePath);
    m_rendererID = createShader(programSources.vertexSource,programSources.fragmentSource);
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_rendererID));
}

void Shader::bind() const
{
    GLCall(glUseProgram(m_rendererID));
}

void Shader::unbind() const
{
    GLCall(glUseProgram(0));
}

void Shader::setUniform4f(const std::string &name, float v0, float v1, float v2, float v3)
{
    GLCall(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}

unsigned int Shader::compileShader(unsigned int type, const std::string &source)
{
    unsigned int shader;
    const char* src = source.c_str();

    GLCall(shader = glCreateShader(type));
    GLCall(glShaderSource(shader, 1, &src, NULL));
    GLCall(glCompileShader(shader));

    return shader;
}

unsigned int Shader::createShader(const std::string &vertexShader,
                                  const std::string &fragmentShader) {
    unsigned int vSh = compileShader(GL_VERTEX_SHADER,vertexShader);
    unsigned int fSh = compileShader(GL_FRAGMENT_SHADER,fragmentShader);

    unsigned int shaderProgram;
    GLCall(shaderProgram = glCreateProgram());
    GLCall(glAttachShader(shaderProgram, vSh));
    GLCall(glAttachShader(shaderProgram, fSh));
    GLCall(glLinkProgram(shaderProgram));
    return shaderProgram;
}

int Shader::getUniformLocation(const std::string &name)
{

    GLCall( int location =  glGetUniformLocation(m_rendererID, name.c_str()));
    if(location == -1)
    {
        std::cout << "warning: uniform '" << name << "' doesn't exist" <<  std::endl;
    }
    return location;
}

void Shader::setUniform1i(const std::string &name, int value)
{
    GLCall(glUniform1i(getUniformLocation(name), value));
}

