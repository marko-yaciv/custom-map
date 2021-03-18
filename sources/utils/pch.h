//
// Created by Marko on 18.03.2021.
//

#ifndef CUSTOM_MAP_PCH_H
#define CUSTOM_MAP_PCH_H
#include <GL/glew.h>

#define ASSERT(expr) if(!(expr)) __debugbreak();
#define GLCall(glFunc) GLClearError();\
    glFunc;\
    ASSERT(GLLogCall(#glFunc, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* funcName, const char* file, int line);

#endif //CUSTOM_MAP_PCH_H
