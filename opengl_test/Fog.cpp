#include "Fog.h"

Fog::Fog(Shader const& shader, float density, float gradient, Vector3 const& fogColorDay, Vector3 const& fogColorNight, bool night)
{
	shader.bind();
	shader.set_uniform_1f("density", density);
	shader.set_uniform_1f("gradient", gradient);
	if (night)
		shader.set_uniform_4f("fogColor", fogColorNight.get_x(), fogColorNight.get_y(), fogColorNight.get_z(), 1.0f);
	else
		shader.set_uniform_4f("fogColor", fogColorDay.get_x(), fogColorDay.get_y(), fogColorDay.get_z(), 1.0f);

}
