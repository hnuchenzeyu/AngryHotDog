#include "MyGraph.h"


void MyGraph::Draw2Lines(HDC hdc, POINT mouseP)
{
	Pen pen(Color(0, 0, 0), 4);
	PointF L_PTStart1(117,210);
	PointF L_PTStart2(146,209);
	PointF L_PTEnd(mouseP.x,mouseP.y);
	Graphics graphics(hdc);
	graphics.DrawLine(&pen, L_PTStart1, L_PTEnd);
	hotDog->SetPosition(mouseP.x-10, mouseP.y-45);
	hotDog->Draw(hdc);
	graphics.DrawLine(&pen, L_PTStart2, L_PTEnd);
}
void MyGraph::DrawLine(HDC hdc)
{
	Pen pen(Color(0, 0, 0), 4);
	PointF L_PTStart1(117, 210);
	PointF L_PTStart2(146, 209);
	Graphics graphics(hdc);
	graphics.DrawLine(&pen, L_PTStart1, L_PTStart2);
}
