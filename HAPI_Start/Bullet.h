#include "Entity.h"

class Bullet : public Entity //Inherits from Entity Class
{
private:

public:

	Bullet(const std::string& name) : Entity(name) { m_active = false; m_speed = 16; bulletMark = true; m_damage = 10; m_health = 1; }; //Initialise all bullet Data
	void Update(Visualisation& vis) override final;
	void Display(Visualisation& vis, float s) override final;
	void Spawn(Visualisation& vis) override final;

};