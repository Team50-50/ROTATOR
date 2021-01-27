/*=======================================================================================

	 狙いシステム制御[sniper.h]
												author:mgc
												date:2020/11/23
 -----------------------------------------------------------------------------------------

 =========================================================================================*/
#ifndef SNIPER_H_
#define SNIPER_H_

#include <d3dx9.h>
#include "collision.h"
#include "data_control.h"

 /*-----------------------------------------------------------------------------------------
   定数宣言
 -------------------------------------------------------------------------------------------*/
#define ROCKET_MAX    (5)
#define ROCKET_SPEED  (10.0f)
#define ROCKET_WIDTH (32.0f)
#define ROCKET_HEIGHT (32.0f)

 /*-----------------------------------------------------------------------------------------
  構造体宣言
 -------------------------------------------------------------------------------------------*/
typedef struct Rocket_tag
{
	D3DXVECTOR2 position;
	D3DXVECTOR2 target;
	float r_angle;
	int frame;
	int a;
		
	bool enable;

	CollisionCircle collision;
}Rocket;

void InitSniper(int rocket_max);

void UninitSniper(void);

void UpdateSniper(void);

void DrawSniper(void);

void Rocket_Spawn(float x, float y);

void Rocket_Destory(int index);

void reversionRocket_Destory(int index);

Rocket* Get_Rocket(void);

int* Get_RocketMax(void);

DataStorage* GetRocket_Prev(void);

int& Get_RocketCount(void);

#endif // !SNIPER_H_

