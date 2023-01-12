#pragma once
#include <math.h>

class GameStruct
{
public:
	struct point
	{
		point(int x, int y)
			: X{ x }
			, Y{ y }
		{

		}

		int distance(GameStruct::point other) const
		{
			return sqrt(pow(other.X - X, 2) + pow(other.Y - Y, 2) * 1.0);
		}

		int X{};
		int Y{};

	};
	

	struct Box
	{
		Box(int x, int y, int width, int height)
			: X{ x }
			, Y{ y }
			, Width{ width }
			, Height{ height }

		{

		}

		int X{};
		int Y{};
		int Width{};
		int Height{};

		GameStruct::point GetCenter() const
		{
			return GameStruct::point{X + Width / 2, Y + Height / 2 };
		}
	};


	struct vector2
	{
		vector2(float x = 0.f, float y = 0.f)
			: X{ x }
			, Y{ y }
		{

		}

		float X{};
		float Y{};

		vector2 operator*=(float v)
		{
			X *= v;
			Y *= v;

			return vector2{ X, Y };
		}		

		float SquaredLength()
		{
			return (X * X) + (Y * Y);
		}

		float Length()
		{
			return sqrtf(SquaredLength());
		}

		vector2 normalize()
		{
			float lenght{ Length() };

			if (lenght == 0)
			{
				return vector2{ 0, 0 };
			}

			X /= lenght;
			Y /= lenght;

			return vector2{ X, Y };
		}

	};
};

