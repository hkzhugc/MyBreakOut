#version 450 core
layout (location = 0) in vec2 v_position;
layout (location = 1) in vec2 v_texCoords;

out vec2 f_texCoords;

layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};

uniform mat4 model;

void main()
{
    f_texCoords = v_texCoords;
    gl_Position = projection * model * vec4(v_position, 0.0, 1.0);
}