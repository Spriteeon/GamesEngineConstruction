#include "Entity.h"
#include <string>

class Enemy : public Entity //Inherits from Entity Class
{ 
private:

	EDirection m_direction{ EDirection::eDirectionLeft }; //Start direction is left so moves onto screen after spawning

public:

	Enemy(const std::string& name) : Entity(name) { m_side = ESide::eSideEnemy; enemyMark = true; m_health = 20; m_damage = 1; m_speed = 4; }; //Initialise all Enemy Data
	void Update(Visualisation& vis) override final;
	void Display(Visualisation& vis, float s) override final;
	void Spawn(Visualisation& vis) override final;

};

