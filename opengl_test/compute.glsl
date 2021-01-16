# version 440

layout (local_size_x = 1000) in;

uniform float time;
uniform float dt;
uniform vec3 viewPosition;

struct Particle
{
    float x, y, z;
    float vx, vy, vz;
    float r, g, b;
    float size;
};

layout (std430, binding = 0) buffer data
{
    Particle particles[5000];
};

float rand(float x)
{
    return fract(sin(x) * 100000);
}

void main() 
{
    const float PI = 3.1415926535897932384626433832795;
    vec3 position = vec3(particles[int(gl_GlobalInvocationID)].x, particles[int(gl_GlobalInvocationID)].y, particles[int(gl_GlobalInvocationID)].z);
    float distanceToCamera = length(position - viewPosition);
    particles[int(gl_GlobalInvocationID.x)].y += dt * (particles[int(gl_GlobalInvocationID.x)].vy + dt * (-9.81) / 2);
    particles[int(gl_GlobalInvocationID.x)].vy += dt * (-9.81);
    particles[int(gl_GlobalInvocationID.x)].size = 1 / (0.05 * distanceToCamera);
    if (particles[int(gl_GlobalInvocationID.x)].y <= 0)
    {
        particles[int(gl_GlobalInvocationID.x)].y = 100 + rand(float(gl_GlobalInvocationID));
        particles[int(gl_GlobalInvocationID.x)].vy = 0;
        float r = 10 * sqrt(rand(float(gl_GlobalInvocationID)));
        particles[int(gl_GlobalInvocationID.x)].x = r * sin(2 * PI * rand(float(gl_GlobalInvocationID) * time));
        particles[int(gl_GlobalInvocationID.x)].z = r * cos(2 * PI * rand(float(gl_GlobalInvocationID) * time));
    }
}