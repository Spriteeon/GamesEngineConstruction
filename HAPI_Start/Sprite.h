#pragma once
#include <HAPI_lib.h>
#include "Rectangle.h"

using namespace HAPISPACE;

class Sprite
{
protected:

	BYTE* texturePointer{ nullptr }; //Pointer for top left of Sprite
	int texWidth{ 0 };
	int texHeight{ 0 };

	Rectangle sourceRect; //Create Rectangle for Sprite

public:

	Sprite();
	~Sprite();
	void createRect();
	void blit(BYTE* screenPnter, int screenWidth, int posX, int posY);
	void clipBlit(BYTE* screenPnter, int screenWidth, const Rectangle& destRect, int posX, int posY);
	bool initialisation(const std::string& location);

	//Returns Width and Height of Sprite
	int getTexWidth() const { return texWidth; };
	int getTexHeight() const { return texHeight; };

};

