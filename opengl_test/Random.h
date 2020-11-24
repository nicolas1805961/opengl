#pragma once

#include <random>

class Random
{
public:
	Random();
	float rand_uniform(float min, float max);
	float rand_normal(float mean, float std, bool no_negative, bool rand_sign);

private:
	std::mt19937 m_generator;
};

