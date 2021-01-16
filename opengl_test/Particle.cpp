#include "Particle.h"

SSBO initializeLayout(Random& rand_generator)
{
	std::vector<Particle> particles(5000);
	//Particle particles[1000];
	for (size_t i = 0; i < 5000; i++)
	{
		particles[i].x = rand_generator.rand_uniform(0, 300);
		particles[i].y = rand_generator.rand_uniform(0, 300);
		particles[i].z = rand_generator.rand_uniform(0, 300);
		particles[i].vx = 0;
		particles[i].vy = 0;
		particles[i].vz = 0;
		particles[i].r = 0.4;
		particles[i].g = 0.4;
		particles[i].b = 0.4;
		particles[i].size = 2;
	}
	SSBO ssbo(&particles[0], sizeof(Particle), 5000);
	return ssbo;
}