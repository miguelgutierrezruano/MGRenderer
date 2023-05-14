
// Distributed under MIT License
// @miguelgutierrezruano
// 2023

#shader vertex
#version 330 core

layout(location = 0) in vec3 position;

// Object transform
uniform mat4 model;

// View (Camera transform)
uniform mat4 view;

// Projection to NDC
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1);
}

#shader fragment
#version 330 core

out vec4 color;

void main()
{
    color = vec4(1, 1, 1, 1);
}
        