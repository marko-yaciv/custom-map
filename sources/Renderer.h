//
// Created by Marko on 12.03.2021.
//

#ifndef CUSTOM_MAP_RENDERER_H
#define CUSTOM_MAP_RENDERER_H

#include "utils/pch.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

/*Renderer class that used to wrap the
 * binding of needed data for rendering, and drawing it.
 * Also calls glClear*/
class Renderer{
public:
    void draw(const VertexArray& vao, const IndexBuffer& ib, Shader& shader) const ;

    static void clear();
};
#endif //CUSTOM_MAP_RENDERER_H
