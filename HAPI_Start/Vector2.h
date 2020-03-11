#pragma once
#include <cmath>

class Vector2
{

public:

	float x{ 0 };
	float y{ 0 };

	//Constructors
	Vector2() = default;
	Vector2(float newX, float newY) : x(newX), y(newY) {}

	// + Operator
	Vector2 operator + (const Vector2& rhs) const
	{
		return Vector2(x + rhs.x, y + rhs.y);
	}

	// - Operator
	Vector2 operator - (const Vector2& rhs) const
	{
		return Vector2(x - rhs.x, y - rhs.y);
	}

	// * Operator
	Vector2 operator * (float rhs) const
	{
		return Vector2(x * rhs, y * rhs);
	}

};

