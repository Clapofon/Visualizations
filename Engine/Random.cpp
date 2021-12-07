#include "Random.h"

namespace Engine
{


	std::random_device Random::m_rd;
	std::mt19937 Random::m_randomEngine(m_rd());

	double Random::randDouble(double x, double y)
	{
		std::uniform_real_distribution<double> rand(x, y);
		return rand(m_randomEngine);
	}

	float Random::randFloat(float x, float y)
	{
		std::uniform_real_distribution<float> rand(x, y);
		return rand(m_randomEngine);
	}

	int Random::randInt(int x, int y)
	{
		std::uniform_int_distribution<int> rand(x, y);
		return rand(m_randomEngine);
	}
}