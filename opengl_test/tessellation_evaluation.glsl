#version 440

layout (quads, equal_spacing, ccw) in;

in vec3 tes_normal[];
out vec3 Normal;
out vec3 vertexPosition;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    vec3 p1_normal = mix(tes_normal[0], tes_normal[1], gl_TessCoord.x);
    vec3 p2_normal = mix(tes_normal[2], tes_normal[3], gl_TessCoord.x);
    Normal = normalize(mat3(transpose(inverse(model))) * mix(p1_normal, p2_normal, gl_TessCoord.y));

    vec3 p1_vp = vec3(mix(gl_in[0].gl_Position, gl_in[1].gl_Position, gl_TessCoord.x));
    vec3 p2_vp = vec3(mix(gl_in[2].gl_Position, gl_in[3].gl_Position, gl_TessCoord.x));
    vertexPosition = vec3(model * vec4(mix(p1_normal, p2_normal, gl_TessCoord.y), 1.0));
	// Interpolate along bottom edge using x component of the
    // tessellation coordinate
    vec4 p1 = mix(gl_in[0].gl_Position, gl_in[1].gl_Position, gl_TessCoord.x);
    // Interpolate along top edge using x component of the
    // tessellation coordinate
    vec4 p2 = mix(gl_in[2].gl_Position, gl_in[3].gl_Position, gl_TessCoord.x);
    // Now interpolate those two results using the y component
    // of tessellation coordinate
    gl_Position = projection * view * model * mix(p1, p2, gl_TessCoord.y);
}