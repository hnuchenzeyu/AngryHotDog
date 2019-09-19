#pragma once
#include "TinyEngine\\T_AI.h"
#include "TinyEngine\\T_Graph.h"
#include "TinyEngine\\T_Sprite.h"
#include "TinyEngine\\T_Engine.h"
#include "TinyEngine\\T_Menu.h"
#include "TinyEngine\T_Menunew.h"
#include "TinyEngine\T_Scene.h"
#include "MyGraph.h"



//鱼的结构体 因为有很多条鱼所以构建结构体
//typedef struct 
//{
//	wstring filename;//角色动画文件
//	int wframe;//对应宽高
//	int hframe;
//}AIRCRAFTINFO;
typedef struct
{
	int Vx;
	int Vy;
}Velocity;
typedef struct
{
	wstring filename;//角色动画文件
	int wframe;//对应宽高
	int hframe;
}CLOUDINFO;
typedef struct
{
	wstring filename;//菜单图片
	int btnwidth;//对应宽高
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

	int wnd_width, wnd_height;	//游戏窗口宽高
	static const long T_LENGTH = 4500; //间隔时间
	
	static const int PAUSE_NUM = 5; //暂停时菜单按钮数量
	static const int LEVEL_NUM = 3+1;//关卡按钮数量为3,还有1个返回按钮
	//static CLOUDINFO cloud[8]; //保存角色动画文件名及帧图宽高 七个可以被随机抽取的鱼动画文件
	static PAUSEMENUINFO pmenu[PAUSE_NUM+1];
	static PAUSEMENUINFO lmenu[LEVEL_NUM];
	//static int sequence[8]; //重新定义玩家角色动画帧序列，使其适应更快的帧频
	POINT mousePT;//当前鼠标位置

	T_Graph* back;//背景图
	T_Graph* levelback;//背景图
	T_Graph* title;//主菜单页面的logo
	T_Graph* hamburger;//
	T_Graph* hotdogsmall;//热狗小标 分数标志
	T_Graph* scorelevel1;//level1的王思聪
	T_Graph* buttons;//button合集
	T_Graph* upgradeback;//下一关背景
	T_Graph* helpPlayerback;//帮助背景
	

	int ham_x, ham_y;//汉堡包的宽高
	int upgrademenu_w, upgrademenu_h, upgrademenu_x, upgrademenu_y;//下一个菜单的背景长宽和位置
	int caodi_height;//草地的高度
	int level=1;//关卡
	int pausemenu_width;//暂停页面的宽
	bool level1lock=true;//关卡1是否锁住了
	bool level2lock=true;//关卡2是否锁住了
	bool isplaysound = true;//是否播放音乐的判断值
	bool isfail = true;//是否失败了
	T_Sprite *player;
	T_Sprite* tanhuang;
	int hotdogcount;//接到热狗数
	//T_Sprite* clouds[8];
	//T_AI* sp_ai; //处理npc的智能行为
	T_Menu *tp_menu;//主菜单
	T_Menunew *run_menu;//主菜单
	T_Menunew *pass_menu;//下一关菜单
	T_Menunew *helpPlayer;//帮助菜单
	/*T_Sprite  *missle_up;
	vSpriteSet missle_set;
	vSpriteSet explosion_set;*/
	T_Menunew *pause_menus[PAUSE_NUM+1];
	T_Menunew *level_menus[LEVEL_NUM];
	//audio******************************************
	AudioDX ds;//directsound 对象
	//再多就做个数组或容器
	AudioDXBuffer backmusic_buffer;
	AudioDXBuffer walk_buffer;//行走音效
	AudioDXBuffer losehotdog_buffer;//热狗掉了音效
	AudioDXBuffer eathotdog_buffer;//被吃掉音效
	AudioDXBuffer pass_buffer;//通过音效
	AudioDXBuffer mousedown_buffer;//鼠标移动音效
	AudioDXBuffer mousemove_buffer;//鼠标点击音效

	//*********************************************

//czy******************************************
	T_Sprite *hotDog;//热狗
	int acc;//掉落的加速度
	RECT dangong_rect;
	static POINT med_dangong;//弹弓的中心点位置
	bool click;//判断是否按下鼠标左键
	bool pull;//判断是否拉了弹弓 false没有射出
	Velocity v;//速度
	T_Scene* scene;//场景用于读取txt文件来获取障碍层地图
	T_Map* levelmap;


	bool left_move;//true移动
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
	//加载评分表 吃了多少个热狗 关卡为多少
	//void LoadScore();



	void UpdateFrames();//更新动画帧序列号
	void UpdatePos();//更新玩家角色和npc角色位置
	void LoadGameMenu(int type);
	void LoadPauseMenu(int num);//游戏暂停时的菜单
	void LoadLevelMenu(int num);//游戏关卡
	void LoadGameScreen(int type);
	void PaintPauseMenu(HDC hdc);//画暂停的界面
	void InitMenuPara(wstring* menuItems, int itemNumber, int b_w, int b_h, int posType = 0);
	void DisplayInfo(HDC hdc, int game_state);
	void PaintScore(HDC hdc, wstring level, wstring hotdognum);//在页面上画分数和热狗数目
	void LoadReplay();//重新开始
	/*void LoadMissle(int num);*/
	/*void UpdateMisslePos();*/
	/*void LoadExplosion(int x, int y);*/

};


