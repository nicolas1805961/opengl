#version 440
layout (points) in;
layout (line_strip, max_vertices = 10) out;

in vec3 normal[1];
in vec3 sideway_vector[1];

float upward_regulation = 0.005;
float sideway_regulation = 0.00005;
  
uniform mat4 projection;

void GenerateLine(int index)
{
    gl_Position = projection * gl_in[index].gl_Position;
    EmitVertex();
    gl_Position = projection * (gl_in[index].gl_Position + vec4(normal[index], 0.0) * upward_regulation);
    EmitVertex();
    EndPrimitive();
}

void main()
{
    vec4 previous_position = gl_in[0].gl_Position;
    gl_Position = projection * previous_position;
    EmitVertex();
    for (int i = 0; i < 10; i++)
    {
        vec4 p = previous_position + (vec4(normal[0], 0.0) * upward_regulation) + (vec4(sideway_vector[0], 1.0) * sideway_regulation);
        sideway_regulation += 0.0005;
        previous_position = p;
        gl_Position = projection * p;
        EmitVertex();
    }
    /*gl_Position = projection * gl_in[0].gl_Position;
    EmitVertex();
    gl_Position = projection * (gl_in[0].gl_Position + vec4(normal[0], 0.0) * upward_regulation);
    EmitVertex();*/
    EndPrimitive();
}  