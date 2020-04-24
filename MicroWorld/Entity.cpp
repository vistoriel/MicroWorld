#include "Entity.h"

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

	color.red = 255;
	color.green = 255;
	color.blue = 255;

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

	color.red = 255;
	color.green = 255;
	color.blue = 255;

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

	color.red = 255;
	color.green = 255;
	color.blue = 255;

	rotation = rotation_;
	position = position_;
	energy = energy_;
	isDead = false;
	genp = 0;
	genoffset = 1;
}


Vector2 Entity::rotToDir(char rot)
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

ret_offset Entity::checkAt(Vector2 pos)
{
	Entity observable = Entity();
	ret_offset offset;

	try
	{
		if (0 > pos.x || pos.x >= SCREEN_WIDTH / SIZE || 0 > pos.y || pos.y >= SCREEN_HEIGHT / SIZE) offset = WALL_OFFSET;
		else
		{
			if (Matrix->at(pos.x).at(pos.y) >= 0)
			{
				observable = List->at(Matrix->at(pos.x).at(pos.y));

				if (observable.isDead) offset = DEAD_OFFSET;
				else
				{
					char error = 0;

					for (char i = 0; i < GENOME_SIZE; i++)
						if (genome[i] != observable.genome[i]) error++;

					if (error <= RELATIVES_GENES) offset = FRIEND_OFFSET;
					else offset = ENEMY_OFFSET;
				}
			}
			else offset = EMPTY_OFFSET;
		}

		return offset;
	}
	catch (std::out_of_range)
	{
		std::cout << "OUT OF RANGE: checkAt" << std::endl << std::endl;
		std::cout << pos.x << " " << pos.y << std::endl;
		std::cout << Matrix->at(pos.x).at(pos.y) << " / " << List->size() << std::endl;

		char f;
		std::cin >> f;
	}
}

ret_offset Entity::checkAt(Vector2 pos, Entity &observable)
{
	ret_offset offset;

	try
	{
		if (0 > pos.x || pos.x >= SCREEN_WIDTH / SIZE || 0 > pos.y || pos.y >= SCREEN_HEIGHT / SIZE) offset = WALL_OFFSET;
		else
		{
			if (Matrix->at(pos.x).at(pos.y) >= 0)
			{
				observable = List->at(Matrix->at(pos.x).at(pos.y));

				if (observable.isDead) offset = DEAD_OFFSET;
				else
				{
					char error = 0;

					for (char i = 0; i < GENOME_SIZE; i++)
						if (genome[i] != observable.genome[i]) error++;

					if (error <= RELATIVES_GENES) offset = FRIEND_OFFSET;
					else offset = ENEMY_OFFSET;
				}
			}
			else offset = EMPTY_OFFSET;
		}

		return offset;
	}
	catch (std::out_of_range)
	{
		std::cout << "OUT OF RANGE: checkAt" << std::endl << std::endl;
		std::cout << pos.x << " " << pos.y << std::endl;
		std::cout << Matrix->at(pos.x).at(pos.y) << " / " << List->size() << std::endl;

		char f;
		std::cin >> f;
	}
}



/*
*	BASIC BOTS COMMANDS
*/

// ROTATE
char Entity::Rotate(char gen, char gp, bool isRel)
{
	char rot = genome[gp + 1];
	rotation = (rot + (isRel ? rotation : 0)) % 8;

	return 2;
}

// LOOK
char Entity::Look(char gen, char gp, bool isRel)
{
	char rot = genome[gp + 1];
	Vector2 direction = rotToDir((rot + (isRel ? rotation : 0)) % 8);
	Vector2 lookAt = position + direction;

	ret_offset offset = checkAt(lookAt);

	return genome[(gp + offset) % GENOME_SIZE];
}

// MOVE
char Entity::Move(char gen, char gp, bool isRel)
{
	char rot = genome[gp + 1];
	Vector2 direction = rotToDir((rot + (isRel ? rotation : 0)) % 8);
	Vector2 lookAt = position + direction;

	ret_offset offset = checkAt(lookAt);

	switch (offset)
	{
	case EMPTY_OFFSET:
		Matrix->at(position.x).at(position.y) = -1; //!
		position = position + direction;
		Matrix->at(position.x).at(position.y) = id; //!
		break;
	case WALL_OFFSET:
		break;
	case DEAD_OFFSET:
		break;
	case FRIEND_OFFSET:
		break;
	case ENEMY_OFFSET:
		break;
	default:
		break;
	}

	return genome[(gp + offset) % GENOME_SIZE];
}

// PHOTOSYNTHESIS
char Entity::Photosynthesis(char gen, char gp)
{
	energy += LIGHT_ENERGY;

	if (this->color.red < 255 || this->color.red) this->color.red--;
	if (this->color.green < 255 || this->color.green) this->color.green++;
	if (this->color.blue < 255 || this->color.blue) this->color.blue--;

	return 1;
}

// DIVISION
char Entity::Division(char gen, char gp)
{
	srand(time(0));

	char chance = 0 + rand() % 4;
	char newGenome[GENOME_SIZE];

	for (char i = 0; i < GENOME_SIZE; i++)
		newGenome[i] = genome[i];

	if (chance == 0)
		newGenome[0 + rand() % GENOME_SIZE] = MIN_GEN + rand() % MAX_GEN;

	Vector2 lookAt;
	ret_offset offset;

	for (int i = 0; i < 8; i++)
	{
		Vector2 direction = rotToDir((rotation + 4 + i) % 8);
		lookAt = position + direction;
		offset = checkAt(lookAt);
		
		if (offset == EMPTY_OFFSET) break;
	}

	if (offset == EMPTY_OFFSET)
	{
		energy /= 2;
		Entity ent = Entity(List->size(), 0 + rand() % 8, lookAt, energy, newGenome, *List, *Matrix);
		Matrix->at(lookAt.x).at(lookAt.y) = List->size();
		List->push_back(ent);

		return 1;
	}
	else this->isDead = true;
	return 1;
}

// EAT
char Entity::Eat(char gen, char gp, bool isRel, int &curEnt)
{
	//std::cout << "Eat";

	char rot = genome[gp + 1];

	Vector2 direction = rotToDir((rot + (isRel ? rotation : 0)) % 8);
	Vector2 lookAt = position + direction;
	Entity* observable = new Entity();

	ret_offset offset = checkAt(lookAt);

	int observableID = observable->id;

	switch (offset)
	{
	case EMPTY_OFFSET:
		break;
	case WALL_OFFSET:
		break;
	case DEAD_OFFSET:
		energy += ORGANIC_ENERGY;

		Matrix->at(observable->position.x).at(observable->position.y) = -1;
		List->erase(List->begin() + observableID);

		if (this->color.red < 255 || this->color.red) this->color.red--;
		if (this->color.green < 255 || this->color.green) this->color.green--;
		if (this->color.blue < 255 || this->color.blue) this->color.blue++;

		std::cout << " dead" << std::endl;

		break;
	case FRIEND_OFFSET:
		energy += (observable->energy / 4) + ORGANIC_ENERGY;

		Matrix->at(observable->position.x).at(observable->position.y) = -1;
		List->erase(List->begin() + observableID);

		if (this->color.red < 255 || this->color.red) this->color.red++;
		if (this->color.green < 255 || this->color.green) this->color.green--;
		if (this->color.blue < 255 || this->color.blue) this->color.blue--;

		std::cout << " friend" << std::endl;

		break;
	case ENEMY_OFFSET:
		energy += (observable->energy / 4) + ORGANIC_ENERGY;

		Matrix->at(observable->position.x).at(observable->position.y) = -1;
		List->erase(List->begin() + observableID);

		if (this->color.red < 255 || this->color.red) this->color.red++;
		if (this->color.green < 255 || this->color.green) this->color.green--;
		if (this->color.blue < 255 || this->color.blue) this->color.blue--;

		std::cout << " enemy" << std::endl;

		break;
	default:
		break;
	}

	int i = (observableID <= 0 ? 0 : observableID <= 0);
	for (; i < List->size(); i++)
	{
		List->at(i).id = i;
		Matrix->at(List->at(i).position.x).at(List->at(i).position.y) = i;
	}

	curEnt = id;

	//std::cout << std::endl;

	return 2;
}