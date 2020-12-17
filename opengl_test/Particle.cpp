#include "Particle.h"

SSBO initializeLayout()
{
	Particle particles[100];
	for (size_t i = 0; i < 100; i++)
	{
		particles[i].x = 0;
		particles[i].y = 0;
		particles[i].z = 0;
		particles[i].r = 0.5;
		particles[i].g = 0.5;
		particles[i].b = 0.5;
		particles[i].lifespan = 10;
		particles[i].size = 4;
	}
	SSBO ssbo(&particles[0], sizeof(Particle), 100);
	return ssbo;
}