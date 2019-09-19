#pragma once
#include "TinyEngine\T_Sprite.h"
typedef struct velocity
{
	int Vx;
	int Vy;
}Velocity;

class HotDog :T_Sprite
{
	static int acc;
public:
	HotDog(wstring imgPath, int frameWidth = 0, int frameHeight = 0);
	void UpdateHotDogPos();

	Velocity v;
};