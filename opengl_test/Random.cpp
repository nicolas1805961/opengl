#include "Random.h"

Random::Random(): m_generator(std::random_device()())
{}

float Random::rand_uniform(float min, float max)
{
	std::uniform_real_distribution<float> distribution(min, max);
	return distribution(m_generator);
}

float Random::rand_normal(float mean, float std, bool no_negative, bool rand_sign)
{
	std::normal_distribution<float> distribution(mean, std);
	float x = -1.0f;
	if (no_negative)
	{
		while (x < 0)
			x = distribution(m_generator);
	}
	else
		x = distribution(m_generator);
	if (rand_sign)
	{
		if (rand_uniform(-1, 1) < 0)
			x *= -1;
	}
	return x;
}
