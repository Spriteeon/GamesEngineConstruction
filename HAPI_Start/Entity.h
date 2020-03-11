#pragma once
#include <string>
#include "Vector2.h"

enum class ESide //Entity sides, cant collide with own side or Neutral
{
	eSidePlayer,
	eSideEnemy,
	eSideNeutral
};

enum class EDirection //Entity Directions
{
	eDirectionLeft,
	eDirectionRight,
	eDirectionUp,
	eDirectionDown,
	eDirectionNeutral
};

class Sprite;
class Visualisation;
class Entity
{
private:

	Vector2 m_oldPos{ 0,0 }; //Old pos for Interpolation
	Vector2 m_pos{ 0,0 };

protected:

	bool m_active{ false };
	ESide m_side{ ESide::eSideNeutral };
	int m_health{ 0 };
	int m_damage{ 0 };
	int m_speed{ 0 };
	std::string m_gfxName;

	//Markers for Entity type
	bool bulletMark{ false };
	bool enemyMark{ false };
	bool playerMark{ false };

public:

	Entity(const std::string& name) : m_gfxName(name) {}; //m_gfxName automatically set
	virtual ~Entity() = default;

	//Virtual functions for all Entities
	virtual void Update(Visualisation& vis) = 0;
	virtual void Display(Visualisation& vis, float s) = 0;
	virtual void Spawn(Visualisation& vis) = 0;
	virtual bool Shoot() { return false; };
	virtual void Die();

	bool CheckForCollisions(Entity& otherEntity, Visualisation& vis);
	void TakeDamage(int damage);

	void SetPos(Vector2 newPos) { m_oldPos = m_pos; m_pos = newPos; };
	void SetOldPos(Vector2 newPos) { m_oldPos = newPos; m_pos = newPos; };
	void SetSide(ESide side) { m_side = side; };
	void SetActive() { m_active = true; };

	//Get functions for transferring private/protected data
	ESide GetSide() { return m_side; };
	int GetDamage() { return m_damage; };
	std::string GetName() { return m_gfxName; };
	Vector2 GetOldPos() { return m_oldPos; };
	Vector2 GetPos() { return m_pos; };

	bool IsActive() { return m_active; };

	//Return Entity type markers
	bool IsPlayer() { return playerMark; };
	bool IsBullet() { return bulletMark; };
	bool IsEnemy() { return enemyMark; };

};

