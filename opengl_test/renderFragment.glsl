#version 440
out vec4 finalColor;
  
uniform sampler2D screenTex;
in vec2 texCoord;
uniform bool nightVisionOn;
uniform float time;

float random(vec2 p)
{
    vec2 K1 = vec2(10, 10000);
    return fract(cos(dot(p, K1)) * 100000.0);
}

void main()
{ 
    vec4 color = texture(screenTex, texCoord);
    if (!nightVisionOn)
        finalColor = color;
    else
    {
        float coeff = 10;
        float green = max(max(color.r, color.g), color.b) * coeff;
        float noise = random(texCoord + random(vec2(time, time))) * 0.2;
        if (green >= 1.0)
        {
            vec3 y = vec3(0.1, green, 0.1) + noise;
            finalColor = vec4(y, 1.0);
        }
        else
            finalColor = vec4(0.0, green + noise, 0.0, 1.0);
    }
}