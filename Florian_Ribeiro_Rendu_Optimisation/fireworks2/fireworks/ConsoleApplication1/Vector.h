#pragma once
struct Vector
{
	float x;
	float y;

	Vector()
	{
		x = 0;
		y = 0;
	}

	Vector(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	Vector(const Vector& vector) {
		x = vector.x;
		y = vector.y;
	}

	Vector& operator=(const Vector& vector) {
		this->x = vector.x;
		this->y = vector.y;
		return *this;
	}

	void Set(float x, float y) {
		this->x = x;
		this->y = y;
	}
};

