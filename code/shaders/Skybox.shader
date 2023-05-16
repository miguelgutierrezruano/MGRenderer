
// Distributed under MIT License
// @miguelgutierrezruano
// 2023

#shader vertex
#version 330 core

layout(location = 0) in vec3 position;

out vec3 TexCoords;

// View (Camera transform)
uniform mat4 view;

// Projection to NDC
uniform mat4 projection;

void main()
{
	TexCoords = position;
    gl_Position = projection * view * vec4(position, 1);
}

#shader fragment
#version 330 core

out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox;

void main()
{
	FragColor = texture(skybox, TexCoords);
}
        