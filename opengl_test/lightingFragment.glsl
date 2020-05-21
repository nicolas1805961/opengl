#version 440

struct LightProperty
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct ObjectProperty
{
    vec3 objectDiffuse;
    vec3 objectSpecular;
    float shininess;
};

struct Fading
{
    float constant;
    float linear;
    float quadratic;
};

struct DirLight
{
    vec3 direction;
    LightProperty lightProperty;
};

struct PointLight
{
    vec3 position;
    Fading fading;
    LightProperty lightProperty;
};

struct Torch
{
    vec3 position;
    vec3 direction;
    float nearBorder;
    float farBorder;
    Fading fading;
    LightProperty lightProperty;
};
uniform ObjectProperty objectProperty;
uniform bool night;
uniform bool torchOn;
uniform sampler2D shadowMap;
uniform DirLight dirLight;
uniform PointLight pointLights[1];
uniform Torch torch;
uniform float time;
uniform bool flashOn;
uniform bool isLamp;
//uniform vec4 fogColor;

out vec4 color;

in vec4 positionToLight;
in vec3 Normal;
in vec3 vertexPosition;
//in float visibility;

uniform vec3 viewPosition;

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
    float specularCoefficient = pow(max(dot(viewDir, reflectionDirection), 0.0), objectProperty.shininess);
    vec3 ambientLighting = light.lightProperty.ambient * objectProperty.objectDiffuse;
    vec3 diffuseLighting = light.lightProperty.diffuse * diffuseCoefficient * objectProperty.objectDiffuse;
    vec3 specularLighting = light.lightProperty.specular * specularCoefficient * objectProperty.objectSpecular;
    if (night)
        return ((ambientLighting + diffuseLighting + specularLighting) * (1 / 150000));
    return (ambientLighting + (isInShadow(positionToLight, diffuseCoefficient) * (diffuseLighting + specularLighting)));
}

vec3 addPointLight(PointLight light, vec3 normal, vec3 vertexPos, vec3 viewDir)
{
    vec3 lightDirection = normalize(vertexPos - light.position);
    float diffuseCoefficient = max(dot(normal, -lightDirection), 0.0);
    vec3 reflectionDirection = reflect(lightDirection, normal);
    float specularCoefficient = pow(max(dot(viewDir, reflectionDirection), 0.0), objectProperty.shininess);
    float distance = length(light.position - vertexPos);
    float distanceFading = 1.0f / (light.fading.constant + light.fading.linear * distance + light.fading.quadratic * pow(distance, 2));
    vec3 ambient = light.lightProperty.ambient * objectProperty.objectDiffuse;
    vec3 diffuse = light.lightProperty.diffuse * diffuseCoefficient * objectProperty.objectDiffuse;
    vec3 specular = light.lightProperty.specular * specularCoefficient * objectProperty.objectSpecular;
    return ((ambient + diffuse + specular) * distanceFading);
}

vec3 addTorch(Torch light, vec3 normal, vec3 vertexPos, vec3 viewDir)
{
    vec3 lightDirection = normalize(vertexPos - light.position);
    float diffuseCoefficient = max(dot(normal, -lightDirection), 0.0);
    vec3 reflectionDirection = reflect(lightDirection, normal);
    float specularCoefficient = pow(max(dot(viewDir, reflectionDirection), 0.0), objectProperty.shininess);
    float distance = length(light.position - vertexPos);
    float distanceFading = 1.0f / (light.fading.constant + light.fading.linear * distance + light.fading.quadratic * pow(distance, 2));
    float theta = dot(-lightDirection, normalize(-light.direction));
    float epsilon = light.nearBorder - light.farBorder;
    float intensity = clamp((theta - light.farBorder) / epsilon, 0.0, 1.0);
    vec3 ambient = light.lightProperty.ambient * objectProperty.objectDiffuse;
    vec3 diffuse = light.lightProperty.diffuse * diffuseCoefficient * objectProperty.objectDiffuse;
    vec3 specular = light.lightProperty.specular * specularCoefficient * objectProperty.objectSpecular;
    return ((ambient + diffuse + specular) * distanceFading * intensity);
}

void main()
{
    bool on = (sin(time) < 0.99);
    if (isLamp)
    {
        if (flashOn && !on)
            color = vec4(0.0, 0.0, 0.0, 1.0);
        else
            color = vec4(1.0, 1.0, 1.0, 1.0);
    }
    else
    {
        vec3 normal = normalize(Normal);
        vec3 viewDirection = normalize(viewPosition - vertexPosition);
        vec3 amountOfLight = addDirLight(dirLight, normal, viewDirection);
        if (night)
        {
            for (int i = 0; i < 1; i++)
            {
                if (flashOn && !on)
                {
                    amountOfLight += vec3(0.0);
                    continue;
                }
                amountOfLight += addPointLight(pointLights[i], normal, vertexPosition, viewDirection);
            }
            if (torchOn)
                amountOfLight += addTorch(torch, normal, vertexPosition, viewDirection);
        }
        color = vec4(amountOfLight, 1.0);
        //color = mix(fogColor, vec4( result, 1.0 ), visibility);
    }
}