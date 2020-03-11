#include "Visualisation.h"
#include "Sprite.h"

Visualisation::Visualisation(int width, int height)
{

	//Set Screen Width and Height
	screenWidth = width;
	screenHeight = height;
	colour = (0, 0, 0);

	//Set Screen Rectangle values
	destRect.bottom = screenHeight;
	destRect.right = screenWidth;

	HAPI.Initialise(screenWidth, screenHeight, "HAPI");
	screenPointer = HAPI.GetScreenPointer();

}

Visualisation::~Visualisation()
{
	for (auto &sprite : mapSprite)
	{
		delete sprite.second; //Delete all Sprites in Sprite map
	}
}

void Visualisation::createSourceRect(const std::string& name)
{

	mapSprite[name]->createRect(); //Create Rectangles for all Sprites 

}

void Visualisation::screenColour() //Set every pixel to  colour
{

	BYTE* temp = screenPointer;
	for (int pixelIndex = 0; pixelIndex < (screenWidth * screenHeight); pixelIndex++)
	{

		memcpy(temp, &colour, 4);
		temp += 4;

	}

}

void Visualisation::createSprite(const std::string &location, const std::string& name) //Create the Sprites and add them to the Sprite map
{

	Sprite* sprite = new Sprite();
	sprite->initialisation(location);
	mapSprite[name] = sprite;

}

void Visualisation::drawSprite(const std::string& name, int posX, int posY)
{

	mapSprite.at(name)->clipBlit(screenPointer, screenWidth, destRect, posX, posY); //Clip the Sprites

}

//Return Functions
int Visualisation::getScreenWidth() const
{
	return screenWidth;
}

int Visualisation::getScreenHeight() const
{
	return screenHeight;
}

int Visualisation::getTexHeight(const std::string& name) const
{

	return mapSprite.at(name)->getTexHeight();

}

int Visualisation::getTexWidth(const std::string& name) const
{

	return mapSprite.at(name)->getTexWidth();

}