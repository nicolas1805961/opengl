#version 440

struct DirLight
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

struct Torch
{
    vec3 position;
    vec3 direction;
    float nearBorder;
    float farBorder;
    float constant;
    float linear;
    float quadratic;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform vec3 objectDiffuse;
uniform vec3 objectSpecular;
uniform float shininess;
uniform bool night;
uniform bool torchOn;
uniform sampler2D shadowMap;
uniform DirLight dirLight;
uniform PointLight pointLights[5];
uniform Torch torch;
//uniform vec4 fogColor;

out vec4 color;

in vec4 positionToLight;
in vec3 Normal;
in vec3 vertexPosition;
//in float visibility;

uniform vec3 viewPos;

float isInShadow(vec4 positionToLight, float angle)
{
    vec3 normalizedLightPosition = (vec3(positionToLight.xyz / positionToLight.w) * 0.5) + 0.5;
    if (normalizedLightPosition.z > 1.0)
        return 1.0;
    float nearest = texture(shadowMap, normalizedLightPosition.xy).r;
    float bias = max(0.2 * (1.0 - angle), 0.005);
    return (normalizedLightPosition.z - bias > nearest ? 0.0: 1.0);
}

vec3 addDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDirection = normalize(light.direction);
    float diffuseCoefficient = max(dot(normal, -lightDirection), 0.0);
    vec3 reflectionDirection = reflect(lightDirection, normal);
    float specularCoefficient = pow(max(dot(viewDir, reflectionDirection), 0.0), shininess);
    vec3 ambientLighting = light.ambient * objectDiffuse;
    vec3 diffuseLighting = light.diffuse * diffuseCoefficient * objectDiffuse;
    vec3 specularLighting = light.specular * specularCoefficient * objectSpecular;
    if (night)
        return ((ambientLighting + diffuseLighting + specularLighting) * (1 / 150000));
    return (ambientLighting + (isInShadow(positionToLight, diffuseCoefficient) * (diffuseLighting + specularLighting)));
}

vec3 addPointLight(PointLight light, vec3 normal, vec3 vertexPos, vec3 viewDir)
{
    vec3 lightDirection = normalize(vertexPos - light.position);
    float diffuseCoefficient = max(dot(normal, -lightDirection), 0.0);
    vec3 reflectionDirection = reflect(lightDirection, normal);
    float specularCoefficient = pow(max(dot(viewDir, reflectionDirection), 0.0), shininess);
    float distance = length(light.position - vertexPos);
    float distanceFading = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    vec3 ambient = light.ambient * objectDiffuse;
    vec3 diffuse = light.diffuse * diffuseCoefficient * objectDiffuse;
    vec3 specular = light.specular * specularCoefficient * objectSpecular;
    return ((ambient + diffuse + specular) * distanceFading);
}

vec3 addTorch(Torch light, vec3 normal, vec3 vertexPos, vec3 viewDir)
{
    vec3 lightDirection = normalize(vertexPos - light.position);
    float diffuseCoefficient = max(dot(normal, -lightDirection), 0.0);
    vec3 reflectionDirection = reflect(lightDirection, normal);
    float specularCoefficient = pow(max(dot(viewDir, reflectionDirection), 0.0), shininess);
    float distance = length(light.position - vertexPos);
    float distanceFading = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    float theta = dot(-lightDirection, normalize(-light.direction));
    float epsilon = light.nearBorder - light.farBorder;
    float intensity = clamp((theta - light.farBorder) / epsilon, 0.0, 1.0);
    vec3 ambient = light.ambient * objectDiffuse;
    vec3 diffuse = light.diffuse * diffuseCoefficient * objectDiffuse;
    vec3 specular = light.specular * specularCoefficient * objectSpecular;
    return ((ambient + diffuse + specular) * distanceFading * intensity);
}

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - vertexPosition);
    vec3 result = addDirLight(dirLight, norm, viewDir);
    if (night)
    {
        for (int i = 0; i < 5; i++)
            result += addPointLight(pointLights[i], norm, vertexPosition, viewDir);
        if (torchOn)
            result += addTorch(torch, norm, vertexPosition, viewDir);
    }
    color = vec4(result, 1.0);
    //color = mix(fogColor, vec4( result, 1.0 ), visibility);
}