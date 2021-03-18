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

class Shader {
public:
    Shader(const std::string& filePath);
    Shader();
    ~Shader();
    void bind() const;
    void unbind() const;


    void initialise(const std::string& filePath);
    ShadersSources parseFile(const std::string &filename);
    void setUniform4f(const std::string& name, float v0,float v1, float v2, float v3);
    void setUniform1i(const std::string& name, int value);

private:
    unsigned int compileShader(unsigned int type, const std::string& source);
    unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);

    int getUniformLocation(const std::string& name);
    std::string m_filePath;
    unsigned int m_rendererID;
};


#endif //CUSTOM_MAP_SHADERPARSER_H
