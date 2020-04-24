#pragma once
#include <vector>
#include "Vector2.h"
#include <stdio.h>
#include <time.h>
#include "Definitions.h"
#include <stdexcept>
#include <iostream> 
#include "Global.h"

class Entity
{
public:
	int id;
	unsigned char rotation;
	Vector2 position;
	int energy;
	unsigned char genome[GENOME_SIZE];
	bool isDead;
	std::vector<Entity> *List;
	std::vector<std::vector<int>> *Matrix;
	unsigned char genp;
	unsigned char genoffset;
	mColor color;

	Entity();
	Entity(int id_, char genome_[GENOME_SIZE], std::vector<Entity>& list, std::vector<std::vector<int>>& mat);
	Entity(int id_, char rotation_, Vector2 position_,int energy_, char genome_[GENOME_SIZE], std::vector<Entity>& list, std::vector<std::vector<int>>& mat);
	Entity(int id_, int rotation_, Vector2 position_, int energy_, char genome_[GENOME_SIZE], std::vector<Entity>& list, std::vector<std::vector<int>>& mat);

private:
	Vector2 rotToDir(char rot);
	ret_offset checkAt(Vector2 pos);
	ret_offset checkAt(Vector2 pos, Entity &observable);


public:
	char Rotate(char gen, char gp, bool isRel);
	char Look(char gen, char gp, bool isRel);
	char Move(char gen, char gp, bool isRel);
	char Photosynthesis(char gen, char gp);
	char Division(char gen, char gp);
	char Eat(char gen, char gp, bool isRel, int &curEnt);

};

