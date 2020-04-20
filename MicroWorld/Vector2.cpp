#include "Vector2.h"

Vector2::Vector2() {
	x = 0;
	y = 0;
}
Vector2::Vector2(int _x, int _y)
{
	x = _x;
	y = _y;
}

const Vector2 operator+(const Vector2& left, const Vector2& right) {
	return Vector2(left.x + right.x, left.y + right.y);
}

bool operator==(const Vector2& left, const Vector2& right) {
	return left.x == right.x && left.y == right.y;
}

bool operator!=(const Vector2& left, const Vector2& right) {
	return left.x != right.x && left.y != right.y;
}