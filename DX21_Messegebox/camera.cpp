/*=======================================================================================

	 �Q�[���̃J��������i2D�j[camera.cpp]
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
   �O���[�o���ϐ�
 -------------------------------------------------------------------------------------------*/
static D3DXVECTOR2 g_cameraPosition;

/*-----------------------------------------------------------------------------------------
  �֐���`
-------------------------------------------------------------------------------------------*/
void GameCamera_Update(void)
{
	D3DXVECTOR2 playerPosition = GetPlayerPosition();

	SetCamera(playerPosition.x, playerPosition.y);

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
	// �X�N���[�����W���Z�o
	D3DXVECTOR2 screenPosition =
	{
		g_cameraPosition.x - SCREEN_WIDTH * 0.5f,
		g_cameraPosition.y - SCREEN_HEIGHT * 0.5f
	};

	// ���[���h���W����X�N���[�����W�ɕϊ�����
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
