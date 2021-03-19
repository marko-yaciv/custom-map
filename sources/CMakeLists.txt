find_package (OpenGL REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/includes/glfw/include)
include_directories(${PROJECT_SOURCE_DIR}/includes/glew/include)
include_directories(${PROJECT_SOURCE_DIR}/includes/libcurlpp/include)
include_directories(${PROJECT_SOURCE_DIR}/includes/libcurl/include)

link_directories(../includes/glfw/bin)
link_directories(../includes/glew/bin)
link_directories(../includes/libcurl/bin)
link_directories(../includes/libcurlpp/bin)

set(RENDER_API_SRC
        VertexBuffer.cpp VertexBuffer.h
        IndexBuffer.cpp IndexBuffer.h
        Renderer.cpp Renderer.h
        Shader.cpp Shader.h
        VertexArray.cpp VertexArray.h
        VertexBufferLayout.cpp VertexBufferLayout.h
        utils/stb_image.h utils/stb_image.cpp
        Texture.cpp Texture.h
        utils/pch.h)
set(APPLICATION_SRC
        Application.cpp Application.h
        main.cpp Tile.cpp Tile.h utils/pch.cpp)
add_executable(${CMAKE_PROJECT_NAME} ${APPLICATION_SRC} ${RENDER_API_SRC})

target_link_libraries(${CMAKE_PROJECT_NAME}
        ${OPENGL_LIBRARIES}
        libcurl.dll
        libcurlpp.dll
        glfw3.dll
        glew32.dll)


set(THIRD_PARTY_LIBS
        ${PROJECT_SOURCE_DIR}/includes/glew/bin/glew32.dll
        ${PROJECT_SOURCE_DIR}/includes/glfw/bin/glfw3.dll
        ${PROJECT_SOURCE_DIR}/includes/libcurl/bin/libcurl.dll
        ${PROJECT_SOURCE_DIR}/includes/libcurlpp/bin/libcurlpp.dll
        )
foreach (libpath ${THIRD_PARTY_LIBS})
    add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${libpath}"
            "${CMAKE_BINARY_DIR}/sources")
endforeach ()