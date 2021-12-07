#pragma once

#include <glm.hpp>

namespace Engine
{
	class Collider2D
	{
	public:
		Collider2D()
		{}

		Collider2D(int x, int y, int w, int h) 
		{
			this->x = x;
			this->y = y;
			this->w = w;
			this->h = h;
		}

		~Collider2D()
		{}

		int x, y, w, h;
	};
}


