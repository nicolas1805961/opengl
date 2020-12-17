# version 440

layout (local_size_x = 100) in;

uniform float time;

struct Particle
{
    float x, y, z;
    float r, g, b;
    float lifespan;
    float size;
};

layout (std430, binding = 0) buffer data
{
    Particle particles[100];
};

void main() 
{
    const float PI = 3.1415926535897932384626433832795;
    //particles[int(gl_GlobalInvocationID.x)].size += 0.01;
    particles[int(gl_GlobalInvocationID.x)].y -= (pow(float(gl_GlobalInvocationID.x), 2) / 100000) + 0.05;
    //particles[int(gl_GlobalInvocationID.x)].y -= 0.001;
    if (particles[int(gl_GlobalInvocationID.x)].y <= -1)
    {
        particles[int(gl_GlobalInvocationID.x)].y = 1;
        particles[int(gl_GlobalInvocationID.x)].x = sin(float(gl_GlobalInvocationID.x) + time);
    }
}