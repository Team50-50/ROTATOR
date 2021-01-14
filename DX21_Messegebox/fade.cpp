
#include "Main.h"
#include "texture.h"
#include "Sprite.h"
#include "fade.h"

#define	FADE_RATE	(5)		// フェード係数(明るくまたは暗くなる速度)

static int g_TextureFade = TEXTURE_INVALID_ID;

int			g_Fade = FADE_IN;	// フェードの状態
int			g_NextScene;		// 次のScene
D3DCOLOR		g_Color;			// フェードのカラー（α値）

int       apha;

void InitFade(void)
{
	g_TextureFade = Texture_SetTextureLoadFile("asset/fade_black.png");	//Fade画像

	g_Fade = FADE_IN;
	g_Color = D3DCOLOR_RGBA(  255, 255, 255, 255);
	//                         R    G    B    α

	apha = 255;
}


void UninitFade(void)
{

	Texture_Release(&g_TextureFade,1);

}


void UpdateFade(void)
{
	if (g_Fade != FADE_NONE)
	{// フェード処理中
		if (g_Fade == FADE_OUT)
		{// フェードアウト処理
			apha += FADE_RATE;
			g_Color = D3DCOLOR_RGBA(255, 255, 255, (int)apha);		// α値を加算して画面を消していく
			if (apha >= 255)
			{
				// フェードイン処理に切り替え
				apha = 255;
				SetFade(FADE_IN, g_NextScene);

				// モードを設定
				SetScene(g_NextScene);
			}

		}
		else if (g_Fade == FADE_IN)
		{// フェードイン処理
			apha -= FADE_RATE;
			g_Color = D3DCOLOR_RGBA(255, 255, 255, (int)apha);		// α値を減算して画面を浮き上がらせる
			if (apha <= 0)
			{
				// フェード処理終了
				apha = 0;
				SetFade(FADE_NONE, g_NextScene);
			}

		}
	}

}


void DrawFade(void)
{
	if (g_Fade == FADE_NONE) return;	// フェードしないのなら描画しない

	//SetTexture(NULL);	// テクスチャーを使わない

	// スプライトを描画
	Sprite_Draw(g_TextureFade, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT,
		0.0f, 0.0f, 1.0f, 1.0f,
		g_Color);

	/*Sprite_Draw(NULL, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT,
		0.0f, 0.0f, 1.0f, 1.0f,
		g_Color);*/

	/*DrawSprite(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT,
		0.0f, 0.0f, 1.0f, 1.0f,
		g_Color);*/

}

//=============================================================================
// フェードの状態設定
//=============================================================================
void SetFade(int fade, int nextScene)
{
	g_Fade = fade;
	g_NextScene = nextScene;
}