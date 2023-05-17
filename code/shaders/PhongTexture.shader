
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
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct DirectionalLight
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight 
{
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection);
vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDirection);

in vec3 vertexNormal;
in vec2 vertexTexCoord;
in vec3 fragPos;

out vec4 color;

uniform Material material;

uniform DirectionalLight dirLight;
uniform PointLight pointLight;

uniform vec3 viewPos;

void main()
{
    // properties
    vec3 norm = normalize(vertexNormal);
    vec3 viewDir = normalize(viewPos - fragPos);

    // Calculate directional light
    vec3 result = CalculateDirectionalLight(dirLight, norm, viewDir);

    // Calculate point light
    result += CalculatePointLight(pointLight, norm, fragPos, viewDir);

    color = vec4(result, 1.0);
}

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection)
{
    vec3 lightDir = normalize(-light.direction);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDirection, reflectDir), 0.0), material.shininess);

    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, vertexTexCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, vertexTexCoord));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, vertexTexCoord));

    return (ambient + diffuse + specular);
}

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDirection)
{
    vec3 lightDir = normalize(light.position - fragPos);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDirection, reflectDir), 0.0), material.shininess);

    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
        light.quadratic * (distance * distance));

    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, vertexTexCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, vertexTexCoord));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, vertexTexCoord));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}
        