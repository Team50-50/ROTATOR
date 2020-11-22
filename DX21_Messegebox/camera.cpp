/*=======================================================================================

	 ゲームのカメラ制御（2D）[camera.cpp]
												author:mgc
												date:2020/11/12
 -----------------------------------------------------------------------------------------

 =========================================================================================*/
#include<d3dx9.h>
#include"camera.h"
#include"config.h"
#include"bg.h"
#include"player.h"

 /*-----------------------------------------------------------------------------------------
   グローバル変数
 -------------------------------------------------------------------------------------------*/
static D3DXVECTOR2 g_cameraPosition;

/*-----------------------------------------------------------------------------------------
  関数定義
-------------------------------------------------------------------------------------------*/
void GameCamera_Update(void)
{
	D3DXVECTOR2 playerPosition = GetPlayerPosition();

	SetCamera(playerPosition.x, playerPosition.y);

	/*if (g_cameraPosition.x <= SCREEN_WIDTH * 0.5f)
	{
		g_cameraPosition.x = SCREEN_WIDTH * 0.5f;
	}

	if (g_cameraPosition.x >= STAGE_WIDTH - SCREEN_WIDTH * 0.5f)
	{
		g_cameraPosition.x = STAGE_WIDTH - SCREEN_WIDTH * 0.5f;
	}

	if (g_cameraPosition.y <= SCREEN_HEIGHT * 0.5f)
	{
		g_cameraPosition.y = SCREEN_HEIGHT * 0.5f;
	}

	if (g_cameraPosition.y >= STAGE_HEIGHT - SCREEN_HEIGHT * 0.5f)
	{
		g_cameraPosition.y = STAGE_HEIGHT - SCREEN_HEIGHT * 0.5f;
	}*/


}

D3DXVECTOR2 CALLBACK WorldToScreen(D3DXVECTOR2 objPosition)
{
	// スクリーン座標を算出
	D3DXVECTOR2 screenPosition =
	{
		g_cameraPosition.x - SCREEN_WIDTH * 0.5f,
		g_cameraPosition.y - SCREEN_HEIGHT * 0.5f
	};

	// ワールド座標からスクリーン座標に変換する
	D3DXVECTOR2 screenCoordinate = objPosition - screenPosition;

	return screenCoordinate;
}

void SetCamera(float x, float y)
{
	g_cameraPosition = D3DXVECTOR2(x, y);
}

D3DXVECTOR2 GetCameraPosition(void)
{
	return g_cameraPosition;
}
