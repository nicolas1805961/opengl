#pragma once

#include "Shader.h"

class Fog
{
public:
	Fog(Shader const& shader, float density, float gradient, Vector3 const& fogColorDay, Vector3 const& fogColorNight, bool night);

private:
};