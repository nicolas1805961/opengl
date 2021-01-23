# version 440

layout (local_size_x = 20) in;

uniform float time;
uniform float dt;

struct Particle
{
    float x, y, z;
    float vx, vy, vz;
    float r, g, b;
    float size;
};

layout (std430, binding = 1) buffer data
{
    Particle particles[20];
};

float rand(float x)
{
    return fract(sin(x) * 100000);
}

void main() 
{
    particles[int(gl_GlobalInvocationID)].y += dt * (particles[int(gl_GlobalInvocationID.x)].vy + dt * (-9.81) / 2);
    particles[int(gl_GlobalInvocationID)].vy += dt * (-0.1);
    particles[int(gl_GlobalInvocationID)].size /=  1.001;
    if (particles[int(gl_GlobalInvocationID)].y <= -1)
    {
        particles[int(gl_GlobalInvocationID.x)].x = rand(particles[int(gl_GlobalInvocationID.x)].x + time/10000) * 2 - 1;
        particles[int(gl_GlobalInvocationID.x)].y = rand(particles[int(gl_GlobalInvocationID.x)].y + time/10000);
        particles[int(gl_GlobalInvocationID.x)].vy = 0;
        particles[int(gl_GlobalInvocationID)].size = 60 ;
    }
}