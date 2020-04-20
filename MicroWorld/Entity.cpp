#include "Entity.h"
#include <vector>

Entity::Entity()
{
}

Entity::Entity(char genome_[GENOME_SIZE], std::vector<Entity> &list)
{
	for (size_t i = 0; i < GENOME_SIZE; i++)
	{
		genome[i] = genome_[i];
	}

	List = &list;

	rotation = 0;
	position = Vector2(0, 0);
	energy = 10;
	isDead = false;

	genp = 0;
	genoffset = 0;
}

Entity::Entity(char rotation_, Vector2 position_, int energy_, char genome_[GENOME_SIZE], std::vector<Entity>& list)
{
	for (size_t i = 0; i < GENOME_SIZE; i++)
	{
		genome[i] = genome_[i];
	}

	List = &list;

	rotation = rotation_;
	position = position_;
	energy = energy_;
	isDead = false;
	genp = 0;
	genoffset = 1;
}

Entity::Entity(int rotation_, Vector2 position_, int energy_, char genome_[GENOME_SIZE], std::vector<Entity>& list)
{
	for (size_t i = 0; i < GENOME_SIZE; i++)
	{
		genome[i] = genome_[i];
	}

	List = &list;

	rotation = rotation_;
	position = position_;
	energy = energy_;
	isDead = false;
	genp = 0;
	genoffset = 1;
}


/*
*	BASIC BOTS COMMANDS
*/

// ROTATE ABSOLUTLY
char Entity::RotateAbs(char gen, char gp)
{
	char rot = genome[gp + 1];
	rotation = (rot + rotation) % 8;

	return 2;
}

// ROTATE RELATIVELY
char Entity::RotateRel(char gen, char gp)
{
	char rot = genome[gp + 1];
	rotation = (rot + rotation) % 8;

	return 2;
}

// LOOK ABSOLUTLY
char Entity::LookAbs(char gen, char gp)
{
	extern Vector2 rotToDir(char);

	char rot = genome[gp + 1];

	Vector2 direction = rotToDir(rot % 8);
	Vector2 lookAt = position + direction;

	Entity observable = Entity();
	bool isEmpty = true;
	for (int i = 0; i < List->size(); i++)
		if (List->at(i).position == lookAt) {
			observable = List->at(i);
			isEmpty = false;
			break;
		}

	char offset;
	bool isFriedly = false;
	char error = 0;

	if (isEmpty) offset = 2;
	else
	{
		if (observable.isDead) offset = 3;
		else
		{
			for (char i = 0; i < GENOME_SIZE; i++)
				if (genome[i] != observable.genome[i]) error++;
			if (error <= 2) offset = 4;
			else offset = 5;
		}
	}

	return genome[gp + offset];
}

// LOOK RELATIVELY
char Entity::LookRel(char gen, char gp)
{
	extern Vector2 rotToDir(char);

	char rot = genome[gp + 1];

	Vector2 direction = rotToDir((rot + rotation) % 8);
	Vector2 lookAt = position + direction;

	Entity observable = Entity();
	bool isEmpty = true;
	for (int i = 0; i < List->size(); i++)
		if (List->at(i).position == lookAt) {
			observable = List->at(i);
			isEmpty = false;
			break;
		}

	char offset;
	bool isFriedly = false;
	char error = 0;

	if (isEmpty) offset = 2;
	else
	{
		if (observable.isDead) offset = 3;
		else
		{
			for (char i = 0; i < GENOME_SIZE; i++)
				if (genome[i] != observable.genome[i]) error++;
			if (error <= 2) offset = 4;
			else offset = 5;
		}
	}

	return genome[gp + offset];
}

// MOVE ABSOLUTLY
char Entity::MoveAbs(char gen, char gp)
{
	extern Vector2 rotToDir(char);

	char rot = genome[gp + 1];
	Vector2 direction = rotToDir(rot % 8);
	Vector2 lookAt = position + direction;

	bool isThatWall = false;
	if (0 > lookAt.x || lookAt.x >= SCREEN_WIDTH / SIZE || 0 > lookAt.y || lookAt.y >= SCREEN_HEIGHT / SIZE)
	{
		isThatWall = true;
	}

	Entity observable = Entity();
	bool isEmpty = true;
	for (int i = 0; i < List->size(); i++)
		if (List->at(i).position == lookAt)
		{
			observable = List->at(i);
			isEmpty = false;
			break;
		}

	char offset;
	bool isFriedly = false;
	char error = 0;

	if (isThatWall)
	{
		offset = 2;
	}
	else if (isEmpty)
	{
		offset = 3;
		position = position + direction;
	}
	else
	{
		if (observable.isDead) offset = 4;
		else
		{
			for (char i = 0; i < GENOME_SIZE; i++)
				if (genome[i] != observable.genome[i]) error++;
			if (error <= 2) offset = 5;
			else offset = 6;
		}
	}

	return genome[gp + offset];
}

// MOVE RELATIVELY
char Entity::MoveRel(char gen, char gp)
{
	extern Vector2 rotToDir(char);

	char rot = genome[gp + 1];
	Vector2 direction = rotToDir((rot + rotation) % 8);
	Vector2 lookAt = position + direction;

	bool isThatWall = false;
	if (0 > lookAt.x || lookAt.x >= SCREEN_WIDTH / SIZE || 0 > lookAt.y || lookAt.y >= SCREEN_HEIGHT / SIZE)
	{
		isThatWall = true;
	}

	Entity observable = Entity();
	bool isEmpty = true;
	for (int i = 0; i < List->size(); i++)
		if (List->at(i).position == lookAt)
		{
			observable = List->at(i);
			isEmpty = false;
			break;
		}

	char offset;
	bool isFriedly = false;
	char error = 0;

	if (isThatWall)
	{
		offset = 2;
	}
	else if (isEmpty)
	{
		offset = 3;
		position = position + direction;
	}
	else
	{
		if (observable.isDead) offset = 4;
		else
		{
			for (char i = 0; i < GENOME_SIZE; i++)
				if (genome[i] != observable.genome[i]) error++;
			if (error <= 2) offset = 5;
			else offset = 6;
		}
	}

	return genome[gp + offset];
}

// PHOTOSYNTHESIS
char Entity::Photosynthesis(char gen, char gp)
{
	energy += LIGHT_FORCE;
	return 1;
}

// DIVISION
char Entity::Division(char gen, char gp)
{
	extern Vector2 rotToDir(char);
	srand(time(0));

	char chance = 0 + rand() % 4;
	char newGenome[GENOME_SIZE];

	for (char i = 0; i < GENOME_SIZE; i++)
		newGenome[i] = genome[i];

	if (chance == 0)
		newGenome[0 + rand() % GENOME_SIZE] = MIN_GEN + rand() % MAX_GEN;

	Vector2 lookAt;
	bool isEmpty;

	for (int i = 0; i < 8; i++)
	{
		isEmpty = true;
		Vector2 direction = rotToDir((rotation + 4 + i) % 8);
		lookAt = position + direction;

		if (0 > lookAt.x || lookAt.x >= SCREEN_WIDTH / SIZE || 0 > lookAt.y || lookAt.y >= SCREEN_HEIGHT / SIZE)
			isEmpty = false;
		else
			for (int j = 0; j < List->size(); j++)
				if (List->at(j).position == lookAt)
				{
					isEmpty = false;
					break;
				}

		if (isEmpty)
			break;
	}

	if (isEmpty)
	{
		energy /= 2;
		Entity ent = Entity(0 + rand() % 8, lookAt, energy, newGenome, *List);
		List->push_back(ent);
		return 1;
	}
	else
		return 2;
}

// EAT ABSOLUTLY
char Entity::EatAbs(char gen, char gp)
{
	extern Vector2 rotToDir(char);

	char rot = genome[gp + 1];

	Vector2 direction = rotToDir(rot % 8);
	Vector2 lookAt = position + direction;

	bool isEmpty = true;
	bool isThatWall = false;

	if (0 > lookAt.x || lookAt.x >= SCREEN_WIDTH / SIZE || 0 > lookAt.y || lookAt.y >= SCREEN_HEIGHT / SIZE)
		isThatWall = true;

	Entity *observable = new Entity();
	int observableID = 0;
	for (int i = 0; i < List->size(); i++)
	{
		if (isThatWall) break;

		if (List->at(i).position == lookAt)
		{
			observable = &List->at(i);
			observableID = i;
			isEmpty = false;
			break;
		}
	}

	char offset;
	bool isFriedly = false;
	char error = 0;

	if (isThatWall)
	{
		offset = 2;
	}
	else if (isEmpty) offset = 3;
	else
	{
		if (observable->isDead)
		{
			energy += 100;

			List->erase(List->begin() + observableID);

			offset = 4;
		}
		else
		{
			energy += (observable->energy / 4) + 100;

			for (char i = 0; i < GENOME_SIZE; i++)
				if (genome[i] != observable->genome[i]) error++;

			if (error <= 2) offset = 5;
			else offset = 6;

			List->erase(List->begin() + observableID);
		}
	}

	return genome[gp + offset];
}
