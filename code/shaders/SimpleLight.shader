
// Distributed under MIT License
// @miguelgutierrezruano
// 2023

#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

out vec3 vertexColor;

// Object transform
uniform mat4 model;

// View (Camera transform)
uniform mat4 view;

// Projection to NDC
uniform mat4 projection;

void main()
{
    vertexColor = color;
    gl_Position = projection * view * model * vec4(position, 1);
}

#shader fragment
#version 330 core

in vec3 vertexColor;

out vec4 color;

uniform vec3 lightColor;

void main()
{
    color = vec4(lightColor * vertexColor, 1);
}
        