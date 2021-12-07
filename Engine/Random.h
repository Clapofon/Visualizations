#pragma once

#include <random>

namespace Engine
{


	class Random
	{
	public:
		static double randDouble(double x, double y);
		static float randFloat(float x, float y);
		static int randInt(int x, int y);

	private:
		static std::random_device m_rd;
		static std::mt19937 m_randomEngine;
	};
}
