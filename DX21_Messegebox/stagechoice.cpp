
#include "main.h"
#include "Sprite.h"
#include "texture.h"
#include "fade.h"
#include "keylogger.h"

static int g_TextureStageChoiceBG;

static  int    Gamemord = 9;
static  int    Gamemord_sentaku = 0;

static  float  Gamemord_sy;
static  float  Gamemord_sa;
static  bool   Gamemord_sb;

void InitStageChoice(void)
{

	g_TextureStageChoiceBG = Texture_SetTextureLoadFile("asset/stageC(kari).png");

}

void UninitStageChoice(void)
{

	Texture_Release(&g_TextureStageChoiceBG, 1);

}

void UpdateStageChoice(void)
{



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

}

int* GetGamemord()
{
	return &Gamemord;
}