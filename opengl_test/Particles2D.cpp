#include "Particle2D.h"

SSBO initializeLayoutParticles2D(Random& rand_generator)
{
	std::vector<Particle2D> particles(20);
	for (size_t i = 0; i < 20; i++)
	{
		particles[i].x = rand_generator.rand_uniform(-1.0, 1.0);
		particles[i].y = rand_generator.rand_uniform(-1.0, 1.0);
		particles[i].z = 1.0;
		particles[i].vx = 0;
		particles[i].vy = 0;
		particles[i].vz = 0;
		particles[i].r = 0.4;
		particles[i].g = 0.4;
		particles[i].b = 0.4;
		particles[i].size = 10;
	}
	SSBO ssbo(&particles[0], sizeof(Particle2D), 20, 1);
	return ssbo;
}