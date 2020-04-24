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
vector<vector<int>> matrix;

int age = 0;

bool isGameOver = false;

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
char defaultKillGenome[GENOME_SIZE] = {
	21, 31, 21, 21, 32, 21, 21, 32,
	21, 21, 31, 21, 21, 21, 21, 21,
	21, 21, 21, 21, 21, 31, 21, 21,
	21, 21, 21, 21, 32, 21, 21, 21,
	21, 21, 21, 32, 21, 21, 21, 21,
	21, 21, 21, 21, 21, 21, 21, 21,
	21, 21, 32, 21, 21, 21, 23, 21,
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
	matrix.resize(SCREEN_WIDTH / SIZE);

	for (int i = 0; i < SCREEN_WIDTH / SIZE; i++)
	{
		matrix.at(i).resize(SCREEN_HEIGHT / SIZE);
		for (size_t j = 0; j < SCREEN_HEIGHT / SIZE; j++)
			matrix.at(i).at(j) = -1;
	}


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

	entList.push_back(Entity(0, randomGenome0, entList, matrix));
	entList.at(0).position.x = 40;
	entList.at(0).position.y = 50;
	matrix[40][50] = 0;
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

		Draw();

		int countA = 0;
		int countD = 0;
		for (int i = 0; i < entList.size(); i++)
			if (!entList.at(i).isDead)
				countA++;
			else
				countD++;

		cout << "Alive: " << countA << "\tDead: " << countD  << "\tAll: " << entList.size() << endl;

		if ((isGameOver == true) || (entList.size() == 0) || (countA == 0))
		{
			cout << "You are alone! Game Over!" << endl;
			//char f;
			//cin >> f;
		}
	}

	return 0;
}


void ageHandler()
{
	for (int curEnt = 0; curEnt < entList.size(); curEnt++)
	{
		Entity& ent = entList.at(curEnt);

		if (ent.isDead)
		{
			int id = ent.id;
			matrix.at(ent.position.x).at(ent.position.y) = -1;
			entList.erase(entList.begin() + id);


			int i = (id <= 0 ? 0 : id <= 0);
			for (; i < entList.size(); i++)
			{
				entList.at(i).id = i;
				matrix.at(entList.at(i).position.x).at(entList.at(i).position.y) = i;
			}

			continue;
		}

		char gp = ent.genp;
		char offset = ent.genoffset;
		try
		{
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


				if (ent.energy >= DIVISION_ENERGY)
				{
					ent.Division(gen, gp);

					break;
				}
				
				if (gen == 15)
					offset = ent.Rotate(gen, gp, false);
				if (gen == 16)
					offset = ent.Rotate(gen, gp, true);
				if (gen == 17)
					offset = ent.Look(gen, gp, false);
				if (gen == 18)
					offset = ent.Look(gen, gp, true);
				if (gen == 19)
					offset = ent.Move(gen, gp, false);
				if (gen == 20)
					offset = ent.Move(gen, gp, true);
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
					offset = ent.Eat(gen, gp, false, curEnt);
					break;
				}
				if (gen == 32)
				{
					offset = ent.Eat(gen, gp, true, curEnt);
					break;
				}
				else
					offset = gen;
			}

			try
			{

				if (curEnt == entList.size()) curEnt = entList.size() - 1;

				entList.at(curEnt).genp = gp;
				entList.at(curEnt).genoffset = offset;
			}
			catch (std::out_of_range)
			{
				isGameOver = true;
			}
		}
		catch (std::out_of_range)
		{
			cout << "OUT OF RANGE: ageHandler - " << curEnt << " / " << entList.size() << endl;
			int f;
			cin >> f;
		}
	}
	age++;
}

void Draw()
{
	window.clear();

	for (int i = 0; i < entList.size(); i++)
	{
		Vector2 pos = entList.at(i).position;
		int e = entList.at(i).energy;

		sf::RectangleShape rec(sf::Vector2f(SIZE, SIZE));
		rec.setPosition(pos.x * SIZE, pos.y * SIZE);
		sf::Color deadcol(30, 30, 30);

		double r = ((double)e / 10000.0) * 255;
		if (r > 255) r = 255;
		sf::Color col(r, 100, 0);

		if (entList.at(i).isDead)
			rec.setFillColor(deadcol);
		else
		{
			//sf::Color col(entList.at(i).color.red, entList.at(i).color.green, entList.at(i).color.blue);
			rec.setFillColor(col);
		}

		window.draw(rec);
	}

	window.display();
}