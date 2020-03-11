#include "Sprite.h"

Sprite::Sprite()
{

}

Sprite::~Sprite()
{
	delete[] texturePointer; //Delete texture point after Sprite is Deleted
}

void Sprite::createRect()
{

	//Set Rectangle values
	sourceRect.bottom = texHeight;
	sourceRect.right = texWidth;

}

void Sprite::blit(BYTE* screenPnter, int screenWidth, int posX, int posY) //This function is used when clipping is unneccassary
{

	BYTE* screenPosPnter = screenPnter + ((size_t)posX + (size_t)posY * screenWidth) * 4;
	BYTE* texturePnter = texturePointer;

	int endOfLineScreenIncrement = (screenWidth - texWidth) * 4;

	for (int Y = 0; Y < texHeight; Y++)
	{
		for (int X = 0; X < texWidth; X++) //For every pixel
		{

			BYTE red = texturePnter[0];
			BYTE green = texturePnter[1];
			BYTE blue = texturePnter[2];
			BYTE alpha = texturePnter[3];

			if (alpha == 255) //If texture is 'Solid'
			{

				screenPosPnter[0] = red;
				screenPosPnter[1] = green;
				screenPosPnter[2] = blue;

			}

			else if (alpha > 0)
			{

				screenPosPnter[0] = screenPosPnter[0] + ((alpha * (red - screenPosPnter[0])) >> 8);
				screenPosPnter[1] = screenPosPnter[1] + ((alpha * (green - screenPosPnter[1])) >> 8);
				screenPosPnter[2] = screenPosPnter[2] + ((alpha * (blue - screenPosPnter[2])) >> 8);

			}

			texturePnter += 4;
			screenPosPnter += 4;

		}

		screenPosPnter += endOfLineScreenIncrement;

	}

}

void Sprite::clipBlit(BYTE* screenPnter, int screenWidth, const Rectangle& destRect, int posX, int posY) //This function is used when clipping is needed
{

	Rectangle clipped(sourceRect); 

	clipped.Translate(posX, posY);

	if (!clipped.CompletelyOutside(destRect))
	{
		if (clipped.CompletelyInside(destRect))
		{

			blit(screenPnter, screenWidth, posX, posY);

		}

		else
		{

			clipped.ClipTo(destRect);
			clipped.Translate(-posX, -posY);

			posX = std::max(0, posX);
			posY = std::max(0, posY);

			BYTE* screenPosPnter = (screenPnter + ((size_t)posX + (size_t)posY * screenWidth) * 4);

			BYTE* texturePnter = texturePointer + (((size_t)clipped.left * 4) + ((size_t)clipped.top * sourceRect.Width() * 4));

			for (int Y = 0; Y < clipped.Height(); Y++)
			{
				for (int X = 0; X < clipped.Width(); X++) //For every pixel
				{

					BYTE red = texturePnter[0];
					BYTE green = texturePnter[1];
					BYTE blue = texturePnter[2];
					BYTE alpha = texturePnter[3];

					if (alpha == 255)
					{

						screenPosPnter[0] = red;
						screenPosPnter[1] = green;
						screenPosPnter[2] = blue;

					}

					else if (alpha > 0)
					{

						screenPosPnter[0] = screenPosPnter[0] + ((alpha * (red - screenPosPnter[0])) >> 8);
						screenPosPnter[1] = screenPosPnter[1] + ((alpha * (green - screenPosPnter[1])) >> 8);
						screenPosPnter[2] = screenPosPnter[2] + ((alpha * (blue - screenPosPnter[2])) >> 8);

					}

					texturePnter += 4;
					screenPosPnter += 4;

				}

				screenPosPnter += (destRect.Width() - (size_t)clipped.Width()) * 4;
				texturePnter += (sourceRect.Width() - (size_t)clipped.Width()) * 4;
			}

		}
	}

	clipped.Translate(-posX, -posY);

}

bool Sprite::initialisation(const std::string& location)
{

	if (!HAPI.LoadTexture(location, &texturePointer, texWidth, texHeight))
	{
		//ERROR
		HAPI.UserMessage("Texture not found", "Error!");
		return false;

	}
	return true;
}
