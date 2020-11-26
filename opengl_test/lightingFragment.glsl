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

struct DirLight
{
    vec3 direction;
    LightProperty lightProperty;
};

struct Lamp
{
    vec3 position;
    LightProperty lightProperty;
};

struct Torch
{
    vec3 position;
    vec3 direction;
    float nearBorder;
    float farBorder;
    LightProperty lightProperty;
};

struct Utils
{
    vec3 normal;
    vec3 viewDirection;
};

uniform ObjectProperty objectProperty;
uniform bool night;
uniform bool torchOn;
uniform sampler2D shadowMap;
uniform DirLight dirLight;
uniform Lamp lamps[1];
uniform Torch torch;
//uniform Torch torches[1];
uniform float time;
uniform bool flashOn;
uniform bool isLamp;
//uniform vec4 fogColor;

out vec4 colorF;
in vec4 positionToLight;
in vec3 Normal;
in vec3 vertexPosition;
//in float visibility;

uniform vec3 viewPosition;

/*float isInShadow(vec4 positionToLight, float angle)
{
    vec3 normalizedLightPosition = (vec3(positionToLight.xyz / positionToLight.w) * 0.5) + 0.5;
    if (normalizedLightPosition.z > 1.0)
        return 1.0;
    float nearest = texture(shadowMap, normalizedLightPosition.xy).r;
    float bias = max(0.2 * (1.0 - angle), 0.005);
    return (normalizedLightPosition.z - bias > nearest ? 0.0: 1.0);
}*/

vec3 addDirLight(DirLight light, Utils tools)
{
    vec3 lightDirection = normalize(light.direction);
    float diffuseCoefficient = max(dot(tools.normal, -lightDirection), 0.0);
    vec3 reflectionDirection = reflect(lightDirection, tools.normal);
    float specularCoefficient = pow(max(dot(tools.viewDirection, reflectionDirection), 0.0), objectProperty.shininess);
    vec3 ambientLighting = light.lightProperty.ambient * objectProperty.objectDiffuse;
    vec3 diffuseLighting = light.lightProperty.diffuse * diffuseCoefficient * objectProperty.objectDiffuse;
    vec3 specularLighting = light.lightProperty.specular * specularCoefficient * objectProperty.objectSpecular;
    if (night)
        return ((ambientLighting + diffuseLighting + specularLighting) * (1 / 150000));
    return (ambientLighting + diffuseLighting + specularLighting);
    //return (ambientLighting + (isInShadow(positionToLight, diffuseCoefficient) * (diffuseLighting + specularLighting)));
}

vec3 addLamp(Lamp light, Utils tools)
{
    vec3 lightDirection = normalize(vertexPosition - light.position);
    float diffuseCoefficient = max(dot(tools.normal, -lightDirection), 0.0);
    vec3 reflectionDirection = reflect(lightDirection, tools.normal);
    float specularCoefficient = pow(max(dot(tools.viewDirection, reflectionDirection), 0.0), objectProperty.shininess);
    float distance = length(light.position - vertexPosition);
    float distanceFading = 1.0f / pow(distance, 2);
    vec3 ambient = light.lightProperty.ambient * objectProperty.objectDiffuse;
    vec3 diffuse = light.lightProperty.diffuse * diffuseCoefficient * objectProperty.objectDiffuse;
    vec3 specular = light.lightProperty.specular * specularCoefficient * objectProperty.objectSpecular;
    return ((ambient + diffuse + specular) * distanceFading);
}

vec3 addTorch(Torch light, Utils tools)
{
    vec3 lightDirection = normalize(vertexPosition - light.position);
    float diffuseCoefficient = max(dot(tools.normal, -lightDirection), 0.0);
    vec3 reflectionDirection = reflect(lightDirection, tools.normal);
    float specularCoefficient = pow(max(dot(tools.viewDirection, reflectionDirection), 0.0), objectProperty.shininess);
    float distance = length(light.position - vertexPosition);
    float distanceFading = 1.0f / pow(distance, 2);
    float angleFragmentDirection = dot(-lightDirection, normalize(-light.direction));
    float intensity = 0;
    if (angleFragmentDirection >= light.nearBorder)
        intensity = 1.0;
    else if (angleFragmentDirection <= light.farBorder)
        intensity = 0;
    else
    {
        float beta = light.nearBorder - light.farBorder;
        float alpha = light.nearBorder - angleFragmentDirection;
        intensity = 1.0 - (alpha / beta);
    }
    vec3 ambient = light.lightProperty.ambient * objectProperty.objectDiffuse;
    vec3 diffuse = light.lightProperty.diffuse * diffuseCoefficient * objectProperty.objectDiffuse;
    vec3 specular = light.lightProperty.specular * specularCoefficient * objectProperty.objectSpecular;
    return ((ambient + diffuse + specular) * distanceFading * intensity);
}

vec4 addLighting()
{
    bool on = (fract(sin(time * 0.001)*100000.0) < 0.9);
    if (isLamp)
    {
        if (flashOn && !on)
            return vec4(0.0, 0.0, 0.0, 1.0);
        else
            return vec4(1.0, 1.0, 1.0, 1.0);
    }
    else
    {
        Utils tools = {normalize(Normal), normalize(viewPosition - vertexPosition)};
        vec3 amountOfLight = addDirLight(dirLight, tools);
        for (int i = 0; i < 1; i++)
        {
            if (flashOn && !on)
            {
                amountOfLight += vec3(0.0);
                continue;
            }
            amountOfLight += addLamp(lamps[i], tools);
        }
        if (torchOn)
            amountOfLight += addTorch(torch, tools);
        return vec4(amountOfLight, 1.0);
        //color = mix(fogColor, vec4( result, 1.0 ), visibility);
    }
}

void main()
{
    colorF = addLighting();
}