#include "Background.h"
#include "Visualisation.h"
#include "Sprite.h"

void Background::Spawn(Visualisation& vis)
{

}

void Background::Update(Visualisation& vis)
{

	//Create continuous scrolling effect
	if (posOne.x == -vis.getTexWidth(m_gfxName))
	{
		posOne.x = vis.getTexWidth(m_gfxName);
	}
	if (posTwo.x == -vis.getTexWidth(m_gfxName))
	{
		posTwo.x = vis.getTexWidth(m_gfxName);
	}

	posOne.x += m_speed; //Both backgrounds move left at same speed
	posTwo.x += m_speed;

}

void Background::Display(Visualisation& vis, float s)
{

	vis.drawSprite(m_gfxName, posOne.x, posOne.y); //Draw two backgrounds to create scrolling effect
	vis.drawSprite(m_gfxName, posTwo.x, posTwo.y);

}

