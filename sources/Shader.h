//
// Created by Marko on 12.03.2021.
//

#ifndef CUSTOM_MAP_SHADERPARSER_H
#define CUSTOM_MAP_SHADER_H
#include <iostream>

struct ShadersSources{
    std::string vertexSource;
    std::string fragmentSource;
};

/*Represents shader program.
 * It takes path to file with shaders,
 * parses it and compiles shaders and link program.
 * Also provides setting of uniforms*/
class Shader {
public:
    Shader(const std::string& filePath);
    Shader();
    ~Shader();
    void bind() const;
    void unbind() const;


    void initialise(const std::string& filePath);
    ShadersSources parseFile(const std::string &filename);
    /*to set color*/
    void setUniform4f(const std::string& name, float v0,float v1, float v2, float v3);
    /*to set texture*/
    void setUniform1i(const std::string& name, int value);

private:
    /*type can be GL_VERTEX_SHADER or GL_FRAGMENT_SHADER*/
    unsigned int compileShader(unsigned int type, const std::string& source);
    unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);

    int getUniformLocation(const std::string& name);
    /*path to shader program file*/
    std::string m_filePath;
    unsigned int m_rendererID;
};

#endif //CUSTOM_MAP_SHADERPARSER_H
