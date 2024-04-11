#pragma once
#include <cmath>

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
	Vector2D_t(unsigned x, unsigned y)
		: x(x), y(y)
	{}

	bool IsNull() const
	{
		return !x && !y;
	}

	Vector2D_t Normalize() const
	{
		float length = sqrt(x * x + y * y);
		return {x / length, y / length};
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

struct Vector3D_t
{
	Vector3D_t()
		: x(0.0f), y(0.0f), z(0.0f)
	{}
	Vector3D_t(float x, float y, float z)
		: x(x), y(y), z(z)
	{}
	Vector3D_t(int x, int y, int z)
		: x(x), y(y), z(z)
	{}

	Vector3D_t Normalize() const
	{
		float length = sqrtf(x * x + y * y + z * z);
		return {x / length, y / length, z / length};
	}

	bool IsNull() const
	{
		return !x && !y && !z;
	}

	bool operator==(const Vector3D_t& other) const
	{
		return x == other.x && y == other.y && z == other.z;
	}

	Vector3D_t operator+(const Vector3D_t& other) const
	{
		return {x + other.x, y + other.y, z + other.z};
	}

	Vector3D_t operator-(const Vector3D_t& other) const
	{
		return {x - other.x, y - other.y, z - other.z};
	}

	Vector3D_t operator*(float scalar) const
	{
		return {x * scalar, y * scalar, z * scalar};
	}

	Vector3D_t operator/(float scalar) const
	{
		return { x / scalar, y / scalar, z / scalar };
	}

	Vector3D_t operator+=(const Vector3D_t& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	Vector3D_t operator-=(const Vector3D_t& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	Vector3D_t operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}

	Vector3D_t operator/=(float scalar)
	{
		x /= scalar;
		y /= scalar;
		z /= scalar;
		return *this;
	}

	Vector3D_t operator-() const
	{
		return {-x, -y, -z};
	}

	float x, y, z;
};

struct Vector4D_t
{
	Vector4D_t()
		: x(0.0f), y(0.0f), z(0.0f), w(0.0f)
	{}
	Vector4D_t(float x, float y, float z, float w)
		: x(x), y(y), z(z), w(w)
	{}
	Vector4D_t(int x, int y, int z, int w)
		: x(x), y(y), z(z), w(w)
	{}

	bool IsNull() const
	{
		return !x && !y && !z && !w;
	}

	Vector4D_t operator+(const Vector4D_t& other) const
	{
		return {x + other.x, y + other.y, z + other.z, w + other.w};
	}

	Vector4D_t operator-(const Vector4D_t& other) const
	{
		return {x - other.x, y - other.y, z - other.z, w - other.w};
	}

	Vector4D_t operator*(float scalar) const
	{
		return {x * scalar, y * scalar, z * scalar, w * scalar};
	}

	Vector4D_t operator/(float scalar) const
	{
		return { x / scalar, y / scalar, z / scalar, w / scalar };
	}

	Vector4D_t operator+=(const Vector4D_t& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
		return *this;
	}

	Vector4D_t operator-=(const Vector4D_t& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;
		return *this;
	}

	Vector4D_t operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		w *= scalar;
		return *this;
	}

	Vector4D_t operator/=(float scalar)
	{
		x /= scalar;
		y /= scalar;
		z /= scalar;
		w /= scalar;
		return *this;
	}

	Vector4D_t operator-() const
	{
		return {-x, -y, -z, -w};
	}

	float x, y, z, w;
};

struct Matrix3x3_t
{
	Matrix3x3_t()
	{
		for (auto& i : m)
			for (float& j : i)
				j = 0.0f;
	}
	Matrix3x3_t(float m00, float m01, float m02,
				float m10, float m11, float m12,
				float m20, float m21, float m22)
	{
		m[0][0] = m00; m[0][1] = m01; m[0][2] = m02;
		m[1][0] = m10; m[1][1] = m11; m[1][2] = m12;
		m[2][0] = m20; m[2][1] = m21; m[2][2] = m22;
	}

	bool operator==(const Matrix3x3_t& other) const
	{
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				if (m[i][j] != other.m[i][j])
					return false;
		return true;
	}

	Matrix3x3_t operator*(const Matrix3x3_t& other) const
	{
		Matrix3x3_t result;
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				result.m[i][j] = m[i][0] * other.m[0][j] + m[i][1] * other.m[1][j] + m[i][2] * other.m[2][j];
		return result;
	}

	Vector3D_t operator*(const Vector3D_t& vector) const
	{
		return {
			m[0][0] * vector.x + m[0][1] * vector.y + m[0][2] * vector.z,
			m[1][0] * vector.x + m[1][1] * vector.y + m[1][2] * vector.z,
			m[2][0] * vector.x + m[2][1] * vector.y + m[2][2] * vector.z
		};
	}

	Matrix3x3_t operator+(const Matrix3x3_t& other) const
	{
		Matrix3x3_t result;
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				result.m[i][j] = m[i][j] + other.m[i][j];
		return result;
	}

	Matrix3x3_t operator-(const Matrix3x3_t& other) const
	{
		Matrix3x3_t result;
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				result.m[i][j] = m[i][j] - other.m[i][j];
		return result;
	}

	Matrix3x3_t operator*(float scalar) const
	{
				Matrix3x3_t result;
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				result.m[i][j] = m[i][j] * scalar;
		return result;
	}

	Matrix3x3_t operator/(float scalar) const
	{
				Matrix3x3_t result;
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				result.m[i][j] = m[i][j] / scalar;
		return result;
	}

	Matrix3x3_t operator+=(const Matrix3x3_t& other)
	{
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				m[i][j] += other.m[i][j];
		return *this;
	}

	Matrix3x3_t operator-=(const Matrix3x3_t& other)
	{
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				m[i][j] -= other.m[i][j];
		return *this;
	}

	Matrix3x3_t operator*=(float scalar)
	{
		for (auto& i : m)
			for (float& j : i)
				j *= scalar;
		return *this;
	}

	Matrix3x3_t operator/=(float scalar)
	{
		for (auto& i : m)
			for (float& j : i)
				j /= scalar;
		return *this;
	}

	Matrix3x3_t operator-() const
	{
		Matrix3x3_t result;
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				result.m[i][j] = -m[i][j];
		return result;
	}

	Matrix3x3_t Inverse() const
	{
		Matrix3x3_t result;
		float det = m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) -
					m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) +
					m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
		if (det == 0.0f)
			return result;
		float invDet = 1.0f / det;
		result.m[0][0] = (m[1][1] * m[2][2] - m[1][2] * m[2][1]) * invDet;
		result.m[0][1] = (m[0][2] * m[2][1] - m[0][1] * m[2][2]) * invDet;
		result.m[0][2] = (m[0][1] * m[1][2] - m[0][2] * m[1][1]) * invDet;
		result.m[1][0] = (m[1][2] * m[2][0] - m[1][0] * m[2][2]) * invDet;
		result.m[1][1] = (m[0][0] * m[2][2] - m[0][2] * m[2][0]) * invDet;
		result.m[1][2] = (m[1][0] * m[0][2] - m[0][0] * m[1][2]) * invDet;
		result.m[2][0] = (m[1][0] * m[2][1] - m[2][0] * m[1][1]) * invDet;
		result.m[2][1] = (m[2][0] * m[0][1] - m[0][0] * m[2][1]) * invDet;
		result.m[2][2] = (m[0][0] * m[1][1] - m[1][0] * m[0][1]) * invDet;
		return result;
	}

	Matrix3x3_t Transpose() const
	{
		Matrix3x3_t result;
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				result.m[i][j] = m[j][i];
		return result;
	}

	static Matrix3x3_t Identity()
	{
		return {
			1.0f,	0.0f,	0.0f,
			0.0f,	1.0f,	0.0f,
			0.0f,	0.0f,	1.0f
		};
	}

	static Matrix3x3_t Translate(Vector2D_t const& translation)
	{
		return {
			1.0f,	0.0f,	translation.x,
			0.0f,	1.0f,	translation.y,
			0.0f,	0.0f,	1.0f
		};
	}

	static Matrix3x3_t Scale(Vector2D_t const& scale)
	{
		return {
			scale.x,	0.0f,		0.0f,
			0.0f,		scale.y,	0.0f,
			0.0f,		0.0f,		1.0f
		};
	}

	static Matrix3x3_t Rotate(float angle)
	{
		angle *= 3.1415f / 180.0f;
		float c = cosf(angle);
		float s = sinf(angle);
		return {
			c,		-s,		0.0f,
			s,		c,		0.0f,
			0.0f,	0.0f,	1.0f
		};
	}

	float m[3][3];
};

struct Matrix4x4_t
{
	Matrix4x4_t()
	{
		for (auto& i : m)
			for (float& j : i)
				j = 0.0f;
	}
	Matrix4x4_t(float m00, float m01, float m02, float m03,
				float m10, float m11, float m12, float m13,
				float m20, float m21, float m22, float m23,
				float m30, float m31, float m32, float m33)
	{
		m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
		m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
		m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
		m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
	}

    Matrix4x4_t operator*(const Matrix4x4_t& other) const
	{
		Matrix4x4_t result;
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				result.m[i][j] = m[i][0] * other.m[0][j] + m[i][1] * other.m[1][j] + m[i][2] * other.m[2][j] + m[i][3] * other.m[3][j];
		return result;
	}

	Vector4D_t operator*(const Vector4D_t& vector) const
	{
		return {
			m[0][0] * vector.x + m[0][1] * vector.y + m[0][2] * vector.z + m[0][3] * vector.w,
			m[1][0] * vector.x + m[1][1] * vector.y + m[1][2] * vector.z + m[1][3] * vector.w,
			m[2][0] * vector.x + m[2][1] * vector.y + m[2][2] * vector.z + m[2][3] * vector.w,
			m[3][0] * vector.x + m[3][1] * vector.y + m[3][2] * vector.z + m[3][3] * vector.w
		};
	}

	Matrix4x4_t operator+(const Matrix4x4_t& other) const
	{
		Matrix4x4_t result;
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				result.m[i][j] = m[i][j] + other.m[i][j];
		return result;
	}

	Matrix4x4_t operator-(const Matrix4x4_t& other) const
	{
		Matrix4x4_t result;
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				result.m[i][j] = m[i][j] - other.m[i][j];
		return result;
	}

	Matrix4x4_t operator*(float scalar) const
	{
		Matrix4x4_t result;
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				result.m[i][j] = m[i][j] * scalar;
		return result;
	}

	Matrix4x4_t operator/(float scalar) const
	{
		Matrix4x4_t result;
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				result.m[i][j] = m[i][j] / scalar;
		return result;
	}

	Matrix4x4_t operator+=(const Matrix4x4_t& other)
	{
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				m[i][j] += other.m[i][j];
		return *this;
	}

    Matrix4x4_t operator-=(const Matrix4x4_t& other)
	{
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				m[i][j] -= other.m[i][j];
		return *this;
	}

	Matrix4x4_t operator*=(float scalar)
	{
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				m[i][j] *= scalar;
		return *this;
	}

	Matrix4x4_t operator/=(float scalar)
	{
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				m[i][j] /= scalar;
		return *this;
	}

	Matrix4x4_t operator-() const
	{
		Matrix4x4_t result;
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				result.m[i][j] = -m[i][j];
		return result;
	}

	static Matrix4x4_t Identity()
	{
		return {
			1.0f,	0.0f,	0.0f,	0.0f,
			0.0f,	1.0f,	0.0f,	0.0f,
			0.0f,	0.0f,	1.0f,	0.0f,
			0.0f,	0.0f,	0.0f,	1.0f
		};
	}

	static Matrix4x4_t Translate(Vector3D_t const& translation)
	{
		return {
			1.0f,	0.0f,	0.0f,	translation.x,
			0.0f,	1.0f,	0.0f,	translation.y,
			0.0f,	0.0f,	1.0f,	translation.z,
			0.0f,	0.0f,	0.0f,	1.0f
		};
	}

	static Matrix4x4_t Scale(Vector3D_t const& scale)
	{
		return {
			scale.x,	0.0f,		0.0f,		0.0f,
			0.0f,		scale.y,	0.0f,		0.0f,
			0.0f,		0.0f,		scale.z,	0.0f,
			0.0f,		0.0f,		0.0f,		1.0f
		};
	}

	static Matrix4x4_t RotateX(float angle)
	{
		angle *= 3.1415f / 180.0f;
		float c = cosf(angle);
		float s = sinf(angle);
		return {
			1.0f,	0.0f,	0.0f,	0.0f,
			0.0f,	c,		-s,		0.0f,
			0.0f,	s,		c,		0.0f,
			0.0f,	0.0f,	0.0f,	1.0f
		};
	}

	static Matrix4x4_t RotateY(float angle)
	{
		angle *= 3.1415f / 180.0f;
		float c = cosf(angle);
		float s = sinf(angle);
		return {
			c,		0.0f,	s,		0.0f,
			0.0f,	1.0f,	0.0f,	0.0f,
			-s,		0.0f,	c,		0.0f,
			0.0f,	0.0f,	0.0f,	1.0f
		};
	}

	static Matrix4x4_t RotateZ(float angle)
	{
		angle *= 3.1415f / 180.0f;
		float c = cosf(angle);
		float s = sinf(angle);
		return {
			c,		-s,		0.0f,	0.0f,
			s,		c,		0.0f,	0.0f,
			0.0f,	0.0f,	1.0f,	0.0f,
			0.0f,	0.0f,	0.0f,	1.0f
		};
	}

	float m[4][4];
};
