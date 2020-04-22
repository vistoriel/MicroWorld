#pragma once
#include <vector>
#include "Vector2.h"
#include <stdio.h>
#include <time.h>
#include "Definitions.h"
#include <stdexcept>
#include <iostream> 

class Entity
{
public:
	int id;
	char rotation;
	Vector2 position;
	int energy;
	char genome[GENOME_SIZE];
	bool isDead;
	std::vector<Entity> *List;
	std::vector<std::vector<int>> *Matrix;
	char genp;
	char genoffset;

	Entity();
	Entity(int id_, char genome_[GENOME_SIZE], std::vector<Entity>& list, std::vector<std::vector<int>>& mat);
	Entity(int id_, char rotation_, Vector2 position_,int energy_, char genome_[GENOME_SIZE], std::vector<Entity>& list, std::vector<std::vector<int>>& mat);
	Entity(int id_, int rotation_, Vector2 position_, int energy_, char genome_[GENOME_SIZE], std::vector<Entity>& list, std::vector<std::vector<int>>& mat);

	char RotateAbs(char gen, char gp);
	char LookAbs(char gen, char gp);
	char MoveAbs(char gen, char gp);
	char Photosynthesis(char gen, char gp);
	char Division(char gen, char gp);
	char EatAbs(char gen, char gp);
};

