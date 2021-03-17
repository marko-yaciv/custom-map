#shader vertex
#version 330 core
layout (location = 0) in vec4 position;
layout (location = 1) in vec2 textCoord;

out vec2 v_textCoord;
void main()
{
    gl_Position = position;
    v_textCoord = textCoord;
}

#shader fragment
#version 330 core
layout(location = 0) out vec4 color;
in vec2 v_textCoord;

uniform sampler2D u_texture;

void main()
{
    vec4 textColor = texture(u_texture, v_textCoord);
    color = textColor;
}