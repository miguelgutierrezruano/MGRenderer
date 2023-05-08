
// Distributed under MIT License
// @miguelgutierrezruano
// 2023

#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
//layout(location = 1) in vec3 color;

out vec3 vertexColor;

uniform mat4 modelViewProjection;

void main()
{
    vertexColor = vec3(1, 0, 0);
    gl_Position = modelViewProjection * position;
}

#shader fragment
#version 330 core

in vec3 vertexColor;

out vec4 color;

void main()
{
    color = vec4(vertexColor, 1);
}
        