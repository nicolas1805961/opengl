#version 440
layout (points) in;
layout (triangle_strip, max_vertices = 20) out;

in vec3 normal[1];
in vec3 direction[1];
in float height[1];

uniform float g_height;


void main()
{
    float grass_height = height[0] + g_height;
    vec3 weight = vec3(0.0, -0.1, 0.0);

    vec4 bottom_left = gl_in[0].gl_Position - vec4(direction[0], 0.0);
    gl_Position = bottom_left;
    EmitVertex();
    vec4 bottom_right = gl_in[0].gl_Position + vec4(direction[0], 0.0);
    gl_Position = bottom_right;
    EmitVertex();
    for (int i = 0; i < 9; i++)
    {
        vec4 top_left = bottom_left + vec4((normal[0] + weight) * grass_height, 0.0);
        bottom_left = top_left;
        gl_Position = top_left;
        EmitVertex();
        vec4 top_right = bottom_right + vec4((normal[0] + weight) * grass_height, 0.0);
        bottom_right = top_right;
        gl_Position = top_right;
        EmitVertex();
        weight += vec3(0.0, -grass_height*0.1, 0.0);
    }
    EndPrimitive();
}  