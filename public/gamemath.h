#pragma once

struct Vector2D_t
{
	Vector2D_t()
		: x(0.0f), y(0.0f)
	{}
	Vector2D_t(float x, float y)
		: x(x), y(y)
	{}
	Vector2D_t(int x, int y)
		: x(x), y(y)
	{}

	bool IsNull() const
	{
		return !x && !y;
	}

	Vector2D_t operator+(const Vector2D_t& other) const
	{
		return {x + other.x, y + other.y};
	}

	Vector2D_t operator-(const Vector2D_t& other) const
	{
		return {x - other.x, y - other.y};
	}

	Vector2D_t operator*(float scalar) const
	{
		return {x * scalar, y * scalar};
	}

	Vector2D_t operator/(float scalar) const
	{
		return { x / scalar, y / scalar };
	}

	Vector2D_t operator+=(const Vector2D_t& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	Vector2D_t operator-=(const Vector2D_t& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	Vector2D_t operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}

	Vector2D_t operator/=(float scalar)
	{
		x /= scalar;
		y /= scalar;
		return *this;
	}

	Vector2D_t operator-() const
	{
		return {-x, -y};
	}

	float x, y;
};
