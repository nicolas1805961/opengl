#pragma once

#include "Vector3.h"
#include "VertexArray.h"
#include "SSBO.h"
#include "Random.h"

struct Particle
{
	float x, y, z;
	float vx, vy, vz;
	float r, g, b;
	float size;
};

SSBO initializeLayout(Random& rand_generator);