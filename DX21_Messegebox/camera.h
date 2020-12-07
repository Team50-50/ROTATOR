/*=======================================================================================

	 ゲームのカメラ制御（2D）[game_camera.h]
												author:mgc
												date:2020/11/12
 -----------------------------------------------------------------------------------------

 =========================================================================================*/
#ifndef GAME_CAMERA_H_
#define GAME_CAMERA_H_

#include<d3dx9.h>

void GameCamera_Update(void);

D3DXVECTOR2 WorldToScreen(D3DXVECTOR2 objPosition);

void SetCamera(float x, float y);

D3DXVECTOR2 GetCameraPosition(void);

#endif // !GAME_CAMERA_H_

