#include "Bullet.h"
#include "Visualisation.h"

void Bullet::Spawn(Visualisation& vis)
{
	m_health = 1; //Resets Health when respawned so can be shot again
}

void Bullet::Update(Visualisation& vis)
{

	Vector2 pos{ GetPos() };

	if (m_side == ESide::eSidePlayer) //If Player shot Bullet
	{
		pos.x += m_speed;

		if (pos.x > vis.getScreenWidth())
		{
			m_active = false; //Set to not active if goes off screen
		}
	}

	if (m_side == ESide::eSideEnemy) //If Enemey shot Bullet
	{
		pos.x -= m_speed;

		if (pos.x < - vis.getTexWidth(m_gfxName))
		{
			m_active = false; //Set to not active if goes off screen
		}
	}

	SetPos(pos);

}

void Bullet::Display(Visualisation& vis, float s)
{

	Vector2 interPos{ GetOldPos() + (GetPos() - GetOldPos()) * s }; //Interpolate position
	vis.drawSprite(m_gfxName, interPos.x, interPos.y);

}
