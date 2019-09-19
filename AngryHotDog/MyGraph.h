#pragma once

#include "TinyEngine\T_Graph.h"
#include "xuan.h"
///³ÂÔóÓî
class MyGraph:T_Graph
{
private:
	T_Sprite *hotDog;
public:
	MyGraph() {}
	MyGraph(T_Sprite *d)
	{
		this->hotDog = d;
	}
	void Draw2Lines(HDC hdc, POINT mouseP);
	static void DrawLine(HDC hdc);
};