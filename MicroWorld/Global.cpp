#pragma once
#include "Vector2.h";

Vector2 rotToDir(char rot)
{
	Vector2 dir;

	switch (rot) {
	case 0:
		dir = Vector2(0, 1);
		break;
	case 1:
		dir = Vector2(1, 1);
		break;
	case 2:
		dir = Vector2(1, 0);
		break;
	case 3:
		dir = Vector2(1, -1);
		break;
	case 4:
		dir = Vector2(0, -1);
		break;
	case 5:
		dir = Vector2(-1, -1);
		break;
	case 6:
		dir = Vector2(-1, 0);
		break;
	case 7:
		dir = Vector2(-1, 1);
		break;
	default:
		break;
	}

	return dir;
}