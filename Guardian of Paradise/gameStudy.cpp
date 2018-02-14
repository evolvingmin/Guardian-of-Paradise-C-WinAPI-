#include "stdafx.h"
#include "gameStudy.h"

gameStudy::gameStudy()
{
}


gameStudy::~gameStudy()
{
}

//////////////////////////////////////////////////
////////// 더 이 상 생 성 자 와 소 멸 자는 쓰지 않는다/
//////////////////////////////////////////////////

//초기화 하는 곳
HRESULT gameStudy::init()
{
	gameNode::init(true);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////타일이미지//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	char sResult[128];
	char sResult_bmp[128];
	char sScaleResult[128];
	for (int i = 0; i < TILESETNUMBER; i++)
	{
		
		sprintf(sResult, "t_%d", i);
		if (i<6)
			sprintf(sResult_bmp, "Image/tileSet/t_%d_editer.bmp", i);
		else
			sprintf(sResult_bmp, "Image/tileSet/t_%d.bmp", i);

		sprintf(sScaleResult, "multiply_t_%d", i);
		 IMAGEMANAGER->addFrameImage(sResult, sResult_bmp, 320, 640, 10, 20, true, RGB(255, 0, 255));
		 sprintf(sResult_bmp, "Image/tileSet/t_%d.bmp", i);
		 IMAGEMANAGER->addFrameImage(sScaleResult, sResult_bmp, 320 * MULTIPLY_X, 640 * MULTIPLY_Y, 10, 20, true, RGB(255, 0, 255));
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////UI/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	IMAGEMANAGER->addImage("BasicBackGroundImage", "Image/CG/BasicBackGround.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("elementBackGround", "Image/UI/elementBackGround.bmp", 61 * MULTIPLY_X, 48 * MULTIPLY_Y, true, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("StateLable", "Image/UI/StateLable.bmp", 17 * MULTIPLY_X, 15 * MULTIPLY_Y, true, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("StateLable_enemy", "Image/UI/StateLable_enemy.bmp", 36 * MULTIPLY_X, 7 * MULTIPLY_Y, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("ElementChange", "Image/UI/ElementChange.bmp", 43 * MULTIPLY_X, 32 * MULTIPLY_Y,1,2, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("ElementSelect", "Image/UI/elementSelect.bmp", 192 * MULTIPLY_X, 32 * MULTIPLY_Y, 6, 1, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("ElementSkill", "Image/UI/ElementSkill.bmp", 72 * MULTIPLY_X, 80 * MULTIPLY_Y, 3, 6, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("QuestItem", "Image/UI/QuestItem.bmp", 128 * MULTIPLY_X, 16 * MULTIPLY_Y, 8, 1, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("StatusBar", "Image/UI/StatusBar.bmp", 8 * MULTIPLY_X, 24 * MULTIPLY_Y, 2 ,3, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("CGs", "Image/CG/CGs.bmp", 5600 , 8000 , 4, 10, false, RGB(0, 0, 0));
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////오브젝트 이미지 .///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//쥔공
	IMAGEMANAGER->addFrameImage("hero_attack_down", "Image/object/attack_frame_down.bmp", 63 * MULTIPLY_X, 56 * MULTIPLY_Y, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("hero_attack_left", "Image/object/attack_frame_left.bmp", 159 * MULTIPLY_X, 46 * MULTIPLY_Y, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("hero_attack_right", "Image/object/attack_frame_right.bmp", 168 * MULTIPLY_X, 46 * MULTIPLY_Y, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("hero_attack_up", "Image/object/attack_frame_up.bmp", 96 * MULTIPLY_X, 32 * MULTIPLY_Y, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("multiply_Hero", "Image/object/Hero.bmp", 320 * MULTIPLY_X, 352 * MULTIPLY_Y, 10, 11, true, RGB(255, 0, 255));

	// 오브젝트

	IMAGEMANAGER->addFrameImage("multiply_smalleffectObject", "Image/object/smallEffect.bmp", 320 * MULTIPLY_X, 128 * MULTIPLY_Y, 20, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("itemObject", "Image/object/Object_Item.bmp", 320, 96, 10, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("multiply_itemObject", "Image/object/Object_Item.bmp", 320 * MULTIPLY_X, 96 * MULTIPLY_Y, 10, 3, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("InteractableObject", "Image/object/Object_Interactable.bmp", 320, 448, 10, 14, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("multiply_InteractableObject", "Image/object/Object_Interactable.bmp", 320 * MULTIPLY_X, 448 * MULTIPLY_Y, 10, 14, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("InteractableObject_2", "Image/object/Object_Interactable_2.bmp", 320, 448, 10, 14, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("multiply_InteractableObject_2", "Image/object/Object_Interactable_2.bmp", 320 * MULTIPLY_X, 448 * MULTIPLY_Y, 10, 14, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("InteractableObject_3", "Image/object/Object_Interactable_3.bmp", 288, 384, 6, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("multiply_InteractableObject_3", "Image/object/Object_Interactable_3.bmp", 288 * MULTIPLY_X, 384 * MULTIPLY_Y, 6, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Object_Interactable_5", "Image/object/Object_Interactable_5.bmp", 160, 160, 5, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("multiply_Object_Interactable_5", "Image/object/Object_Interactable_5.bmp", 160 * MULTIPLY_X, 160 * MULTIPLY_Y, 5, 5, true, RGB(255, 0, 255));
	//SHELL EFFECT
	IMAGEMANAGER->addFrameImage("shell_effect", "Image/enemy/Shell_Effect.bmp", 256 * MULTIPLY_X, 16 * MULTIPLY_Y, 16, 1, true, RGB(0, 0, 0));
	//HITEFFECT
	IMAGEMANAGER->addFrameImage("hit_Effect", "Image/object/hit_frame.bmp", 192 * MULTIPLY_X, 64 * MULTIPLY_Y, 3, 1, true, RGB(255, 0, 255));
	//DOOR
	IMAGEMANAGER->addFrameImage("Door", "image/object/Door.bmp", 96, 48, 3,1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("multiply_Door", "image/object/Door.bmp", 96 * MULTIPLY_X, 48 * MULTIPLY_Y, 3, 1, true, RGB(255, 0, 255));
	//NPC
	IMAGEMANAGER->addFrameImage("NPC", "image/object/NPC.bmp", 320, 192, 10, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("multiply_NPC", "image/object/NPC.bmp", 320 * MULTIPLY_X, 192 * MULTIPLY_Y, 10, 6, true, RGB(255, 0, 255));
	//HOUSE
	IMAGEMANAGER->addFrameImage("House", "image/object/House.bmp", 160, 160,1,1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("multiply_House", "image/object/House.bmp", 160 * MULTIPLY_X, 160 * MULTIPLY_Y, 1, 1, true, RGB(255, 0, 255));
	//GRASS
	IMAGEMANAGER->addFrameImage("grass", "image/object/grass.bmp", 128, 92, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("multiply_grass", "image/object/grass.bmp", 128 * MULTIPLY_X, 92 * MULTIPLY_Y, 2, 1, true, RGB(255, 0, 255));


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////에너미/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//적은 에디터에서는 그냥 씬네일을 따로 만들어서 찍고, 확대한 것을 기본으로 두자.
	//여긴까는데 노가다로 깔아야한당.... 이미지 크기가 다르고 그 정보를 여기단에서는 알 수가 없으니깐. 다만 이 이후에는 코드로 자동화 시켜 줄 수 있다.
	IMAGEMANAGER->addFrameImage("monster_0", "Image/enemy/crap.bmp", 288 , 80 , 6, 2, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("crap", "Image/enemy/crap.bmp", 288 * MULTIPLY_X, 80 * MULTIPLY_Y, 6, 2, true, RGB(0, 0, 0));

	IMAGEMANAGER->addFrameImage("monster_1", "Image/enemy/flower.bmp", 256, 32, 8, 1, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("flower", "Image/enemy/flower.bmp", 256 * MULTIPLY_X, 32 * MULTIPLY_Y, 8, 1, true, RGB(0, 0, 0));

	IMAGEMANAGER->addFrameImage("monster_2", "Image/enemy/fly.bmp", 192, 32, 6, 1, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("fly", "Image/enemy/fly.bmp", 192 * MULTIPLY_X, 32 * MULTIPLY_Y, 6, 1, true, RGB(0, 0, 0));

	IMAGEMANAGER->addFrameImage("monster_3", "Image/enemy/Forest_boss.bmp", 256, 128, 4, 2, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("Forest_boss", "Image/enemy/Forest_boss.bmp", 256 * MULTIPLY_X, 128 * MULTIPLY_Y, 4, 2, true, RGB(0, 0, 0));

	IMAGEMANAGER->addFrameImage("monster_4", "Image/enemy/Forest_boss_tentacle.bmp", 288, 96, 6, 2, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("Forest_boss_tentacle", "Image/enemy/Forest_boss_tentacle.bmp", 288 * MULTIPLY_X, 96 * MULTIPLY_Y, 6, 2, true, RGB(0, 0, 0));

	IMAGEMANAGER->addFrameImage("monster_5", "Image/enemy/Forest_MiniBoss.bmp", 320, 128, 5, 2, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("Forest_MiniBoss", "Image/enemy/Forest_MiniBoss.bmp", 320 * MULTIPLY_X, 128 * MULTIPLY_Y, 5, 2, true, RGB(0, 0, 0));

	IMAGEMANAGER->addFrameImage("monster_6", "Image/enemy/frog.bmp", 192, 96, 6, 3, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("frog", "Image/enemy/frog.bmp", 192 * MULTIPLY_X, 96 * MULTIPLY_Y, 6, 3, true, RGB(0, 0, 0));

	IMAGEMANAGER->addFrameImage("monster_7", "Image/enemy/grasshopper.bmp", 192, 96, 6, 3, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("grasshopper", "Image/enemy/grasshopper.bmp", 192 * MULTIPLY_X, 96 * MULTIPLY_Y, 6, 3, true, RGB(0, 0, 0));

	IMAGEMANAGER->addFrameImage("monster_8", "Image/enemy/Shell_Monster.bmp", 320, 32, 10, 1, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("Shell_Monster", "Image/enemy/Shell_Monster.bmp", 320 * MULTIPLY_X, 32 * MULTIPLY_Y, 10, 1, true, RGB(0, 0, 0));

	IMAGEMANAGER->addFrameImage("monster_9", "Image/enemy/slime.bmp", 320, 32, 10, 1, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("slime", "Image/enemy/slime.bmp", 320 * MULTIPLY_X, 32 * MULTIPLY_Y, 10, 1, true, RGB(0, 0, 0));

	IMAGEMANAGER->addFrameImage("monster_10", "Image/enemy/turtle.bmp", 320, 96, 10, 3, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("turtle", "Image/enemy/turtle.bmp", 320 * MULTIPLY_X, 96 * MULTIPLY_Y, 10, 3, true, RGB(0, 0, 0));

	IMAGEMANAGER->addFrameImage("monster_11", "Image/enemy/water_boss.bmp", 256, 286, 2, 3, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("water_boss", "Image/enemy/water_boss.bmp", 256 * MULTIPLY_X, 286 * MULTIPLY_Y, 2, 3, true, RGB(0, 0, 0));

	IMAGEMANAGER->addFrameImage("monster_12", "Image/enemy/water_MiniBoss.bmp", 320, 58, 5, 1, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("water_MiniBoss", "Image/enemy/water_MiniBoss.bmp", 320 * MULTIPLY_X, 58 * MULTIPLY_Y, 5, 1, true, RGB(0, 0, 0));

	IMAGEMANAGER->addFrameImage("monster_13", "Image/enemy/water_shell.bmp", 192, 96, 4, 3, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("water_shell", "Image/enemy/water_shell.bmp", 192 * MULTIPLY_X, 96 * MULTIPLY_Y, 4, 3, true, RGB(0, 0, 0));

	IMAGEMANAGER->addFrameImage("monster_14", "Image/enemy/waterFog.bmp", 128, 32, 4, 1, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("waterFog", "Image/enemy/waterFog.bmp", 128 * MULTIPLY_X, 32 * MULTIPLY_Y, 4, 1, true, RGB(0, 0, 0));
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////ETC///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	IMAGEMANAGER->addImage("PortalAlpha", "Image/etc/PlaceAlpha.bmp", 32, 32, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("dialogwindow", "Image/UI/dialogWindow.bmp",1000, 200, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("savewindow", "Image/UI/saveWindow.bmp", 700, 358, false, RGB(0, 0, 0));
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////SOUND////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////wav for effect sound///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	SOUNDMANAGER->addSound("bee01", "wav/bee01.wav",false,false);
	SOUNDMANAGER->addSound("bom01", "wav/bom01.wav",false,false);
	SOUNDMANAGER->addSound("bom02", "wav/bom02.wav",false,false);
	SOUNDMANAGER->addSound("bom03", "wav/bom03.wav",false,false);
	SOUNDMANAGER->addSound("bom04", "wav/bom04.wav",false,false);
	SOUNDMANAGER->addSound("bom05", "wav/bom05.wav",false,false);
	SOUNDMANAGER->addSound("bom06", "wav/bom06.wav",false,false);
	SOUNDMANAGER->addSound("bom07", "wav/bom07.wav",false,false);
	SOUNDMANAGER->addSound("bom08", "wav/bom08.wav",false,false);
	SOUNDMANAGER->addSound("cut01", "wav/cut01.wav",false,false);
	SOUNDMANAGER->addSound("drag01", "wav/drag01.wav",false,false);
	SOUNDMANAGER->addSound("drag02", "wav/drag02.wav",false,false);
	SOUNDMANAGER->addSound("fall01", "wav/fall01.wav",false,false);
	SOUNDMANAGER->addSound("fire01", "wav/fire01.wav",false,false);
	SOUNDMANAGER->addSound("fire02", "wav/fire02.wav",false,false);
	SOUNDMANAGER->addSound("get01", "wav/get01.wav",false,false);
	SOUNDMANAGER->addSound("get02", "wav/get02.wav",false,false);
	SOUNDMANAGER->addSound("hit01", "wav/hit01.wav",false,false);
	SOUNDMANAGER->addSound("hit02", "wav/hit02.wav",false,false);
	SOUNDMANAGER->addSound("hit03", "wav/hit03.wav",false,false);
	SOUNDMANAGER->addSound("hit04", "wav/hit04.wav",false,false);
	SOUNDMANAGER->addSound("hit05", "wav/hit05.wav",false,false);
	SOUNDMANAGER->addSound("hit06", "wav/hit06.wav",false,false);
	SOUNDMANAGER->addSound("hit07", "wav/hit07.wav",false,false);
	SOUNDMANAGER->addSound("hit08", "wav/hit08.wav",false,false);
	SOUNDMANAGER->addSound("jump01", "wav/jump01.wav",false,false);
	SOUNDMANAGER->addSound("jump02", "wav/jump02.wav",false,false);
	SOUNDMANAGER->addSound("kachi01", "wav/kachi01.wav",false,false);
	SOUNDMANAGER->addSound("kachi02", "wav/kachi02.wav",false,false);
	SOUNDMANAGER->addSound("kachi03", "wav/kachi03.wav",false,false);
	SOUNDMANAGER->addSound("kachi04", "wav/kachi04.wav",false,false);
	SOUNDMANAGER->addSound("kakunin", "wav/kakunin.wav", false, false);
	SOUNDMANAGER->addSound("kidou01", "wav/kidou01.wav",false,false);
	SOUNDMANAGER->addSound("kin01", "wav/kin01.wav",false,false);
	SOUNDMANAGER->addSound("mizu01", "wav/mizu01.wav",false,false);
	SOUNDMANAGER->addSound("mizu02", "wav/mizu02.wav",false,false);
	SOUNDMANAGER->addSound("ng", "wav/ng.wav",false,false);
	SOUNDMANAGER->addSound("off", "wav/off.wav",false,false);
	SOUNDMANAGER->addSound("ok", "wav/ok.wav",false,false);
	SOUNDMANAGER->addSound("over01", "wav/over01.wav",false,false);
	SOUNDMANAGER->addSound("over02", "wav/over02.wav",false,false);
	SOUNDMANAGER->addSound("pi", "wav/pi.wav",false,false);
	SOUNDMANAGER->addSound("power01", "wav/power01.wav",false,false);
	SOUNDMANAGER->addSound("power02", "wav/power02.wav",false,false);
	SOUNDMANAGER->addSound("puu01", "wav/puu01.wav",false,false);
	SOUNDMANAGER->addSound("puu02", "wav/puu02.wav",false,false);
	SOUNDMANAGER->addSound("puu03", "wav/puu03.wav",false,false);
	SOUNDMANAGER->addSound("puu04", "wav/puu04.wav",false,false);
	SOUNDMANAGER->addSound("shot01", "wav/shot01.wav",false,false);
	SOUNDMANAGER->addSound("shot02", "wav/shot02.wav",false,false);
	SOUNDMANAGER->addSound("shot03", "wav/shot03.wav",false,false);
	SOUNDMANAGER->addSound("shot04", "wav/shot04.wav",false,false);
	SOUNDMANAGER->addSound("shot05", "wav/shot05.wav",false,false);
	SOUNDMANAGER->addSound("shot06", "wav/shot06.wav",false,false);
	SOUNDMANAGER->addSound("shot07", "wav/shot07.wav",false,false);
	SOUNDMANAGER->addSound("step01", "wav/step01.wav",false,false);
	SOUNDMANAGER->addSound("step02", "wav/step02.wav",false,false);
	SOUNDMANAGER->addSound("stop01", "wav/stop01.wav",false,false);
	SOUNDMANAGER->addSound("swing01", "wav/swing01.wav",false,false);
	SOUNDMANAGER->addSound("swing02", "wav/swing02.wav",false,false);
	SOUNDMANAGER->addSound("swing03", "wav/swing03.wav",false,false);
	SOUNDMANAGER->addSound("swing04", "wav/swing04.wav",false,false);
	SOUNDMANAGER->addSound("voice01", "wav/voice01.wav",false,false);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////midi for back ground////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	SOUNDMANAGER->addSound("boss01.mid", "midi/boss01.mid", true, true);
	SOUNDMANAGER->addSound("boss02.mid", "midi/boss02.mid", true, true);
	SOUNDMANAGER->addSound("dg01.mid", "midi/dg01.mid", true, true);
	SOUNDMANAGER->addSound("dg02.mid", "midi/dg02.mid", true, true);
	SOUNDMANAGER->addSound("dg03.mid", "midi/dg03.mid", true, true);
	SOUNDMANAGER->addSound("ele01.mid", "midi/ele01.mid", true, true);
	SOUNDMANAGER->addSound("field01.mid", "midi/field01.mid", true, true);
	SOUNDMANAGER->addSound("gameover.mid", "midi/gameover.mid", false, false);
	SOUNDMANAGER->addSound("itemget01.mid", "midi/itemget01.mid", false, false);
	SOUNDMANAGER->addSound("itemget02.mid", "midi/itemget02.mid", false, false);
	SOUNDMANAGER->addSound("op01.mid", "midi/op01.mid", false, false);
	SOUNDMANAGER->addSound("town01.mid", "midi/town01.mid", true, true);
	SOUNDMANAGER->addSound("town02.mid", "midi/town02.mid", true, true);
	SOUNDMANAGER->addSound("town03.mid", "midi/town03.mid", true, true);
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////신등록//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_menuScene = new MainMenu;
	_mainGameScene = new MainGame;
	_mapEditerScene = new MapEditer;



	SCENEMANAGER->addScene("menuScene", _menuScene);
	SCENEMANAGER->addScene("mainGameScene", _mainGameScene);
	SCENEMANAGER->addScene("mapEditerScene", _mapEditerScene);
	SCENEMANAGER->changeScene("menuScene");
	
	return S_OK;
}

//메모리 해제 해주는 곳
void gameStudy::release()
{
	gameNode::release();

}

//연산 해주는 곳
void gameStudy::update()
{
	gameNode::update();
	SCENEMANAGER->update();
	SOUNDMANAGER->update();
}

//그려주는 곳
void gameStudy::render(void)
{
	//백버퍼 내용을 hdc에 그린다(지우지 말 것)
	this->getBackBuffer()->render(getHDC(), 0, 0);

	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	///////////////////// 건 들 지 마 시 오 /////////////////////////////////////////////////////////

	SCENEMANAGER->render();

	//TIMEMANAGER->render(getMemDC());
}
