#include "Particle.h"

SSBO initializeLayout()
{
	Particle particles[1000];
	for (size_t i = 0; i < 1000; i++)
	{
		particles[i].x = 0;
		particles[i].y = 10;
		particles[i].z = 0;
		particles[i].r = 0.4;
		particles[i].g = 0.4;
		particles[i].b = 0.4;
		particles[i].lifespan = 10;
		particles[i].size = 4;
	}
	SSBO ssbo(&particles[0], sizeof(Particle), 1000);
	return ssbo;
}