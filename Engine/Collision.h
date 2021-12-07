#pragma once

#include "Collider2D.h"

namespace Engine
{
	class Collision
	{
	public:
		static bool AABB(Collider2D A, Collider2D B)
		{
            //The sides of the rectangles
            int leftA, leftB;
            int rightA, rightB;
            int topA, topB;
            int bottomA, bottomB;

            //Calculate the sides of rect A
            leftA = A.x;
            rightA = A.x + A.w;
            topA = A.y;
            bottomA = A.y + A.h;

            //Calculate the sides of rect B
            leftB = B.x;
            rightB = B.x + B.w;
            topB = B.y;
            bottomB = B.y + B.h;

            if (bottomA <= topB)
            {
                return false;
            }

            if (topA >= bottomB)
            {
                return false;
            }

            if (rightA <= leftB)
            {
                return false;
            }

            if (leftA >= rightB)
            {
                return false;
            }

            //If none of the sides from A are outside B
            return true;
		}
	};
}