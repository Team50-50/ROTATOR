/*==============================================================================

	ステージ選択画面の制御[stagechoice.cpp]

													Author : トウ ミンヨウ
													Date   :

==============================================================================*/
#include "main.h"
#include "Sprite.h"
#include "texture.h"
#include "fade.h"
#include "keylogger.h"

static int g_TextureStageChoiceBG;
static int g_TextureStageChoiceS;
static int g_TextureStageChoiceRW;

static  int    GameStage = 9;
static  int    Gamemord_sentaku = 0;

static  float  Gamemord_sx = -500;
static  bool   Gamemord_st;

void InitStageChoice(void)
{

	g_TextureStageChoiceBG = Texture_SetTextureLoadFile("asset/stageC(kari).png");
	g_TextureStageChoiceS  = Texture_SetTextureLoadFile("asset/stageCS.png");
	g_TextureStageChoiceRW = Texture_SetTextureLoadFile("asset/redwaku.png");

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
		Gamemord_sx = -500;
		break;
	case 1:
		Gamemord_sx = -144;
		break;
	case 2:
		Gamemord_sx = 212;
		break;
	}

	if (Keylogger_Trigger(KL_RIGHT))
	{
		Gamemord_sentaku++;

		if (Gamemord_sentaku > 2)
		{
			Gamemord_sentaku = 0;
		}
	}
	if (Keylogger_Trigger(KL_LEFT))
	{
		Gamemord_sentaku--;

		if (Gamemord_sentaku < 0)
		{
			Gamemord_sentaku = 2;
		}
	}

	if (Keylogger_Press(KL_JUMP))
	{
		GameStage = Gamemord_sentaku;
		SetFade(FADE_OUT, SCENE_GAME);
		//PlaySE(SE_06);
	}

	if (GetKeyState('Z') & 0x80)
	{
		SetFade(FADE_OUT, SCENE_GAME);
		//PlaySE(SE_06);
	}

}

void DrawStageChoice(void)
{

	// スプライトを描画
	Sprite_Draw(g_TextureStageChoiceBG, -SCREEN_WIDTH * 0.5, -SCREEN_HEIGHT * 0.5, SCREEN_WIDTH, SCREEN_HEIGHT,
		0, 0, 1920, 1080);
	
	Sprite_Draw(g_TextureStageChoiceS, -500, -96, 288, 192,
	    0, 0, 1440, 960);
	Sprite_Draw(g_TextureStageChoiceS, -144, -96, 288, 192,
		1440, 0, 1440, 960);
	Sprite_Draw(g_TextureStageChoiceS,  212, -96, 288, 192,
		2880, 0, 1440, 960);

	Sprite_Draw(g_TextureStageChoiceRW, Gamemord_sx, -96, 288, 192,
		0, 0, 1440, 960/*, (255, 255, 255, 255)*/);

}

int* GetGamemord()
{
	return &GameStage;
}