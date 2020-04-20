#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Entity.h"
#include <vector>
#include <stdio.h>
#include <time.h>
#include "Definitions.h"

using namespace std;

vector<Entity> entList;

int age = 0;

char defaultGenome[GENOME_SIZE] = {
	21, 21, 21, 21, 21, 21, 21, 21,
	21, 21, 21, 21, 21, 21, 21, 21,
	21, 21, 21, 21, 21, 21, 21, 21,
	21, 21, 21, 21, 21, 21, 21, 21,
	21, 21, 21, 21, 21, 21, 21, 21,
	21, 21, 21, 21, 21, 21, 21, 21,
	21, 21, 21, 21, 21, 21, 21, 21,
	21, 21, 21, 21, 21, 21, 21, 21,
};
char defaultGenomeL[GENOME_SIZE] = {
	20, 6, 6, 9, 1, 1, 1, 21,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 21, 1, 1, 1,
	1, 21, 1, 1, 1, 1, 21, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 21, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1
};
char defaultGenomeT[GENOME_SIZE] = {
	20, 0, 6, 9, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1
};
char defaultGenomeR[GENOME_SIZE] = {
	20, 2, 6, 9, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1
};
char defaultGenomeB[GENOME_SIZE] = {
	20, 4, 6, 9, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1
};
char randomGenome0[GENOME_SIZE];
char randomGenome1[GENOME_SIZE];
char randomGenome2[GENOME_SIZE];

sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "MicroWorld");
vector<sf::RectangleShape> entities;

void ageHandler();
void Draw();

int main()
{
	srand(time(0));
	for (char i = 0; i < GENOME_SIZE; i++)
	{
		randomGenome0[i] = MIN_GEN + rand() % MAX_GEN;
	}
	for (char i = 0; i < GENOME_SIZE; i++)
	{
		randomGenome1[i] = MIN_GEN + rand() % MAX_GEN;
	}
	for (char i = 0; i < GENOME_SIZE; i++)
	{
		randomGenome2[i] = MIN_GEN + rand() % MAX_GEN;
	}

	entList.push_back(Entity(randomGenome0, entList));
	entList.at(0).position.x = 40;
	entList.at(0).position.y = 30;
	entList.at(0).energy = 100000;

	Draw();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		ageHandler();

		window.clear();

		Draw();

		window.display();

		int count = 0;
		for (int i = 0; i < entList.size(); i++)
			if (!entList.at(i).isDead)
				count++;

		cout << count << endl;
	}

	return 0;
}


void ageHandler()
{
	for (auto curEnt = 0; curEnt < entList.size(); curEnt++)
	{
		Entity &ent = entList.at(curEnt);

		if (ent.isDead)
		{
			ent.genome[1] = 0;
			ent.MoveAbs(0, 0);
			continue;
		}

		char gp = ent.genp;
		char offset = ent.genoffset;

		for (char step = 0; step < STEPS; step++)
		{
			ent.energy--;

			if (ent.energy < 0)
			{
				ent.isDead = true;

				break;
			}

			gp = (gp + offset) % GENOME_SIZE;
			offset = 1;

			char gen = ent.genome[gp];

			if (ent.energy >= 10000)
			{
				ent.Division(gen, gp);

				break;
			}

			if (gen == 15)
				offset = ent.RotateAbs(gen, gp);
			if (gen == 16)
				offset = ent.RotateRel(gen, gp);
			if (gen == 17)
				offset = ent.LookAbs(gen, gp);
			if (gen == 18)
				offset = ent.LookRel(gen, gp);
			if (gen == 19)
				offset = ent.MoveAbs(gen, gp);
			if (gen == 20)
				offset = ent.MoveRel(gen, gp);
			if (gen == 21)
			{
				offset = ent.Photosynthesis(gen, gp);
				break;
			}
			if (gen == 30)
			{
				offset = ent.Division(gen, gp);
				break;
			}
			if (gen == 31)
			{
				offset = ent.EatAbs(gen, gp);
				break;
			}
			else
				offset = gen;
		}

		entList.at(curEnt).genp = gp;
		entList.at(curEnt).genoffset = offset;
	}

	age++;
}

void Draw()
{
	for (int i = 0; i < entList.size(); i++)
	{
		Vector2 pos = entList.at(i).position;

		sf::RectangleShape rec(sf::Vector2f(SIZE, SIZE));
		rec.setPosition(pos.x * SIZE, pos.y * SIZE);

		if (entList.at(i).isDead)
			rec.setFillColor(sf::Color::Cyan);
		else
			rec.setFillColor(sf::Color::Green);

		window.draw(rec);
	}
}