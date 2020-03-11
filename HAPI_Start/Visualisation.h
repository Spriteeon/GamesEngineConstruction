#pragma once
#include <HAPI_lib.h>
#include <unordered_map>
#include <string>

#include "Rectangle.h"

using namespace HAPISPACE;

class Sprite;
class Visualisation
{
protected:

	BYTE* screenPointer{ nullptr }; //Pointer for top left of Screen
	int screenWidth, screenHeight;

	std::unordered_map<std::string, Sprite*> mapSprite; //Map that holds all the Sprites
	HAPI_TColour colour;

	Rectangle destRect; //Create Rectangle for Screen

public:

	Visualisation(int width, int height);
	~Visualisation();

	void createSourceRect(const std::string& name);
	void screenColour();
	void createSprite(const std::string& location, const std::string& name);
	void drawSprite(const std::string& name, int posX, int posY);

	//Get Functions
	int getScreenWidth() const;
	int getScreenHeight() const;
	int getTexHeight(const std::string& name) const;
	int getTexWidth(const std::string& name) const;

};

