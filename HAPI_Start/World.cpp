#include "World.h"
#include "Visualisation.h"
#include "Player.h"
#include "Enemy.h"
#include "Entity.h"
#include "Background.h"

#include <fstream>
#include <time.h>
#include <cassert>

bool World::Initialise(int width, int height)
{

	//Set Screen Width and Height
	screenWidth = width;
	screenHeight = height;

	if (!HAPI.SetShowFPS(true, 10, 10, HAPI_TColour::WHITE))
	{
		//ERROR
		std::cout << "FPS not shown" << std::endl;
		return false;
	}

	m_viz = std::make_shared<Visualisation>(screenWidth, screenHeight);

	//Load in all Sprites
	m_viz->createSprite("Data/playership.png", "playerGraphic");
	m_viz->createSprite("Data/enemyship.png", "enemyGraphic");
	m_viz->createSprite("Data/bullet.png", "bulletGraphic");
	m_viz->createSprite("Data/stars.png", "backgroundGraphic");

	//Create Rectangles for all Sprites
	m_viz->createSourceRect("playerGraphic");
	m_viz->createSourceRect("enemyGraphic");
	m_viz->createSourceRect("bulletGraphic");
	m_viz->createSourceRect("backgroundGraphic");

	//Create Entities
	Background* background = new Background("backgroundGraphic");
	Player* player = new Player("playerGraphic");
	
	//Add Entities to Entity Vector
	m_entityVector.push_back(background);
	m_entityVector.push_back(player);

	for (int i = 0; i < 1; i++) //Create Enemies and add to Entity Vector
	{
		Enemy* enemy = new Enemy("enemyGraphic");
		m_entityVector.push_back(enemy);
	}

	for (int i = 0; i < 100; i++) //Create Bullets and add to Entity Vector
	{
		Bullet* bullet = new Bullet("bulletGraphic"); //Need to find bullet graphic
		m_entityVector.push_back(bullet);
	}

	return false;

}

constexpr DWORD kTickTime{ 50 };

void World::Run()
{
	srand(time(0));

	DWORD lastTimeTicked{ 0 };

	while (HAPI.Update()) //Game Loop
	{

		for (auto& entity : m_entityVector) 
		{
			if (entity->IsEnemy() && !entity->IsActive()) 
			{
				entity->Spawn(*m_viz); //Reset Enemies after dying
			}
			if (entity->IsBullet() && !entity->IsActive())
			{
				entity->Spawn(*m_viz); //Reset Bullets after being shot
			}
		}

		DWORD timeSinceLastTick{ HAPI.GetTime() - lastTimeTicked };
		if (timeSinceLastTick >= kTickTime)
		{

			for (auto& eachEntity : m_entityVector)
			{
				//Shooting
				bulletShot = false; //bullet has not been shot
				if (eachEntity->IsActive() && eachEntity->Shoot() && bulletShot == false)
				{
					for (int i = 0; i < m_entityVector.size(); i++) //loop through bullet array
					{
						if ((m_entityVector[i]->IsBullet()) && (!m_entityVector[i]->IsActive()))
						{
							
							//Set initial Bullet position
							m_entityVector[i]->SetPos({ (m_viz->getTexWidth(eachEntity->GetName()) + eachEntity->GetPos().x), (m_viz->getTexHeight(eachEntity->GetName()) / 2) + (eachEntity->GetPos().y - (m_viz->getTexHeight(m_entityVector[i]->GetName()) / 2)) });
							m_entityVector[i]->SetSide(eachEntity->GetSide()); //Set bullet to side of shooter
							m_entityVector[i]->SetActive(); //Make Bullet appear

							i = m_entityVector.size(); //Jump out of for loop
							bulletShot = true; //bullet has been shot

						}
					}
				}
			}

			for (auto& eachEntity : m_entityVector)
			{
				if (eachEntity->IsActive())
				{
					eachEntity->Update(*m_viz); //Update every Entity pos
				}
			}

			lastTimeTicked = HAPI.GetTime();

			for (auto& eachEntity : m_entityVector)
			{
				if (eachEntity->IsActive() && eachEntity->GetSide() != ESide::eSideNeutral) //Only test collisions on active non neutral Entities
				{
					//Collision testing here
					for (auto& otherEntity : m_entityVector)
					{
						if (otherEntity->IsActive())
						{
							if (eachEntity->GetSide() != otherEntity->GetSide())
							{
								//Test for Collisions
								if (eachEntity->CheckForCollisions(*otherEntity, *m_viz))
								{
									//Take Damage
									eachEntity->TakeDamage(otherEntity->GetDamage());
									if (otherEntity->GetSide() == ESide::eSidePlayer && !eachEntity->IsActive()) //If Player killed Enemy
									{
										m_score += 1; //Increase player score
									}
								}
							}
						}
					}

				}
			}

			timeSinceLastTick = 0;

		}

		//Needed for Interpolation
		float s = timeSinceLastTick / (float)kTickTime;
		assert(s >= 0 && s <= 1.0f); 

		for (auto& eachEntity : m_entityVector)
		{
			if (eachEntity->IsActive()) //Only display active Entities
			{
				//Display new Positions
				eachEntity->Display(*m_viz, s);
			}
		}

		//Display Score and HUD
		for (auto& eachEntity : m_entityVector)
		{
			if (eachEntity->IsPlayer())
			{
				//Display Score
				std::string score = std::to_string(m_score);
				if (!HAPI.RenderText( 10, 500, HAPI_TColour::WHITE, ("Score: " + score), 16, eBold))
				{
					//ERROR
					std::cout << "Can't display score!" << std::endl;
				}

				scoreFile.open("Highscore.txt");
				scoreFile >> m_highscore;

				if (!HAPI.RenderText( 10, 550, HAPI_TColour::WHITE, std::string("Highscore: " + std::to_string(m_highscore)), 16, eBold))
				{
					//ERROR
					std::cout << "Can't display Highscore!" << std::endl;

				}

				//Highscore Control 
				if (m_score > m_highscore)
				{
					std::ofstream scoreFile("Highscore.txt", std::ofstream::trunc);
					scoreFile << m_score;
					scoreFile.close();
				}

			}
		}

	}
}

World::~World()
{

	for (auto& entity : m_entityVector)
	{
		delete entity; //Delete every Entity when World Deleted
	}

}