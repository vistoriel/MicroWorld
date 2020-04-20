#pragma once
class Vector2
{
public:
	int x, y;

	Vector2();
	Vector2(int _x, int _y);

	friend const Vector2 operator+(const Vector2& left, const Vector2& right);

	friend bool operator==(const Vector2& left, const Vector2& right);
	friend bool operator!=(const Vector2& left, const Vector2& right);
};

