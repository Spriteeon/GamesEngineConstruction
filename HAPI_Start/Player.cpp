#include "Player.h"
#include "Visualisation.h"
#include <HAPI_lib.h>

void Player::Spawn(Visualisation& vis)
{

}

void Player::Update(Visualisation& vis)
{

	Vector2 pos{ GetPos() };
	shot = false; //Bullet hasnt been shot 
	const HAPI_TControllerData& controller = HAPI.GetControllerData(controllerNum);

	if (keyboard.scanCode[HK_DOWN]) //Move Down
	{
		pos.y += m_speed;
	}

	if (keyboard.scanCode[HK_UP]) //Move Up
	{
		pos.y -= m_speed;
	}

	if (keyboard.scanCode[HK_RIGHT]) //Move Right
	{
		pos.x += m_speed;
	}

	if (keyboard.scanCode[HK_LEFT]) //Move Left
	{
		pos.x -= m_speed;
	}

	if (keyboard.scanCode[HK_SPACE]) //Shoot
	{
		shot = true; //Bullet shot
	}

	if (controller.isAttached)
	{

		//Controller Buttons
		//D Pad
		if (controller.digitalButtons[HK_DIGITAL_DPAD_DOWN]) //Down
		{
			pos.y += m_speed;
		}
		if (controller.digitalButtons[HK_DIGITAL_DPAD_UP]) //Up
		{
			pos.y -= m_speed;
		}
		if (controller.digitalButtons[HK_DIGITAL_DPAD_RIGHT]) //Right
		{
			pos.x += m_speed;
		}
		if (controller.digitalButtons[HK_DIGITAL_DPAD_LEFT]) //Left
		{
			pos.x -= m_speed;
		}

		//AXYB
		if (controller.digitalButtons[HK_DIGITAL_A]) //A
		{
			shot = true;
		}
		if (controller.digitalButtons[HK_DIGITAL_X]) //X
		{

		}
		if (controller.digitalButtons[HK_DIGITAL_B]) //B
		{

		}
		if (controller.digitalButtons[HK_DIGITAL_Y]) //Y
		{

		}

		//Analogue Sticks
		//Left Analogue
		if (controller.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] > HK_GAMEPAD_LEFT_THUMB_DEADZONE) //Left Analogue RIGHT
		{
			pos.x += m_speed;
		}
		if (controller.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] < -HK_GAMEPAD_LEFT_THUMB_DEADZONE) //Left Analogue LEFT
		{
			pos.x -= m_speed;
		}
		if (controller.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] > HK_GAMEPAD_LEFT_THUMB_DEADZONE) //Left Analogue UP
		{
			pos.y -= m_speed;
		}
		if (controller.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] < -HK_GAMEPAD_LEFT_THUMB_DEADZONE) //Left Analogue DOWN
		{
			pos.y += m_speed;
		}

		//Right Analogue
		if (controller.analogueButtons[HK_ANALOGUE_RIGHT_THUMB_X] > HK_GAMEPAD_RIGHT_THUMB_DEADZONE) //Right Analogue RIGHT
		{
			pos.x += m_speed;
		}
		if (controller.analogueButtons[HK_ANALOGUE_RIGHT_THUMB_X] < -HK_GAMEPAD_RIGHT_THUMB_DEADZONE) //Right Analogue LEFT
		{
			pos.x -= m_speed;
		}
		if (controller.analogueButtons[HK_ANALOGUE_RIGHT_THUMB_Y] > HK_GAMEPAD_RIGHT_THUMB_DEADZONE) //Right Analogue UP
		{
			pos.y -= m_speed;
		}
		if (controller.analogueButtons[HK_ANALOGUE_RIGHT_THUMB_Y] < -HK_GAMEPAD_RIGHT_THUMB_DEADZONE) //Right Analogue DOWN
		{
			pos.y += m_speed;
		}

	}

	SetPos(pos);

}

void Player::Display(Visualisation& vis, float s)
{

	Vector2 interPos{ GetOldPos() + (GetPos() - GetOldPos()) * s }; //Interpolation
	vis.drawSprite(m_gfxName, interPos.x, interPos.y);

}

bool Player::Shoot()
{

	return shot;

}

