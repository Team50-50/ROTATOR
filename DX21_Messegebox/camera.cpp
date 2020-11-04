
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "block.h"
#include "player.h"
#include "camera.h"

void InitCamera()
{
	static D3DXVECTOR2 PlayerPosition;

	PlayerPosition = GetPlayerPosition();

	g_CameraPosition = { SCREEN_WIDTH / 2.0f,SCREEN_HEIGHT / 2.0f };

	g_Screen_Position =	{g_CameraPosition.x - SCREEN_WIDTH / 2.0f,
						 g_CameraPosition.y - SCREEN_HEIGHT / 2.0f };
}

void UninitCamera()
{
	
}

void UpdateCamera()
{
	static D3DXVECTOR2 PlayerPosition;

	PlayerPosition = GetPlayerPosition();

	g_CameraPosition.x = PlayerPosition.x;

	g_CameraPosition.y = PlayerPosition.y;

	g_Screen_Position = { g_CameraPosition.x - SCREEN_WIDTH / 2.0f,
						 g_CameraPosition.y - SCREEN_HEIGHT / 2.0f };
}

void DrawCamera()
{

}