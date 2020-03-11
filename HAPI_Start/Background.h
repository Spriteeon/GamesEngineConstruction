#pragma once
#include "Vector2.h"
#include "Entity.h"

#include <string>

class Background : public Entity //Inherits from Entity Class
{

private:

	Vector2 posOne{ 0,0 }; //First scroll start pos
	Vector2 posTwo{ 800,0 }; //Second scroll start pos

public:

	Background(const std::string& name) : Entity(name) { m_speed = -1; m_active = true; };

	void Spawn(Visualisation& vis) override final;

	void Update(Visualisation& vis) override final;
	void Display(Visualisation& vis, float s) override final;

	void Die() override final { return; }; //Background cant 'die' so function does nothing

};

