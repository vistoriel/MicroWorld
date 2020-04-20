#pragma once
#include <vector>
#include "Vector2.h"
#include <stdio.h>
#include <time.h>
#include "Definitions.h"

class Entity
{
public:
	char rotation;
	Vector2 position;
	int energy;
	char genome[GENOME_SIZE];
	bool isDead;
	std::vector<Entity> *List;
	char genp;
	char genoffset;

	Entity();
	Entity(char genome_[GENOME_SIZE], std::vector<Entity> &list);
	Entity(char rotation_, Vector2 position_,int energy_, char genome_[GENOME_SIZE], std::vector<Entity>& list);
	Entity(int rotation_, Vector2 position_, int energy_, char genome_[GENOME_SIZE], std::vector<Entity>& list);

	char RotateAbs(char gen, char gp);
	char RotateRel(char gen, char gp);
	char LookAbs(char gen, char gp);
	char LookRel(char gen, char gp);
	char MoveAbs(char gen, char gp);
	char MoveRel(char gen, char gp);
	char Photosynthesis(char gen, char gp);
	char Division(char gen, char gp);
	char EatAbs(char gen, char gp);
};

