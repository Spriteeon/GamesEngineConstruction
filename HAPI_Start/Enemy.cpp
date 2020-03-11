#include "Enemy.h"
#include "Visualisation.h"
#include <time.h>
#include <HAPI_lib.h>

void Enemy::Spawn(Visualisation& vis) 
{

	Vector2 pos{ 0,0 };

	m_health = 20;

	//Spawn at a random Y value to the right of the screen
	pos.y = rand() % (vis.getScreenHeight() - vis.getTexHeight(m_gfxName));
	pos.x = vis.getScreenWidth();

	SetOldPos(pos); //Set old pos aswell so interpolation still works
	SetPos(pos);

	m_active = true;

	m_direction = EDirection::eDirectionLeft;

}

void Enemy::Update(Visualisation& vis)
{

	Vector2 pos{ GetPos() };

	if ((m_direction == EDirection::eDirectionLeft) && (pos.x > vis.getScreenWidth() - (vis.getTexWidth(m_gfxName) + 10))) //Move onto screen after spawning to the right of it
	{
		pos.x -= m_speed;
		if (pos.x <= vis.getScreenWidth() - (vis.getTexWidth(m_gfxName) + 10))
		{
			m_direction = EDirection::eDirectionDown; //When on the Screen, move down
		}
	}

	if ((m_direction == EDirection::eDirectionDown) && ((pos.y + vis.getTexHeight(m_gfxName)) < vis.getScreenHeight())) //If Space on the screen to move down
	{
		pos.y += m_speed;
		if ((pos.y + vis.getTexHeight(m_gfxName)) >= vis.getScreenHeight()) //If at bottom of screen
		{
			m_direction = EDirection::eDirectionUp;
		}
	}

	if (m_direction == EDirection::eDirectionUp && (pos.y > 0)) //If space on the screen to move up
	{
		pos.y -= m_speed;
		if (pos.y <= 0) //If at top of screen
		{
			m_direction = EDirection::eDirectionDown;
		}
	}

	SetPos(pos);

	//Shooting

}

void Enemy::Display(Visualisation& vis, float s)
{
	
	Vector2 interPos{ GetOldPos() + (GetPos() - GetOldPos()) * s }; //Interpolation
	vis.drawSprite(m_gfxName, interPos.x, interPos.y);

}
