/*=======================================================================================

	 �_���V�X�e������[sniper.h]
												author:mgc
												date:2020/11/23
 -----------------------------------------------------------------------------------------

 =========================================================================================*/
#ifndef SNIPER_H_
#define SNIPER_H_

 /*-----------------------------------------------------------------------------------------
   �萔�錾
 -------------------------------------------------------------------------------------------*/
#define ROCKET_MAX    (5)

 /*-----------------------------------------------------------------------------------------
  �\���̐錾
 -------------------------------------------------------------------------------------------*/
typedef struct Rocket_tag
{
	D3DXVECTOR2 position;

	D3DXVECTOR2 target;
	float r_angle;

	bool enable;


}Rocket;

void InitSniper(void);

void UninitSniper(void);

void UpdateSniper(void);

void DrawSniper(void);

void Rocket_Spawn(float x, float y);

#endif // !SNIPER_H_
