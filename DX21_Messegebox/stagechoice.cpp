/*==============================================================================

	ステージ選択画面の制御[stagechoice.cpp]

													Author : トウ ミンヨウ
													Date   :

==============================================================================*/
#define _CRT_SECURE_NO_WARNINGS

#include "main.h"
#include "Sprite.h"
#include "texture.h"
#include "fade.h"
#include "keylogger.h"
#include "Texture.h"
#include "controller.h"
#include<stdio.h>
#include "debug_font.h"
#include "sound.h"


static int g_TextureStageChoiceBG;
static int g_TextureStageChoiceS;
static int g_TextureStageChoiceRW;

static  int    GameStage = 9;
static  int    Gamemord_sentaku = 0;

static  float  Gamemord_sx = -500;
static  bool   Gamemord_st;

static int sec;

void InitStageChoice(void)
{

	g_TextureStageChoiceBG = Texture_SetTextureLoadFile("asset/title.jpg");
	g_TextureStageChoiceS  = Texture_SetTextureLoadFile("asset/stageCS.png");
	g_TextureStageChoiceRW = Texture_SetTextureLoadFile("asset/redwaku.png");

	Texture_Load();

}

void UninitStageChoice(void)
{

	Texture_Release(&g_TextureStageChoiceBG, 1);
	Texture_Release(&g_TextureStageChoiceS, 1);
	Texture_Release(&g_TextureStageChoiceRW, 1);

}

void UpdateStageChoice(void)
{
	
	switch (Gamemord_sentaku)
	{
	case 0:
		Gamemord_sx = 200.0f;
		break;
	case 1:
		Gamemord_sx = 520.0f;
		break;
	case 2:
		Gamemord_sx = 820.0f;
		break;
	}

	if (Keylogger_Trigger(KL_RIGHT) || JoystickTrigger(RightButton))
	{
		Gamemord_sentaku++;

		if (Gamemord_sentaku > 2)
		{
			Gamemord_sentaku = 0;
		}
	}
	if (Keylogger_Trigger(KL_LEFT) || JoystickTrigger(LeftButton))
	{
		Gamemord_sentaku--;

		if (Gamemord_sentaku < 0)
		{
			Gamemord_sentaku = 2;
		}
	}

	if (Keylogger_Press(KL_JUMP) || JoystickPress(ButtonB))
	{
		GameStage = Gamemord_sentaku;
		SetFade(FADE_OUT, SCENE_GAME);
		if (sec == 0)
		{
			PlaySound(SOUND_LABEL_SE_TITLE);
			sec = 1;
		}
	}

	if (GetKeyState('Z') & 0x80)
	{
		SetFade(FADE_OUT, SCENE_GAME);
		//PlaySE(SE_06);
	}

}

void DrawStageChoice(void)
{
	//360
	// スプライトを描画
	Screen_Draw(g_TextureStageChoiceBG, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT,
		0, 0, 1280, 720);
	
	Screen_Draw(g_TextureStageChoiceS, 200.0f, 420.0f, 288.0f, 192.0f,
	    0, 0, 1440, 960);						  		  		 
	Screen_Draw(g_TextureStageChoiceS, 520.0f, 420.0f, 288.0f, 192.0f,
		1440, 0, 1440, 960);					  		  		 
	Screen_Draw(g_TextureStageChoiceS, 820.0f, 420.0f, 288.0f, 192.0f,
		2880, 0, 1440, 960);

	Screen_Draw(g_TextureStageChoiceRW, Gamemord_sx, 420.0f, 288.0f, 192.0f,
		0, 0, 1440, 960/*, (255, 255, 255, 255)*/);

	char Buf[64];
	sprintf(Buf, "s=%d", Gamemord_sentaku);
	//DebugFont_Draw(900.0f, 300.0f, Buf);

}

int* GetGamemord()
{
	return &GameStage;
}

int& Getmap(void)
{
	return Gamemord_sentaku;
}