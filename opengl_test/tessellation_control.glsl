# version 440

layout (vertices = 4) out;

in vec3 tcs_normal[];
out vec3 tes_normal[];

void main()
{

	tes_normal[gl_InvocationID] = tcs_normal[gl_InvocationID];

	gl_TessLevelOuter[0] = 4;
	gl_TessLevelOuter[1] = 4;
	gl_TessLevelOuter[2] = 4;
	gl_TessLevelOuter[3] = 4;

	gl_TessLevelInner[0] = 4;
	gl_TessLevelInner[1] = 4;

	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}