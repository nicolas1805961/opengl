#pragma once

#include "Vector3.h"
#include "VertexArray.h"
#include "SSBO.h"

struct Particle
{
	float x, y, z;
	float vx, vy, vz;
	float r, g, b;
	float lifespan;
	float size;
};

SSBO initializeLayout();