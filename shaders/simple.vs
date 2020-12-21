#version 330 core
layout (location = 0) in vec3 pos;

//out vec3 ourColor;

uniform float uni_offset_x;
uniform float uni_offset_y;

void main()
{
    gl_Position = vec4(pos.x + uni_offset_x, pos.y+uni_offset_y, pos.z, 1.0);
}
