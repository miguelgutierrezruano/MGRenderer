
// Distributed under MIT License
// @miguelgutierrezruano
// 2023

#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 color;

out vec3 vertexNormal;
out vec3 vertexColor;
out vec3 fragPos;

// Object transform
uniform mat4 model;

// View (Camera transform)
uniform mat4 view;

// Projection to NDC
uniform mat4 projection;

void main()
{
    vertexNormal = mat3(transpose(inverse(model))) * normal;
    vertexColor = color;

    fragPos = vec3(model * vec4(position, 1));
    gl_Position = projection * view * model * vec4(position, 1);
}

#shader fragment
#version 330 core

in vec3 vertexNormal;
in vec3 vertexColor;
in vec3 fragPos;

out vec4 color;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;

void main()
{
    // Ambient lightning
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse lightning
    vec3 norm = normalize(vertexNormal);
    vec3 lightDirection = normalize(lightPos - fragPos);

    float diff = max(dot(norm, lightDirection), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular lightning
    float specularStrength = 0.5;
    vec3 viewDirection = normalize(viewPos - fragPos);
    vec3 reflectDirection = reflect(-lightDirection, norm);

    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    // Result
    vec3 result = (ambient + diffuse + specular) * vertexColor;
    color = vec4(result, 1);
}
        