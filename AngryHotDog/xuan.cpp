#include "xuan.h"
PAUSEMENUINFO xuan::pmenu[PAUSE_NUM+1] = {
	{L"playbutton.png", 88, 94}, {L"replaybutton.png", 92, 96}, 
{L"soundbutton.png", 92, 96}, {L"pausemenubutton.png", 92, 96}, 
{L"aboutbutton.png", 92, 96},{L"stop.png", 92, 96}

};
PAUSEMENUINFO xuan::lmenu[LEVEL_NUM] = {
	{L"guan1.png", 255,255}, {L"guan2.png", 255,255}, {L"guan33.png", 255,255},{L"goback.png",92,96}
};

POINT xuan::med_dangong = {131, 217}; //弹弓中心位置

xuan::xuan(HINSTANCE hInstance, LPCTSTR szWindowClass, LPCTSTR szTitle,
		   WORD Icon, WORD SmIcon, int iWidth, int iHeight) : T_Engine(hInstance, szWindowClass, szTitle, Icon, SmIcon)
{
	srand(GetTickCount());
	wnd_width = WIN_WIDTH;
	wnd_height = WIN_HEIGHT;
	caodi_height = 17 * wnd_height / 80;
	
}

xuan::~xuan()
{
}

void xuan::LoadPlayer()
{
	int x = 0;
	int y = 0;
	player = new T_Sprite(L"..\\res\\player1.png");
	SPRITEINFO spinfo;
	spinfo.Active = true;
	spinfo.Alpha = 255;
	spinfo.Dead = false;
	spinfo.Dir = DIR_RIGHT;
	spinfo.Level = 0;
	spinfo.Ratio = 0.7f;
	spinfo.Rotation = TRANS_NONE;
	spinfo.Score = 0;
	spinfo.Speed = 7;
	spinfo.Visible = true;
	player->Initiate(spinfo);
	x = (wnd_width - player->GetRatioSize().cx) / 2;			 //根据缩放比计算帧图片宽高/ 2 设置玩家在中心
	y = (wnd_height - player->GetRatioSize().cy) - caodi_height; //背景图片中含有草地
	player->SetPosition(x, y);
	player->AdjustCollideRect(-40, -5);
	//player->SetActive(false);
}

void xuan::LoadTanHuang()
{
	int x = 0;
	int y = 0;
	tanhuang = new T_Sprite(L"..\\res\\tanhuang.png", 100, 210);
	SPRITEINFO spinfo;
	spinfo.Active = true;
	spinfo.Alpha = 255;
	spinfo.Dead = false;
	spinfo.Dir = DIR_DOWN;
	spinfo.Level = 0;
	spinfo.Ratio = 0.7;
	spinfo.Rotation = TRANS_NONE;
	spinfo.Visible = true;
	tanhuang->Initiate(spinfo);
	x = 30 + ham_x / 2 - tanhuang->GetRatioSize().cx / 2;					  //在一开始就随机好
	y = wnd_height - caodi_height - ham_y - tanhuang->GetRatioSize().cy + 10; //在汉堡包上
	tanhuang->SetPosition(x, y);
	//npc[i]->SetSequence(sequence, 8);//设置帧序列
}
void xuan::LoadHotDog()
{
	int x, y;
	hotDog = new T_Sprite(L"..\\res\\hotdog.png");
	SPRITEINFO spinfo;
	spinfo.Active = true;
	spinfo.Alpha = 255;
	spinfo.Dead = false;
	spinfo.Dir = DIR_RIGHT;
	spinfo.Level = 0;
	spinfo.Ratio = 0.4f;
	spinfo.Rotation = TRANS_NOFLIP_ROT90;
	spinfo.Score = 0;
	spinfo.Speed = 0;
	spinfo.Visible = true;
	hotDog->Initiate(spinfo);
	x = 103;
	y = 181;
	hotDog->SetPosition(x, y);
	hotDog->AdjustCollideRect(-17, -5);
}
void xuan::LoadLevel2()
{
	scene = new T_Scene();
	scene->LoadTxtMap("..\\map\\level2.txt");
	levelmap = scene->getBarrier();
	levelmap->SetPosition(0, 0);
	if (back != NULL)
	{
		delete back;
		back = new T_Graph(L"..\\res\\bk2.png");
	}
	player->SetPosition((wnd_width - player->GetRatioSize().cx)/2, player->GetY());
	hotdogcount = 0;//吃到的热狗数为0
	level = 2;//关卡为2
	/*delete scene;
	scene = NULL;*/
}
void xuan::LoadLevel3()
{
	T_Scene *p = scene;
	scene = new T_Scene();
	scene->LoadTxtMap("..\\map\\level3.txt");
	levelmap = scene->getBarrier();
	levelmap->SetPosition(0, 0);
	if (back != NULL)
	{
		delete back;
		back = new T_Graph(L"..\\res\\bk3.png");
	}
	player->SetPosition((wnd_width - player->GetRatioSize().cx)/2, player->GetY());
	hotdogcount = 0;//吃到的热狗数为0
	level = 3;//关卡为3
	delete p;//删除上一个场景
}
void xuan::UpdateFrames()
{   
}
void xuan::UpdateHotDogPos()
{
	if (levelmap != NULL)
	{
		if (hotDog->CollideWith(levelmap))
		{
			v.Vx = -v.Vx;
		}
	}
	//x = 103;y = 181;
	if (hotDog->GetX() != 103 || hotDog->GetY() != 181)
	{
		hotDog->Move(v.Vx * 0.15, v.Vy * 0.15);
		v.Vy += acc;
	}
}
void xuan::UpdatePos()
{
	int x = player->GetX(), y = player->GetY();
	if (right_move)
	{
		player->Move(player->GetSpeed(), 0);
		if (player->GetX() > wnd_width - player->GetRatioSize().cx)
		{
			player->SetPosition(wnd_width - player->GetRatioSize().cx, player->GetY());
		}
		if (levelmap != NULL)
		{
			if (player->CollideWith(levelmap))
				player->SetPosition(x, y);
		}
	}
	if (left_move)
	{
		player->Move(-player->GetSpeed(), 0);
		if (player->GetX() < 0)
		{
			player->SetPosition(0, player->GetY());
		}
		if (levelmap != NULL)
		{
			if (player->CollideWith(levelmap))
				player->SetPosition(x, y);
		}
	}
}

void xuan::GameInit()
{
	GameState = GAME_START;
	tp_menu = NULL;
	scene = NULL;
	levelmap = NULL;
	player = NULL;
	back = NULL;
	tanhuang = NULL;
	click = false;
	pull = false;
	left_move = false;
	right_move = false;
	dangong_rect.left = 96;
	dangong_rect.top = 183;
	dangong_rect.right = 161;
	dangong_rect.bottom = 226;
	acc = 1;
	hotdogcount = 0;
	//加载音乐
	if (!ds.CreateDS(m_hWnd)) return;
	backmusic_buffer.LoadWave(ds, L"..\\sound\\backmusic.wav");
	walk_buffer.LoadWave(ds, L"..\\sound\\walking.wav");
	eathotdog_buffer.LoadWave(ds, L"..\\sound\\eathotdog.wav");
	losehotdog_buffer.LoadWave(ds, L"..\\sound\\losehotdog.wav");
	pass_buffer.LoadWave(ds, L"..\\sound\\pass.wav");
	mousedown_buffer.LoadWave(ds, L"..\\sound\\mousedown.wav");
	mousemove_buffer.LoadWave(ds, L"..\\sound\\mousemove.wav");
	backmusic_buffer.Play(true);

	if (tp_menu == NULL)
	{
		tp_menu = new T_Menu();
	}
	run_menu=new T_Menunew();
	run_menu->SetMenuIndex(-1);
	pass_menu = new T_Menunew();
	pass_menu->SetMenuIndex(-1);
	helpPlayer = new T_Menunew();
	helpPlayer->SetMenuIndex(-1);
	tp_menu->SetMenuIndex(-1);
	if (GameState == GAME_START)
	{
		LoadGameMenu(GAME_START);
		//加载标题logo
		title = new T_Graph(L"..\\res\\title.png");
	}
	if (GameState == GAME_RUN)
	{
		LoadGameMenu(GAME_RUN);
		LoadGameScreen(GAME_RUN);
	}
	if (GameState == GAME_ABOUT)
	{
		LoadGameMenu(GAME_ABOUT);
	}
	if (GameState == GAME_LEVEL)
	{
		LoadGameScreen(GAME_LEVEL);
		LoadGameMenu(GAME_LEVEL);
	}
	if (GameState == GAME_PAUSE)
	{
		LoadGameMenu(GAME_PAUSE);
	}
	if (GameState == GAME_UPGRADE)
	{
		LoadGameScreen(GAME_UPGRADE);
		LoadGameMenu(GAME_UPGRADE);
	}
	if (GameState == GAME_FAIL)
	{
		LoadGameScreen(GAME_FAIL);
		LoadGameMenu(GAME_FAIL);
	}
	if (GameState == GAME_HELP)
	{
		LoadGameScreen(GAME_HELP);
		LoadGameMenu(GAME_HELP);
	}
}

void xuan::GameLogic() //处理游戏中角色的状态更新
{
	if (GameState == GAME_RUN)
	{
		UpdateFrames(); //实现动画效果
		UpdatePos();	//实现角色的位置移动
		UpdateHotDogPos();//实现热狗的位置移动
		if (hotDog->CollideWith(player))
		{
			hotDog->SetPosition(103, 181);
			hotdogcount++;
			pull = false;
			eathotdog_buffer.Restore();
			eathotdog_buffer.Play(false);
		}
		if (hotdogcount == 5 && level!=3)
		{
			pass_buffer.Restore();
			pass_buffer.Play(false);
			T_Scene *p;
			T_Map *mp;
			switch (level)
			{
			case 1:
				level1lock = false;
				GameState = GAME_UPGRADE;
				LoadGameScreen(GAME_UPGRADE);
				LoadGameMenu(GAME_UPGRADE);
				LoadLevel2();
				break;
			case 2:
				level2lock = false;
				GameState = GAME_UPGRADE;
				LoadGameScreen(GAME_UPGRADE);
				LoadGameMenu(GAME_UPGRADE);
				LoadLevel3();
				break;
			default:
				break;
			}//下一关
		}
		if(level == 3)//第三关切换不同肚子大小的图片，速度减慢
		{
			switch (hotdogcount)
			{
			case 2:
				player->SetImage(new T_Graph(L"..\\res\\player1-1.png"));
				player->SetSpeed(5);
				break;
			case 4:
				player->SetImage(new T_Graph(L"..\\res\\player1-2.png"));
				player->SetSpeed(4);
				break;
			case 6:
				player->SetImage(new T_Graph(L"..\\res\\player1-3.png"));
				player->SetSpeed(3);
				break;
			default:
				break;
			}
		}
		
		if (hotDog->GetY() > 490)
		{
			losehotdog_buffer.Restore();
			losehotdog_buffer.Play(false);
			//isfail = true;
			GameState = GAME_FAIL;
			LoadGameScreen(GAME_FAIL);
			LoadGameMenu(GAME_FAIL);
			//失败
			pull = false;
		}
	}
}

void xuan::GameEnd()
{
	if (player != NULL)
		delete player;
	player = NULL;
	if (back != NULL)
		delete back;
	back = NULL;

	
	if (tanhuang != NULL)
		delete tanhuang;
	
}

void xuan::GamePaint(HDC hdc)
{
	if (GameState == GAME_START)
	{
		tp_menu->DrawMenu(hdc);
	}
	if (GameState == GAME_ABOUT)
	{
		tp_menu->DrawMenu(hdc);
	}
	if (GameState == GAME_RUN)
	{
		back->PaintImage(hdc, 0, 0, wnd_width, wnd_height, 150);
		//画汉堡包放弹弓
		hamburger->PaintImage(hdc, 30, wnd_height - caodi_height - ham_y, ham_x, ham_y, 255);
		if(levelmap!=NULL)
			levelmap->Draw(hdc);
		if (click)
		{
			MyGraph mg(hotDog);
			mg.Draw2Lines(hdc, mousePT); //画拉线
		}
		if (!click)
		{
			hotDog->Draw(hdc);
			MyGraph::DrawLine(hdc);
		}
		tanhuang->Draw(hdc);
		player->Draw(hdc);
		run_menu->DrawMenu(hdc);
	}
	if (GameState == GAME_UPGRADE)
	{
		upgradeback->PaintImage(hdc, upgrademenu_x, upgrademenu_y, upgrademenu_w, upgrademenu_h, 230);
		pass_menu->DrawMenu(hdc);
	}
	if (GameState == GAME_FAIL)
	{
		upgradeback->PaintImage(hdc, upgrademenu_x, upgrademenu_y, upgrademenu_w, upgrademenu_h, 230);
		pass_menu->DrawMenu(hdc);
	}
	if (GameState == GAME_HELP)
	{
		helpPlayerback->PaintImage(hdc, upgrademenu_x, upgrademenu_y, upgrademenu_w, upgrademenu_h, 230);
		helpPlayer->DrawMenu(hdc);
	}
	if (GameState == GAME_LEVEL)
	{
		levelback->PaintImage(hdc, 0, 0, wnd_width, wnd_height, 150);
		for (int i = 0; i < LEVEL_NUM; i++)
		{
			level_menus[i]->DrawMenu(hdc);
		}
	}
	if (GameState == GAME_PAUSE)
	{
		PaintPauseMenu(hdc);
		for (int i = 0; i < PAUSE_NUM; i++)
		{
			pause_menus[i]->DrawMenu(hdc);
			if (i == 2) {
				if (isplaysound == true)
				{
					pause_menus[i]->DrawMenu(hdc);
				}
				else if (isplaysound == false)
				{
					pause_menus[PAUSE_NUM]->DrawMenu(hdc);
				}
			}
		}
		
	}
	DisplayInfo(hdc, GameState);
}

void xuan::GameKeyAction(int Action)
{
	if (GameState == GAME_START)
	{
		if (GetAsyncKeyState(VK_UP) < 0)
		{
			tp_menu->MenuKeyDown(VK_UP);
		}
		if (GetAsyncKeyState(VK_DOWN) < 0)
		{
			tp_menu->MenuKeyDown(VK_DOWN);
		}
		if (GetAsyncKeyState(VK_LEFT) < 0)
		{
			tp_menu->MenuKeyDown(VK_LEFT);
		}
		if (GetAsyncKeyState(VK_RIGHT) < 0)
		{
			tp_menu->MenuKeyDown(VK_RIGHT);
		}
		if (GetAsyncKeyState(VK_RETURN) < 0)
		{
			if (tp_menu->GetMenuIndex() >= 0)
			{
				switch (tp_menu->GetMenuIndex())
				{
				case 0:
					GameState = GAME_RUN;
					break;
				case 1:
					GameState = GAME_ABOUT;
					break;
				case 2:
					SendMessage(m_hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
					break;
				default:
					break;
				}
			}
		}
	}

	if (GameState == GAME_ABOUT)
	{
		if (GetAsyncKeyState(VK_UP) < 0)
		{
			tp_menu->MenuKeyDown(VK_UP);
		}
		if (GetAsyncKeyState(VK_DOWN) < 0)
		{
			tp_menu->MenuKeyDown(VK_DOWN);
		}
		if (GetAsyncKeyState(VK_LEFT) < 0)
		{
			tp_menu->MenuKeyDown(VK_LEFT);
		}
		if (GetAsyncKeyState(VK_RIGHT) < 0)
		{
			tp_menu->MenuKeyDown(VK_RIGHT);
		}
		if (GetAsyncKeyState(VK_RETURN) < 0)
		{
			if (tp_menu->GetMenuIndex() >= 0)
			{
				switch (tp_menu->GetMenuIndex())
				{
				case 0:
					GameState = GAME_START;
					break;
				case 1:
					GameState = GAME_RUN;
					break;
				case 2:
					SendMessage(m_hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
					break;
				default:
					break;
				}
			}
		}
	}
	if (GameState == GAME_RUN)
	{
		if (Action == KEY_DOWN)
		{
			if (GetKeyState(VK_RIGHT) < 0)
			{
				player->SetDir(DIR_RIGHT);
				player->SetRotation(TRANS_NONE);
				right_move = true;
				walk_buffer.Restore();
				walk_buffer.Play(false);
			}
			if (GetKeyState(VK_LEFT) < 0)
			{
				player->SetDir(DIR_LEFT);
				player->SetRotation(TRANS_HFLIP_NOROT);
				left_move = true;
				walk_buffer.Restore();
				walk_buffer.Play(false);
			}
		}

		if (Action == KEY_UP)
		{
			player->SetActive(false);
			left_move = false;
			right_move = false;
		}
	}
}

void xuan::GameMouseAction(int x, int y, int Action)
{
	
	if (Action == MOUSE_MOVE && GameState != GAME_RUN && GameState != GAME_PAUSE && GameState != GAME_LEVEL && GameState != GAME_UPGRADE && GameState != GAME_FAIL)
	{
		tp_menu->MenuMouseMove(x, y);
	}
	else if (Action == MOUSE_MOVE && GameState == GAME_UPGRADE && GameState == GAME_FAIL)
	{	
		pass_menu->MenuMouseMove(x, y);
	}
	else if (Action == MOUSE_MOVE && GameState == GAME_HELP)
	{
		helpPlayer->MenuMouseMove(x, y);
	}
	else if (Action == MOUSE_MOVE && GameState == GAME_RUN )
	{	//啦弹弓
		run_menu->MenuMouseMove(x, y);
		if (click == true)
		{
			if (pow(x - med_dangong.x, 2) + pow(y - med_dangong.y, 2) < 22500)
			{
				mousePT.x = x;
				mousePT.y = y;
			}
			else
			{
				int x1, y1;
				x1 = x - med_dangong.x;
				y1 = y - med_dangong.y;
				double k = double(y1) / (x1);
				double theta = atan(k);
				if (x1 != 0)
				{
					if (x1 > 0)
					{
						mousePT.x = 150 * cos(theta) + med_dangong.x;
						mousePT.y = 150 * sin(theta) + med_dangong.y;
					}
					else
					{
						mousePT.x = -150 * cos(theta) + med_dangong.x;
						mousePT.y = -150 * sin(theta) + med_dangong.y;
					}
				}
				else if (y1 > 0)
				{
					mousePT.y = 150;
				}
				else if (y1 < 0)
				{
					mousePT.y = -150;
				}
			}
			hotDog->SetPosition(mousePT.x, mousePT.y);
		}
	}
	else if (Action == MOUSE_MOVE && GameState == GAME_PAUSE)
	{
		for (int i = 0; i < PAUSE_NUM; i++)
		{
			pause_menus[i]->MenuMouseMove(x, y);
		}
	}
	else if (Action == MOUSE_MOVE && GameState == GAME_LEVEL)
	{
		for (int i = 0; i < LEVEL_NUM; i++)
		{
			level_menus[i]->MenuMouseMove(x, y);
		}
	}
	else if (Action == MOUSE_LUP && GameState == GAME_RUN && click==true)
	{	//释放弹弓
		click = false;
		v.Vx = (med_dangong.x - mousePT.x) / 1.2 + 1;
		v.Vy = (med_dangong.y - mousePT.y) / 1.2 + 1;
	}
	else if (Action == MOUSE_LCLICK)
	{
		if (GameState == GAME_START)
		{
			int index = tp_menu->MenuMouseClick(x, y);
			if (index >= 0)
			{
				switch (index)
				{
				case 0:
					delete tp_menu;
					tp_menu = NULL;
					LoadGameScreen(GAME_LEVEL);
					LoadGameMenu(GAME_LEVEL);
					GameState = GAME_LEVEL;
					break;
				case 1:
					delete tp_menu;
					tp_menu = NULL;
					LoadGameMenu(GAME_ABOUT);
					GameState = GAME_ABOUT;
					break;
				case 2:
					SendMessage(m_hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
					break;
				}
			}
		}
		else if (GameState == GAME_LEVEL)
		{
			for (int i = 0; i < LEVEL_NUM; i++)
			{
				int index = level_menus[i]->MenuMouseClick(x, y);
				if (index >= 0)
				{
					switch (i)
					{
					case 0:						
						delete levelback;
						levelback = NULL;
						GameState = GAME_RUN;
						LoadGameScreen(GAME_RUN);
						LoadGameMenu(GAME_RUN);						
						break;
					case 1:
						if(level1lock == false)
						{ 
						delete levelback;
						levelback = NULL;
						/*LoadGameScreen(GAME_RUN);
						LoadGameMenu(GAME_RUN);*/
						GameState = GAME_RUN;
						}
						break;
					case 2:
						if (level2lock == false)
						{
						delete levelback;
						levelback = NULL;
						/*LoadGameScreen(GAME_RUN);
						LoadGameMenu(GAME_RUN);*/
						GameState = GAME_RUN;
						}
						break;
					case 3:
						{
						GameState = GAME_START;
						delete tp_menu;
						tp_menu = NULL;
						LoadGameMenu(GAME_START);
						}
						break;
					}								
				/*	delete level_menus[i];
					level_menus[i] = NULL;*/
				}
			}
		}
		else if (GameState == GAME_ABOUT)
		{
			int index = tp_menu->MenuMouseClick(x, y);
			if (index >= 0)
			{
				switch (index)
				{
				case 0:
					GameState = GAME_START;
					delete tp_menu;
					tp_menu = NULL;
					LoadGameMenu(GAME_START);

					break;
				case 1:
					GameState = GAME_RUN;
					delete tp_menu;
					tp_menu = NULL;
					/*LoadGameScreen(GAME_RUN);
					LoadGameMenu(GAME_RUN);*/
					break;
				case 2:
					SendMessage(m_hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
					break;
				}
			}
		}
		else if (GameState == GAME_UPGRADE)
		{
			int index = pass_menu->MenuMouseClick(x, y);
			if (index >= 0)
			{
				switch (index)
				{
				case 0:
					LoadGameScreen(GAME_LEVEL);
					LoadGameMenu(GAME_LEVEL);
					GameState = GAME_LEVEL;	
					delete pass_menu;
					pass_menu = NULL;
					break;
				case 1:
					GameState = GAME_RUN;
					/*LoadGameScreen(GAME_RUN);
					LoadGameMenu(GAME_RUN);*/
					delete pass_menu;
					pass_menu = NULL;
					break;
				}
			}
		}
		else if (GameState == GAME_FAIL)
		{
			left_move = false;
			right_move = false;
			int index = pass_menu->MenuMouseClick(x, y);
			if (index >= 0)
			{
				switch (index)
				{
				case 0:
				LoadGameScreen(GAME_LEVEL);
				LoadGameMenu(GAME_LEVEL);
				GameState = GAME_LEVEL;
				delete pass_menu;
				pass_menu = NULL;
				break;
				case 1:
				LoadReplay();
				break;
				}
			}
		}
		else if (GameState == GAME_HELP)
		{
			left_move = false;
			right_move = false;
			int index = helpPlayer->MenuMouseClick(x, y);
			if (index >= 0)
			{
				switch (index)
				{
				case 0:
					GameState = GAME_RUN;
					/*LoadGameScreen(GAME_RUN);
					LoadGameMenu(GAME_RUN);*/
					delete helpPlayer;
					helpPlayer = NULL;
					break;
				}
			}
		}
		else if (GameState == GAME_RUN)
		{
			//游戏
			POINT m;
			m.x = x;
			m.y = y;
			if (PtInRect(&dangong_rect, m)&& pull==false) //鼠标点在弹弓里
			{
				mousePT.x = x;
				mousePT.y = y;
				click = true;
				pull = true;
			}
			//菜单
			int index = run_menu->MenuMouseClick(x, y);
			if (index >= 0)
			{
				switch (index)
				{
				case 0:
					GameState = GAME_PAUSE;
					
					LoadPauseMenu(PAUSE_NUM);
					break;
				}
			}
		}
		else if (GameState == GAME_PAUSE)
		{
			for (int i = 0; i < PAUSE_NUM; i++)
			{
				int index = pause_menus[i]->MenuMouseClick(x, y);
				if (index >= 0)
				{
					switch (i)
					{
					case 0:
						GameState = GAME_RUN;
						///*delete pause_menus[i];
						//pause_menus[i] = NULL;*/
						//LoadGameScreen(GAME_RUN);
						//LoadGameMenu(GAME_RUN);
						break;
					case 1:
						LoadReplay();
						
						break;
					case 2:
						//音乐播放的判断可以写成函数
						if(isplaysound==true)
						{ 
						backmusic_buffer.Stop(); 				
						if(pass_buffer.IsAlive()==true)
						{ 
							bool a = pass_buffer.IsAlive();
							pass_buffer.Release();
						}
						if (losehotdog_buffer.IsAlive() == true)
						{
							losehotdog_buffer.Release();
						}
						if (eathotdog_buffer.IsAlive() == true)
						{
							eathotdog_buffer.Release();
						}
						if (walk_buffer.IsAlive() == true)
						{
							walk_buffer.Release();
						}
						if (mousedown_buffer.IsAlive() == true)
						{
							mousedown_buffer.Release();
						}
						if (mousemove_buffer.IsAlive() == true)
						{
							mousemove_buffer.Release();
						}
						isplaysound = false;
						}
						else if (isplaysound == false)
						{
							backmusic_buffer.Restore();
							backmusic_buffer.Play(true);
							walk_buffer.LoadWave(ds, L"..\\sound\\walking.wav");
							eathotdog_buffer.LoadWave(ds, L"..\\sound\\eathotdog.wav");
							losehotdog_buffer.LoadWave(ds, L"..\\sound\\losehotdog.wav");
							pass_buffer.LoadWave(ds, L"..\\sound\\pass.wav");
							mousedown_buffer.LoadWave(ds, L"..\\sound\\mousedown.wav");
							mousemove_buffer.LoadWave(ds, L"..\\sound\\mousemove.wav");
							isplaysound = true;
						}
						break;
					case 3:
						LoadGameScreen(GAME_LEVEL);
						LoadGameMenu(GAME_LEVEL);
						GameState = GAME_LEVEL;
						break;
					case 4:
						LoadGameScreen(GAME_HELP);
						LoadGameMenu(GAME_HELP);
						GameState = GAME_HELP;
						break;
					}
					//delete pause_menus[i];
					//pause_menus[i] = NULL;
				}
			}
		}
	}
}
void xuan::LoadGameMenu(int type)
{
	tp_menu = new T_Menu();
	tp_menu->SetMenuIndex(-1);
	run_menu = new T_Menunew();
	run_menu->SetMenuIndex(-1);
	pass_menu = new T_Menunew();
	pass_menu->SetMenuIndex(-1);
	helpPlayer = new T_Menunew();
	helpPlayer->SetMenuIndex(-1);
	if (type == GAME_START)
	{
		wstring menuItems[] = {L"新游戏", L"关于", L"退出游戏"};
		int btn_width = 249;
		int btn_height = 50.5;

		tp_menu->SetMenuBkg(L"..\\res\\menubkg.png");
		tp_menu->SetBtnBmp(L"..\\res\\menubutton.png", btn_width, btn_height);
		InitMenuPara(menuItems, 3, btn_width, btn_height, 0);
	}
	if (type == GAME_ABOUT)
	{
		wstring menuItems[] = {L"返回  ", L"开始  ", L"退出  "};
		int btn_width = 0, btn_height = 0;
		btn_width = 132;
		btn_height = 132;
		tp_menu->SetMenuBkg(L"..\\res\\levelbkg.jpg");
		tp_menu->SetBtnBmp(L"..\\res\\upgradebutton.png", btn_width, btn_height);
		InitMenuPara(menuItems, 3, btn_width, btn_height, 1);
	}
	if (type == GAME_RUN)
	{
		wstring menuItems[] = {L""};
		int btn_width = 0, btn_height = 0;
		btn_width = 88;
		btn_height = 94;
		run_menu->SetBtnBmp(L"..\\res\\pausebutton.png", btn_width, btn_height);
		InitMenuPara(menuItems, 1, btn_width, btn_height, 2);
	}
	if (type == GAME_UPGRADE)
	{
		wstring menuItems[] = { L"返回  ",L"下一关  " };
		int btn_width = 0, btn_height = 0;
		btn_width = 132;
		btn_height = 132;
		pass_menu->SetBtnBmp(L"..\\res\\upgradebutton.png", btn_width, btn_height);
		InitMenuPara(menuItems, 2, btn_width, btn_height, 3);
	}
	if(type == GAME_FAIL)
	{
		wstring menuItems[] = { L"返回菜单",L"重新开始" };
		int btn_width = 0, btn_height = 0;
		btn_width = 132;
		btn_height = 132;
		pass_menu->SetBtnBmp(L"..\\res\\upgradebutton.png", btn_width, btn_height);
		InitMenuPara(menuItems, 2, btn_width, btn_height, 5);
	}
	if (type == GAME_HELP)
	{
		wstring menuItems[] = { L"确定  " };
		int btn_width = 0, btn_height = 0;
		btn_width = 132;
		btn_height = 132;
		helpPlayer->SetBtnBmp(L"..\\res\\upgradebutton.png", btn_width, btn_height);
		InitMenuPara(menuItems, 1, btn_width, btn_height, 4);
	}
	if (type == GAME_LEVEL)
	{
		LoadLevelMenu(LEVEL_NUM);
	}
	if (type == GAME_PAUSE)
	{
		LoadPauseMenu(PAUSE_NUM);
	}
	tp_menu->SetClickSound(&mousedown_buffer);
	tp_menu->SetMoveSound(&mousemove_buffer);
	run_menu->SetClickSound(&mousedown_buffer);
	run_menu->SetMoveSound(&mousemove_buffer);
	pass_menu->SetClickSound(&mousedown_buffer);
	pass_menu->SetMoveSound(&mousemove_buffer);
}
void xuan::LoadGameScreen(int type)
{
	if (type == GAME_RUN)
	{
		back = new T_Graph(L"..\\res\\gamebkg1.png");
		hamburger = new T_Graph(L"..\\res\\hamburger.png");
		//初始化汉堡包大小
		ham_x = 216;
		ham_y = 168;
		//加载热狗的图片
		hotdogsmall = new T_Graph(L"..\\res\\hotdogsmall.png");
		//加载王思聪的第一关的图片
		scorelevel1 = new T_Graph(L"..\\res\\scorelevel1.png");
		//加载buttons
		buttons = new T_Graph(L"..\\res\\buttons.png");
		LoadPlayer();
		LoadTanHuang();
		LoadHotDog();
		/*LoadCloud();*/
	}
	if (type == GAME_LEVEL)
	{
		levelback = new T_Graph(L"..\\res\\levelbkg.jpg");
	}
	if (type == GAME_FAIL)
	{
		upgradeback = new T_Graph(L"..\\res\\upgradebkg.png");
		upgrademenu_x = wnd_width / 3;
		upgrademenu_y = wnd_height / 4;
		upgrademenu_w = 400;
		upgrademenu_h = 268;
	}
	if (type == GAME_UPGRADE)
	{
		upgradeback = new T_Graph(L"..\\res\\upgradebkg.png");
		upgrademenu_x = wnd_width / 3;
		upgrademenu_y = wnd_height / 4;
		upgrademenu_w = 400;
		upgrademenu_h = 268;

	}
	if (type == GAME_HELP)
	{
		helpPlayerback = new T_Graph(L"..\\res\\upgradebkg.png");
		upgrademenu_x = wnd_width / 3;
		upgrademenu_y = wnd_height / 4;
		upgrademenu_w = 400;
		upgrademenu_h = 268;
	}
}
void xuan::InitMenuPara(wstring *menuItems, int itemNumber, int b_w, int b_h, int posType)
{
	int x = 0;
	int y = 0;
	for (int i = 0; i < itemNumber; i++)
	{
		switch (posType)
		{
		case 0:
		{
			x = (wnd_width - b_w) / 2;
			//减去了title的高除以2 可以考虑设置为变量如果利用次数较多的画
			y = i * (b_h + MENU_SPACE * 1.5) + (wnd_height - itemNumber * 100 - (itemNumber - 1) * MENU_SPACE * 1.5) / 2 + 250 / 2; //可改进 设置菜单项的位置
			break;
		}
		case 1:
		{
			x = wnd_width / 6 + i * (b_w + MENU_SPACE * 2) + (wnd_height - 3 * b_w - 3 * MENU_SPACE) / 2;
			y = wnd_height - 2 * b_h;
			break;
		}
		case 2:
		{
			x = 30;
			y = 0;
			break;
		}
		case 3:
		{
			x = upgrademenu_x + b_w / 2 + (i)*(upgrademenu_w - b_w * 2);
			y = upgrademenu_y + upgrademenu_h - b_h;
			break;
		}
		case 4://帮助菜单
		{
			x = upgrademenu_x + ((upgrademenu_w - b_w) / 2);
			y = upgrademenu_y + upgrademenu_h - b_h;//位置和下一关一样
			break;
		}
		case 5:
		{
			x = upgrademenu_x + b_w / 2 + (i)*(upgrademenu_w - b_w * 2);
			y = upgrademenu_y + upgrademenu_h - b_h;
			break;
		}
		}
		MENUITEM mItem;
		mItem.pos.x = x;
		mItem.pos.y = y;
		mItem.ItemName = menuItems[i];		
		if (posType == 2)
		{
			mItem.ItemName = L"";
			run_menu->AddMenuItem(mItem);
		}
		if (posType == 3 || posType == 5)
		{
			pass_menu->AddMenuItem(mItem);
		}
		if (posType == 4)
		{
			helpPlayer->AddMenuItem(mItem);
		}
		else
		{
			tp_menu->AddMenuItem(mItem);
		}
	}
	Color normalClr, focusClr;
	normalClr = Color::White;
	focusClr = Color::Yellow;
	MENU_INFO menuInfo;
	menuInfo.align = 1;
	menuInfo.space = MENU_SPACE;
	menuInfo.width = b_w;
	menuInfo.height = b_h;
	menuInfo.fontName = L"黑体";
	menuInfo.isBold = true;
	menuInfo.normalTextColor = normalClr;
	menuInfo.focusTextColor = focusClr;
	tp_menu->SetMenuInfo(menuInfo);
	run_menu->SetMenuInfo(menuInfo);
	pass_menu->SetMenuInfo(menuInfo);
	helpPlayer->SetMenuInfo(menuInfo);
}
void xuan::DisplayInfo(HDC hdc, int game_state)
{
	int FontHeight = 0;
	Gdiplus::RectF rect;
	wstring Content = L"";
	rect.X = 50.00;
	rect.Width = 768.00;
	switch (game_state)
	{
	case GAME_START:
	{
		Gdiplus::RectF versionrect;
		versionrect.Width = 300;
		versionrect.Height = 60;
		versionrect.X = wnd_width - versionrect.Width;
		versionrect.Y = wnd_height - versionrect.Height;
		FontHeight = 14;
		T_Graph::PaintText(hdc, versionrect, L"愤怒的热狗 version1.0", (REAL)FontHeight, L"黑体", Color::White);
		break;
	}
	case GAME_RUN:
	{
		PaintScore(hdc, to_wstring(level), to_wstring(hotdogcount));
		break;
	}
	case GAME_ABOUT:
	{
		int FontHeight = 0;
		Gdiplus::RectF aboutrect, inforect1, inforect2, inforect3;
		wstring Content = L"";
		aboutrect.X = 30.00;
		aboutrect.Y = 0.00;
		aboutrect.Width = (float)wnd_width;
		aboutrect.Height = (float)wnd_height / 3;
		FontHeight = 24;
		T_Graph::PaintText(hdc, aboutrect, L"关于", (REAL)FontHeight, L"黑体", Color::Black);
		inforect1.X = wnd_width / 6;
		inforect1.Y = wnd_height / 4;
		inforect1.Width = WIN_WIDTH / 5;
		inforect1.Height = wnd_height / 3;

		inforect2.X = inforect1.X + inforect1.Width + 10;
		inforect2.Y = wnd_height / 4;
		inforect2.Width = WIN_WIDTH / 5;
		inforect2.Height = wnd_height / 3;

		inforect3.X = inforect2.X + inforect1.Width + 10;
		inforect3.Y = wnd_height / 4;
		inforect3.Width = WIN_WIDTH / 5;
		inforect3.Height = wnd_height / 3;
		FontHeight = 15;

		T_Graph::PaintBlank(hdc, inforect1.X, inforect1.Y, inforect1.Width, inforect1.Height, Color::White, 100);
		T_Graph::PaintText(hdc, inforect1,
			L" 姓名：徐钰涵\n 班级：软工167班\n 学号：8000116202\n 时间：2018年1月7日",
			(REAL)FontHeight, L"黑体", Color::White, FontStyleBold, StringAlignmentNear);


		T_Graph::PaintBlank(hdc, inforect2.X, inforect2.Y, inforect2.Width, inforect2.Height, Color::White, 100);
		T_Graph::PaintText(hdc, inforect2,
			L" 姓名：陈泽宇\n 班级：软工167\n 学号：8000116216\n 时间：2018年1月7日",
			(REAL)FontHeight, L"黑体", Color::White, FontStyleBold, StringAlignmentNear);


		T_Graph::PaintBlank(hdc, inforect3.X, inforect3.Y, inforect3.Width, inforect3.Height, Color::White, 100);
		T_Graph::PaintText(hdc, inforect3,
			L" 姓名：张悦\n 班级：软工1614班\n 学号8000116433\n 时间：2018年1月7日",
			(REAL)FontHeight, L"黑体", Color::White, FontStyleBold, StringAlignmentNear);
		break;
	}
	case GAME_UPGRADE:
	{
		Gdiplus::RectF versionrect;
		versionrect.Width = 200;
		versionrect.Height = 60;
		versionrect.X = upgrademenu_x+upgrademenu_w/4;
		versionrect.Y = upgrademenu_y+ upgrademenu_y/2;
		FontHeight = 22;
		T_Graph::PaintText(hdc, versionrect, L"闯关成功", (REAL)FontHeight, L"黑体", Color::Black,FontStyleBold,StringAlignmentCenter);
		break;
	}
	case GAME_HELP:
	{
		Gdiplus::RectF versionrect;
		versionrect.Width = 280;
		versionrect.Height = 125;
		versionrect.X = upgrademenu_x + (upgrademenu_w - versionrect.Width) / 2;
		versionrect.Y = upgrademenu_y + (upgrademenu_h - versionrect.Height) / 2;
		FontHeight = 14;
		T_Graph::PaintText(hdc, versionrect, L"  在弹弓线上按住左键鼠标并拖动就可以拉动弹弓，松开左键就可以发射热狗啦！\n  左右方向键移动王思聪来吃到热狗~", (REAL)FontHeight, L"黑体", Color::Black, FontStyleBold, StringAlignmentNear);
		break;
	}
	case GAME_FAIL:
	{
		Gdiplus::RectF versionrect;
		versionrect.Width = 200;
		versionrect.Height = 60;
		versionrect.X = upgrademenu_x + upgrademenu_w / 4;
		versionrect.Y = upgrademenu_y + upgrademenu_y / 2;
		FontHeight = 22;
		T_Graph::PaintText(hdc, versionrect, L"游戏失败", (REAL)FontHeight, L"黑体", Color::Black, FontStyleBold, StringAlignmentCenter);
		break;
	}
	}
}
void xuan::PaintScore(HDC hdc, wstring level, wstring hotdognum)
{
	RectF textRec; //关卡的绘制矩形区域
	textRec.X = (float)wnd_width / 4;
	textRec.Y = 0.00;
	textRec.Width = (float)wnd_width / 4;
	textRec.Height = (float)wnd_height / 8;
	//定义关卡字符串
	wstring guanqia = L"关卡 X";
	guanqia.append(level);
	T_Graph::PaintText(hdc, textRec, guanqia, 24, L"黑体", Color::White, FontStyleBold, StringAlignmentCenter);
	hotdogsmall->PaintImage(hdc, textRec.X + textRec.Width, 0, 40, 72, 255);
	RectF textRec2; //热狗数的绘制的矩形区域
	textRec2.X = textRec.X + textRec.Width + 64;
	textRec2.Y = 0.00;
	textRec2.Width = (float)wnd_width / 4;
	textRec2.Height = (float)wnd_height / 8;
	wstring hotdogs = L"X";
	hotdogs.append(hotdognum);
	T_Graph::PaintText(hdc, textRec2, hotdogs, 24, L"黑体", Color::White, FontStyleBold, StringAlignmentNear);
}

void xuan::LoadPauseMenu(int num)
{
	int x = 0;
	int y = 0;
	for (int i = 0; i < num+1; i++)
	{
		wstring path = L"..\\res\\";
		path.append(pmenu[i].filename);
		pause_menus[i] = new T_Menunew();
		pause_menus[i]->SetMenuIndex(-1);
		if(i == num )
		{
			pause_menus[i]->SetBtnBmp(path.c_str(), pmenu[i].btnwidth, pmenu[i].btnheight);
			y = wnd_height / 16 + 2 * pmenu[i].btnheight + MENU_SPACE * 2;
		}
		else{
			pause_menus[i]->SetBtnBmp(path.c_str(), pmenu[i].btnwidth, pmenu[i].btnheight);
			y = wnd_height / 16 + i * pmenu[i].btnheight + MENU_SPACE * 2;
			
		}
		//加载每个menu的详细信息
		x = wnd_width / 20;
		
		MENUITEM mItem;
		mItem.pos.x = x;
		mItem.pos.y = y;
		mItem.ItemName = L"";
		pause_menus[i]->AddMenuItem(mItem);

		Color normalClr, focusClr;
		normalClr = Color::White;
		focusClr = Color::Yellow;
		MENU_INFO menuInfo;
		menuInfo.align = 1;
		menuInfo.space = MENU_SPACE;
		menuInfo.width = pmenu[i].btnwidth;
		menuInfo.height = pmenu[i].btnheight;
		menuInfo.fontName = L"黑体";
		menuInfo.isBold = true;
		menuInfo.normalTextColor = normalClr;
		menuInfo.focusTextColor = focusClr;
		pause_menus[i]->SetMenuInfo(menuInfo);
		pause_menus[i]->SetMenuInfo(menuInfo);
		pause_menus[i]->SetClickSound(&mousedown_buffer);
		pause_menus[i]->SetMoveSound(&mousemove_buffer);
	}
}
void xuan::PaintPauseMenu(HDC hdc)
{
	Gdiplus::RectF inforect, linerect;
	inforect.X = 0;
	inforect.Y = 0;
	inforect.Width = (float)(WIN_WIDTH / 6);
	//确定暂停页面的宽
	pausemenu_width = inforect.Width;
	inforect.Height = WIN_HEIGHT;
	T_Graph::PaintBlank(hdc, inforect.X, inforect.Y, inforect.Width, inforect.Height, RGB(37, 159, 94), 180);
	linerect.X = inforect.Width;
	linerect.Y = 0;
	linerect.Width = inforect.Width / 8;
	linerect.Height = inforect.Height;
	T_Graph::PaintBlank(hdc, linerect.X, linerect.Y, linerect.Width, linerect.Height, Color::White, 180);
}
void xuan::LoadLevelMenu(int num)
{
	int x = 0;
	int y = 0;

	for (int i = 0; i < num; i++)
	{
		wstring path = L"..\\res\\";
		path.append(lmenu[i].filename);
		level_menus[i] = new T_Menunew();
		level_menus[i]->SetMenuIndex(-1);
			if (level1lock == false && i == 1)
		{
			level_menus[i]->SetBtnBmp(L"..\\res\\guan22.png", lmenu[i].btnwidth, lmenu[i].btnheight);
		}
		if (level2lock == false && i == 2)
		{
			level_menus[i]->SetBtnBmp(L"..\\res\\guan3.png", lmenu[i].btnwidth, lmenu[i].btnheight);
		}
		if (level2lock == false && i == 3)
		{
			level_menus[i]->SetBtnBmp(L"..\\res\\goback.png", lmenu[i].btnwidth, lmenu[i].btnheight);
		}
		else 
		{
			level_menus[i]->SetBtnBmp(path.c_str(), lmenu[i].btnwidth, lmenu[i].btnheight);

		}
		//加载每个menu的详细信息
		if (i == 3)
		{
			x = 73;
			y = 54;
		}
		else
		{
			x = wnd_width / 16 + MENU_SPACE * 2 + i * lmenu[i].btnwidth;
			y = wnd_height / 4;
		}
		MENUITEM mItem;
		mItem.pos.x = x;
		mItem.pos.y = y;
		mItem.ItemName = L"";
		level_menus[i]->AddMenuItem(mItem);

		Color normalClr, focusClr;
		normalClr = Color::White;
		focusClr = Color::Yellow;
		MENU_INFO menuInfo;
		menuInfo.align = 1;
		menuInfo.space = MENU_SPACE;
		menuInfo.width = lmenu[i].btnwidth;
		menuInfo.height = lmenu[i].btnheight;
		menuInfo.fontName = L"黑体";
		menuInfo.isBold = true;
		menuInfo.normalTextColor = normalClr;
		menuInfo.focusTextColor = focusClr;
		level_menus[i]->SetMenuInfo(menuInfo);
		level_menus[i]->SetMenuInfo(menuInfo);
		level_menus[i]->SetClickSound(&mousedown_buffer);
		level_menus[i]->SetMoveSound(&mousemove_buffer);
	}
}

void xuan::LoadReplay()
{
	level = 1;
	hotdogcount = 0;
	if (levelmap != NULL)
		delete levelmap;
	levelmap = NULL;
	LoadGameScreen(GAME_RUN);
	LoadGameMenu(GAME_RUN);
	GameState = GAME_RUN;
}
