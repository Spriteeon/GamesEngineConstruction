#pragma once
#include <HAPI_lib.h>
#include <vector>
#include <fstream>

#include "Bullet.h"

using namespace HAPISPACE;

class Visualisation;
class Entity;
class Bullet;

class World
{

private:

	std::vector<Entity*> m_entityVector; //Vector to hold all Entities
	std::shared_ptr<Visualisation> m_viz; //Visualistion Pointer to use in World System

	int screenWidth, screenHeight;

	int m_score{ 0 }; //Player Score
	int m_highscore{ 0 };

	bool bulletShot = false; //Bullet shot marker

	std::ifstream scoreFile;

public:

	~World();
	bool Initialise(int width, int height);
	void Run();
};

