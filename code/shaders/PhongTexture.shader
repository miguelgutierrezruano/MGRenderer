
// Distributed under MIT License
// @miguelgutierrezruano
// 2023

#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

out vec3 vertexNormal;
out vec2 vertexTexCoord;
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
    vertexTexCoord = texCoord;

    fragPos = vec3(model * vec4(position, 1));
    gl_Position = projection * view * model * vec4(position, 1);
}

#shader fragment
#version 330 core

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

in vec3 vertexNormal;
in vec2 vertexTexCoord;
in vec3 fragPos;

out vec4 color;

uniform Material material;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;

uniform sampler2D texture1;

void main()
{
    // Ambient lightning
    vec3 ambient = material.ambient * lightColor;

    // Diffuse lightning
    vec3 norm = normalize(vertexNormal);
    vec3 lightDirection = normalize(lightPos - fragPos);

    float diff = max(dot(norm, lightDirection), 0.0);
    vec3 diffuse = (diff * material.diffuse) * lightColor;

    // Specular lightning
    vec3 viewDirection = normalize(viewPos - fragPos);
    vec3 reflectDirection = reflect(-lightDirection, norm);

    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
    vec3 specular = (spec * material.specular) * lightColor;


    // Texture color
    vec4 texColor = texture(texture1, vertexTexCoord);

    // Result
    vec3 result = (ambient + diffuse + specular); // * vec3(texColor);
    color = vec4(result, 1);
}
        