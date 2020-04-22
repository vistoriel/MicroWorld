#include "Entity.h"
#include <vector>

Entity::Entity()
{
}

Entity::Entity(int id_, char genome_[GENOME_SIZE], std::vector<Entity> &list, std::vector<std::vector<int>>& mat)
{
	id = id_;

	for (size_t i = 0; i < GENOME_SIZE; i++)
	{
		genome[i] = genome_[i];
	}

	List = &list;
	Matrix = &mat;
	rotation = 0;
	position = Vector2(0, 0);
	energy = 10;
	isDead = false;

	genp = 0;
	genoffset = 0;
}

Entity::Entity(int id_, char rotation_, Vector2 position_, int energy_, char genome_[GENOME_SIZE], std::vector<Entity>& list, std::vector<std::vector<int>>& mat)
{
	id = id_;

	for (size_t i = 0; i < GENOME_SIZE; i++)
	{
		genome[i] = genome_[i];
	}

	List = &list;
	Matrix = &mat;

	rotation = rotation_;
	position = position_;
	energy = energy_;
	isDead = false;
	genp = 0;
	genoffset = 1;
}

Entity::Entity(int id_, int rotation_, Vector2 position_, int energy_, char genome_[GENOME_SIZE], std::vector<Entity>& list, std::vector<std::vector<int>>& mat)
{
	id = id_;

	for (size_t i = 0; i < GENOME_SIZE; i++)
	{
		genome[i] = genome_[i];
	}

	List = &list;
	Matrix = &mat;

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

// LOOK ABSOLUTLY
char Entity::LookAbs(char gen, char gp)
{
	extern Vector2 rotToDir(char);

	char rot = genome[gp + 1];

	Vector2 direction = rotToDir(rot % 8);
	Vector2 lookAt = position + direction;

	bool isThatWall = false;

	Entity observable = Entity();
	bool isEmpty = true;

	if (0 > lookAt.x || lookAt.x >= SCREEN_WIDTH / SIZE || 0 > lookAt.y || lookAt.y >= SCREEN_HEIGHT / SIZE)
		isThatWall = true;
	else if (Matrix->at(lookAt.x).at(lookAt.y) >= 0)
	{
		observable = List->at(Matrix->at(lookAt.x).at(lookAt.y));
		isEmpty = false;
	}

	ret_offset offset;
	bool isFriedly = false;
	char error = 0;

	if (isThatWall)
	{
		offset = 2;
	}
	else if (isEmpty) offset = 3;
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

// MOVE ABSOLUTLY
char Entity::MoveAbs(char gen, char gp)
{
	extern Vector2 rotToDir(char);

	char rot = genome[gp + 1];
	Vector2 direction = rotToDir(rot % 8);
	Vector2 lookAt = position + direction;

	bool isThatWall = false;

	Entity observable = Entity();
	bool isEmpty = true;

	try
	{
		if (0 > lookAt.x || lookAt.x >= SCREEN_WIDTH / SIZE || 0 > lookAt.y || lookAt.y >= SCREEN_HEIGHT / SIZE)
			isThatWall = true;
		else if (Matrix->at(lookAt.x).at(lookAt.y) >= 0) //!
		{
			if (Matrix->at(lookAt.x).at(lookAt.y) >= List->size())
			{
				std::cout << Matrix->at(lookAt.x).at(lookAt.y) << " / " << List->size() << std::endl;
				//int f;
				//std::cin >> f;
			}
			else
			observable = List->at(Matrix->at(lookAt.x).at(lookAt.y)); //!
			isEmpty = false;
		}
	}
	catch (std::out_of_range)
	{
		std::cout << "OUT OF RANGE: QQQQ" << std::endl << std::endl;

		std::cout << lookAt.x << " " << lookAt.y << std::endl;

		std::cout << Matrix->at(lookAt.x).at(lookAt.y) << " / " << List->size() << std::endl;

		char f;
		std::cin >> f;
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
		try
		{
			offset = 3;
			Matrix->at(position.x).at(position.y) = -1; //!
			position = position + direction;
			Matrix->at(position.x).at(position.y) = id; //!
		}
		catch (std::out_of_range)
		{
			std::cout << "OUT OF RANGE: IS EMPTY" << std::endl << std::endl;

			std::cout << position.x << " " << position.y << std::endl;

			char f;
			std::cin >> f;
		}
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
		else if (Matrix->at(lookAt.x).at(lookAt.y) >= 0)
		{
			isEmpty = false;
		}

		if (isEmpty)
			break;
	}

	if (isEmpty)
	{
		energy /= 2;
		Entity ent = Entity(List->size(), 0 + rand() % 8, lookAt, energy, newGenome, *List, *Matrix);
		Matrix->at(lookAt.x).at(lookAt.y) = List->size();
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

	Entity* observable = new Entity();
	int observableID = 0;

	try
	{
		if (0 > lookAt.x || lookAt.x >= SCREEN_WIDTH / SIZE || 0 > lookAt.y || lookAt.y >= SCREEN_HEIGHT / SIZE)
			isThatWall = true;
		else if (Matrix->at(lookAt.x).at(lookAt.y) >= 0)
		{
			observable = &List->at(Matrix->at(lookAt.x).at(lookAt.y));
			isEmpty = false;
			observableID = observable->id;
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
				energy += ORGANIC_ENERGY;

				Matrix->at(observable->position.x).at(observable->position.y) = -1;
				List->erase(List->begin() + observableID);

				offset = 4;
			}
			else
			{
				energy += (observable->energy / 4) + ORGANIC_ENERGY;

				for (char i = 0; i < GENOME_SIZE; i++)
					if (genome[i] != observable->genome[i]) error++;

				if (error <= 2) offset = 5;
				else offset = 6;

				Matrix->at(observable->position.x).at(observable->position.y) = -1;
				List->erase(List->begin() + observableID);
			}
		}

		for (int i = observableID; i < List->size(); i++)
		{
			List->at(i).id = i;
			Matrix->at(List->at(i).position.x).at(List->at(i).position.y) = i;
		}

		return genome[gp + offset];

	}
	catch (std::out_of_range)
	{
		std::cout << "OUT OF RANGE: EAT" << std::endl;

		for (int i = 0; i < Matrix->size(); i++)
		{
			for (int j = 0; j < Matrix->at(i).size(); j++)
			{
				std::cout << Matrix->at(i).at(j) << " ";
			}
			std::cout << std::endl;
		}

		char f;
		std::cin >> f;
	}
}
