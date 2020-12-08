/*=======================================================================================

	 �_���V�X�e������[sniper.h]
												author:mgc
												date:2020/11/23
 -----------------------------------------------------------------------------------------

 =========================================================================================*/
#ifndef SNIPER_H_
#define SNIPER_H_

#include <d3dx9.h>
#include "collision.h"

 /*-----------------------------------------------------------------------------------------
   �萔�錾
 -------------------------------------------------------------------------------------------*/
#define ROCKET_MAX    (5)
#define ROCKET_SPEED  (10.0f)
#define ROCKET_SIZE_X (32.0f)
#define ROCKET_SIZE_Y (32.0f)

 /*-----------------------------------------------------------------------------------------
  �\���̐錾
 -------------------------------------------------------------------------------------------*/
typedef struct Rocket_tag
{
	
	bool enable;
	D3DXVECTOR2 position;
	D3DXVECTOR2 target;
	float r_angle;
	
}Rocket;

void InitSniper(void);

void UninitSniper(void);

void UpdateSniper(void);

void DrawSniper(void);

void Rocket_Spawn(float x, float y);

CollisionCircle GameRocket_GetCollision(int index);

#endif // !SNIPER_H_

