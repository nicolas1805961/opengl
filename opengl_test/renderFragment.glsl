#version 440
out vec4 finalColor;
  
uniform sampler2D screenTex;
in vec2 texCoord;
uniform bool nightVisionOn;
uniform float time;

float random( vec2 p )
{
    vec2 K1 = vec2(23.14069263277926, 2.665144142690225);
    return fract(cos(dot(p, K1)) * 12345.6789);
}

void main()
{ 
    vec4 color = texture(screenTex, texCoord);
    if (!nightVisionOn)
        finalColor = color;
    else
    {
        vec2 coord = texCoord;
        coord.y *= random(vec2(coord.y, time * 0.00000001));
        color *= 10;
        float green = max(max(color.r, color.g), color.b);
        finalColor = vec4(0.0, green + random(coord) * 0.1, 0.0, color.a);
    }
}