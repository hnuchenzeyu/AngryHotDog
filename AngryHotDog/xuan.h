#pragma once
#include "TinyEngine\\T_AI.h"
#include "TinyEngine\\T_Graph.h"
#include "TinyEngine\\T_Sprite.h"
#include "TinyEngine\\T_Engine.h"
#include "TinyEngine\\T_Menu.h"
#include "TinyEngine\T_Menunew.h"
#include "TinyEngine\T_Scene.h"
#include "MyGraph.h"



//��Ľṹ�� ��Ϊ�кܶ��������Թ����ṹ��
//typedef struct 
//{
//	wstring filename;//��ɫ�����ļ�
//	int wframe;//��Ӧ���
//	int hframe;
//}AIRCRAFTINFO;
typedef struct
{
	int Vx;
	int Vy;
}Velocity;
typedef struct
{
	wstring filename;//��ɫ�����ļ�
	int wframe;//��Ӧ���
	int hframe;
}CLOUDINFO;
typedef struct
{
	wstring filename;//�˵�ͼƬ
	int btnwidth;//��Ӧ���
	int btnheight;
}PAUSEMENUINFO;
typedef vector<T_Sprite*>vSpriteSet;
//typedef vector<T_Menunew*>vMenuSet;

class xuan :public T_Engine
{
public:
	xuan(HINSTANCE hInstance, LPCTSTR szWindowClass, LPCTSTR szTitle,
		WORD Icon = NULL, WORD SmIcon = NULL,
		int iWidth = WIN_WIDTH, int iHeight = WIN_HEIGHT);
	~xuan();

	void GameInit();
	void GameLogic();
	void GameEnd();
	void GamePaint(HDC hdc);
	void GameKeyAction(int ActionType = KEY_SYS_NONE);
	void GameMouseAction(int x, int y, int ActionType);

private:

	int wnd_width, wnd_height;	//��Ϸ���ڿ��
	static const long T_LENGTH = 4500; //���ʱ��
	
	static const int PAUSE_NUM = 5; //��ͣʱ�˵���ť����
	static const int LEVEL_NUM = 3+1;//�ؿ���ť����Ϊ3,����1�����ذ�ť
	//static CLOUDINFO cloud[8]; //�����ɫ�����ļ�����֡ͼ��� �߸����Ա������ȡ���㶯���ļ�
	static PAUSEMENUINFO pmenu[PAUSE_NUM+1];
	static PAUSEMENUINFO lmenu[LEVEL_NUM];
	//static int sequence[8]; //���¶�����ҽ�ɫ����֡���У�ʹ����Ӧ�����֡Ƶ
	POINT mousePT;//��ǰ���λ��

	T_Graph* back;//����ͼ
	T_Graph* levelback;//����ͼ
	T_Graph* title;//���˵�ҳ���logo
	T_Graph* hamburger;//
	T_Graph* hotdogsmall;//�ȹ�С�� ������־
	T_Graph* scorelevel1;//level1����˼��
	T_Graph* buttons;//button�ϼ�
	T_Graph* upgradeback;//��һ�ر���
	T_Graph* helpPlayerback;//��������
	

	int ham_x, ham_y;//�������Ŀ��
	int upgrademenu_w, upgrademenu_h, upgrademenu_x, upgrademenu_y;//��һ���˵��ı��������λ��
	int caodi_height;//�ݵصĸ߶�
	int level=1;//�ؿ�
	int pausemenu_width;//��ͣҳ��Ŀ�
	bool level1lock=true;//�ؿ�1�Ƿ���ס��
	bool level2lock=true;//�ؿ�2�Ƿ���ס��
	bool isplaysound = true;//�Ƿ񲥷����ֵ��ж�ֵ
	bool isfail = true;//�Ƿ�ʧ����
	T_Sprite *player;
	T_Sprite* tanhuang;
	int hotdogcount;//�ӵ��ȹ���
	//T_Sprite* clouds[8];
	//T_AI* sp_ai; //����npc��������Ϊ
	T_Menu *tp_menu;//���˵�
	T_Menunew *run_menu;//���˵�
	T_Menunew *pass_menu;//��һ�ز˵�
	T_Menunew *helpPlayer;//�����˵�
	/*T_Sprite  *missle_up;
	vSpriteSet missle_set;
	vSpriteSet explosion_set;*/
	T_Menunew *pause_menus[PAUSE_NUM+1];
	T_Menunew *level_menus[LEVEL_NUM];
	//audio******************************************
	AudioDX ds;//directsound ����
	//�ٶ���������������
	AudioDXBuffer backmusic_buffer;
	AudioDXBuffer walk_buffer;//������Ч
	AudioDXBuffer losehotdog_buffer;//�ȹ�������Ч
	AudioDXBuffer eathotdog_buffer;//���Ե���Ч
	AudioDXBuffer pass_buffer;//ͨ����Ч
	AudioDXBuffer mousedown_buffer;//����ƶ���Ч
	AudioDXBuffer mousemove_buffer;//�������Ч

	//*********************************************

//czy******************************************
	T_Sprite *hotDog;//�ȹ�
	int acc;//����ļ��ٶ�
	RECT dangong_rect;
	static POINT med_dangong;//���������ĵ�λ��
	bool click;//�ж��Ƿ���������
	bool pull;//�ж��Ƿ����˵��� falseû�����
	Velocity v;//�ٶ�
	T_Scene* scene;//�������ڶ�ȡtxt�ļ�����ȡ�ϰ����ͼ
	T_Map* levelmap;


	bool left_move;//true�ƶ�
	bool right_move;
	void LoadHotDog();
	void UpdateHotDogPos();
	void LoadLevel2();
	void LoadLevel3();
//*********************************************

	HBITMAP hbitmap;
	void LoadPlayer();
	/*void LoadCloud();*/
	//void LoadNpc(int num);
	void LoadTanHuang();
	//�������ֱ� ���˶��ٸ��ȹ� �ؿ�Ϊ����
	//void LoadScore();



	void UpdateFrames();//���¶���֡���к�
	void UpdatePos();//������ҽ�ɫ��npc��ɫλ��
	void LoadGameMenu(int type);
	void LoadPauseMenu(int num);//��Ϸ��ͣʱ�Ĳ˵�
	void LoadLevelMenu(int num);//��Ϸ�ؿ�
	void LoadGameScreen(int type);
	void PaintPauseMenu(HDC hdc);//����ͣ�Ľ���
	void InitMenuPara(wstring* menuItems, int itemNumber, int b_w, int b_h, int posType = 0);
	void DisplayInfo(HDC hdc, int game_state);
	void PaintScore(HDC hdc, wstring level, wstring hotdognum);//��ҳ���ϻ��������ȹ���Ŀ
	void LoadReplay();//���¿�ʼ
	/*void LoadMissle(int num);*/
	/*void UpdateMisslePos();*/
	/*void LoadExplosion(int x, int y);*/

};


