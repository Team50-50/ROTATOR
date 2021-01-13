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
#include"keylogger.h"
#include"controller.h"
#include"map.h"

 /*-----------------------------------------------------------------------------------------
   グローバル変数
 -------------------------------------------------------------------------------------------*/
static D3DXVECTOR2 g_cameraPosition;

/*-----------------------------------------------------------------------------------------
  関数定義
-------------------------------------------------------------------------------------------*/
void GameCamera_Update(void)
{
	if (Keylogger_Press(KL_UP) || JoystickPress(UpButton))
	{
		g_cameraPosition.y -= 20.0f;
	}

	if (Keylogger_Press(KL_DOWN) || JoystickPress(DownButton))
	{
		g_cameraPosition.y += 20.0f;
	}

	if (Keylogger_Press(KL_RIGHT) || JoystickPress(RightButton))
	{
		g_cameraPosition.x += 20.0f;
	}

	if (Keylogger_Press(KL_LEFT) || JoystickPress(LeftButton))
	{
		g_cameraPosition.x -= 20.0f;
	}

	Player player = GetPlayer();

	if (!Keylogger_Press(KL_UP) && !Keylogger_Press(KL_DOWN) &&
		!Keylogger_Press(KL_RIGHT) && !Keylogger_Press(KL_LEFT) &&
		!JoystickPress(UpButton) && !JoystickPress(DownButton) &&
		!JoystickPress(RightButton) && !JoystickPress(LeftButton))
	{
		SetCamera(player.position.x, player.position.y);
	}

	if (g_cameraPosition.x <= SCREEN_WIDTH * 0.5f)
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
	}


}

D3DXVECTOR2 WorldToScreen(D3DXVECTOR2 objPosition)
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
