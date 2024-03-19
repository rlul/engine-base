#pragma once

struct vec2_t
{
	vec2_t()
		: x(0.0f), y(0.0f)
	{}
	vec2_t(float x, float y)
		: x(x), y(y)
	{}

	vec2_t operator+(const vec2_t& other) const
	{
		return {x + other.x, y + other.y};
	}

	vec2_t operator-(const vec2_t& other) const
	{
		return {x - other.x, y - other.y};
	}

	vec2_t operator*(float scalar) const
	{
		return {x * scalar, y * scalar};
	}

	vec2_t operator/(float scalar) const
	{
		return { x / scalar, y / scalar };
	}

	vec2_t operator+=(const vec2_t& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	vec2_t operator-=(const vec2_t& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	vec2_t operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}

	vec2_t operator/=(float scalar)
	{
		x /= scalar;
		y /= scalar;
		return *this;
	}

	vec2_t operator-() const
	{
		return {-x, -y};
	}

	float x, y;
};

struct transform_t
{
	transform_t()
		: position(0.0f, 0.0f), scale(1.0f, 1.0f), rotation(0.0f)
	{}
	transform_t(const vec2_t& position, const vec2_t& scale, float rotation)
		: position(position), scale(scale), rotation(rotation)
	{}

	


	vec2_t position;
	vec2_t scale;
	float rotation;
};

