/*=======================================================================================

	 爆発アニメーション[explosion.h]
												author:mgc
												date:2020/12/09
 -----------------------------------------------------------------------------------------

 =========================================================================================*/
#ifndef GAME_EXPLOSION_H_
#define GAME_EXPLOSION_H_

#include<d3dx9.h>
#include"animation.h"

 /*-----------------------------------------------------------------------------------------
   構造体宣言
-------------------------------------------------------------------------------------------*/
typedef struct Explosion_tag
{
	D3DXVECTOR2 position;
	int frame;
	bool enable;

	Animation animation[TYPE_MAX];

}Explosion;


/*----------------------------------------------------------------------------------------
	定数宣言
 ----------------------------------------------------------------------------------------*/
#define EXPLOSION_MAX (30)



void InitExplosion(void);

void UninitExplosion(void);

void UpdateExplosion(void);

void DrawExplosion(void);

void Explosion_Spawn(float x, float y);




#endif // !GAME_Explosion_H_
