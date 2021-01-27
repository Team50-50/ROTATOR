/*=======================================================================================

	 逆再生爆発アニメーション[reversion_explosion.h]
												author:mgc
												date:2021/01/24
 -----------------------------------------------------------------------------------------

 =========================================================================================*/
#ifndef REVERSION_EXPLOSION_H_
#define REVERSION_EXPLOSION_H_

#include<d3dx9.h>
#include"animation.h"


 /*----------------------------------------------------------------------------------------
	 定数宣言
  ----------------------------------------------------------------------------------------*/
#define REXPLOSION_MAX (30)


void InitRExplosion(void);

void UninitRExplosion(void);

void UpdateRExplosion(void);

void DrawRExplosion(void);

void RExplosion_Destory(int index);


#endif // !REVERSION_EXPLOSION_H_
