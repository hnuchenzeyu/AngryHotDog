#include"xuan.h"

//WinMain
int WINAPI WinMain(HINSTANCE h_instance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	LPCTSTR WinTitle = L"xuan1";
	xuan* xuan1 = new xuan(h_instance, WIN_CLASS, WinTitle, NULL, NULL, WIN_WIDTH, WIN_HEIGHT);
	T_Engine::pEngine = xuan1;
	xuan1->SetFrame(300);
	//mybmp->SetFullScreen(TRUE);
	xuan1->StartEngine();
	return TRUE;
}