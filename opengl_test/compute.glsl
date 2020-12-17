# version 440

layout (local_size_x = 1000) in;

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
    Particle particles[1000];
};

float rand(float x)
{
    return fract(sin(x) * 100000);
}

void main() 
{
    const float PI = 3.1415926535897932384626433832795;
    //particles[int(gl_GlobalInvocationID.x)].size += 0.01;
    particles[int(gl_GlobalInvocationID.x)].y -= (pow(float(gl_GlobalInvocationID.x), 2) / 1000000) + 0.1;
    //particles[int(gl_GlobalInvocationID.x)].y -= 0.01;
    if (particles[int(gl_GlobalInvocationID.x)].y <= -10)
    {
        particles[int(gl_GlobalInvocationID.x)].y = 10;
        float r = 10 * sqrt(rand(float(gl_GlobalInvocationID)));
        particles[int(gl_GlobalInvocationID.x)].x = r * sin(2 * PI * rand(float(gl_GlobalInvocationID) * time));
        particles[int(gl_GlobalInvocationID.x)].z = r * cos(2 * PI * rand(float(gl_GlobalInvocationID) * time));
    }
}