#version 450 core
out vec4 frag_color;
in vec2 f_texCoords;

uniform sampler2D image;
uniform vec3      color;
void main()
{
    frag_color = vec4(color, 1.0) * texture(image, f_texCoords);
}