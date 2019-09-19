#include "HotDog.h"
int HotDog::acc = 2;
HotDog::HotDog(wstring imgPath, int frameWidth, int frameHeight):T_Sprite(imgPath, frameWidth, frameHeight)
{
	
}

void HotDog::UpdateHotDogPos()
{
	if (this->GetX() != 103 || this->GetY() != 181)
	{
		this->Move(v.Vx*0.1, v.Vy*0.1);
		v.Vy -= acc;
	}
}