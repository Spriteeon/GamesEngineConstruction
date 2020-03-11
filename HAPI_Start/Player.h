#include "Entity.h"
#include <HAPI_lib.h>
#include <vector>
#include <string>

using namespace HAPISPACE;

class Player : public Entity //Inherits from Entity Class
{
private:

	int controllerNum{ 0 };
	const HAPI_TKeyboardData& keyboard = HAPI.GetKeyboardData();

	bool shot{ false }; //Marker for if bullet has been shot or not

public:

	Player(const std::string& name) : Entity(name) { m_active = true; playerMark = true; m_side = ESide::eSidePlayer; m_health = 100; m_damage = 1; m_speed = 6; }; //Initialises Player Data
	void Update(Visualisation& vis) override final;
	void Display(Visualisation& vis, float s) override final;
	void Spawn(Visualisation& vis) override final;
	bool Shoot() override final;

};

