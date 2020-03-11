#include "Entity.h"
#include "Visualisation.h"
#include "Sprite.h"

bool Entity::CheckForCollisions(Entity& otherEntity, Visualisation& vis)
{

	//Create Collision recatngles
	Rectangle rectA;
	Rectangle rectB;

	//First Rectangle Data
	rectA.top = m_pos.y;
	rectA.left = m_pos.x;
	rectA.bottom = m_pos.y + vis.getTexHeight(m_gfxName);
	rectA.right = m_pos.x + vis.getTexWidth(m_gfxName);

	//Second Rectangle Data
	rectB.top = otherEntity.m_pos.y;
	rectB.left = otherEntity.m_pos.x;
	rectB.bottom = otherEntity.m_pos.y + vis.getTexHeight(otherEntity.m_gfxName);
	rectB.right = otherEntity.m_pos.x + vis.getTexWidth(otherEntity.m_gfxName);
	
	if ((rectA.right < rectB.left || rectA.left > rectB.right) || (rectA.bottom < rectB.top || rectA.top > rectB.bottom))
	{
		//No Collision
		return false;
	}
	else
	{
		//Collision
		return true;
	}

}

void Entity::TakeDamage(int damage)
{

	//Take Damage
	m_health -= damage;

	//If no Health, Die
	if (m_health <= 0)
	{
		Die();
	}

}

void Entity::Die() //Explosions will be handled in individual Die functions
{

	m_active = false;

}