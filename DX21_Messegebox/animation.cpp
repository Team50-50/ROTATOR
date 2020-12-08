/*=======================================================================================

	 アニメーション制御[animation.cpp]
												author:mgc
												date:2020/12/03
 -----------------------------------------------------------------------------------------

 =========================================================================================*/
#include"animation.h"

 //アニメーションの初期化
 //
 //引数：animation	...Animation構造体のポインタ
 //
 //		type		...アニメーションの種類
 //		tWidth		...テクスチャの幅
 //		tHeight		...テクスチャの高さ
 //		aWsize		...横のアニメーションのパターン数
 //		aHsize		...縦のアニメーションのパターン数
 //		aMax		...アニメーションのパターン数
 //
void InitAnimations(Animation *animation, int type, int tWidth, int tHeight, int aWsize, int aHsize, int aMax)
{
	animation[type].frame = 0;
	animation[type].animNo = 0;
	animation[type].texWidth = tWidth;
	animation[type].texHeight = tHeight;
	animation[type].animWSize = aWsize;
	animation[type].animHSize = aHsize;
	animation[type].animMax = aMax;
	animation[type].tcw = tWidth / aWsize;
	animation[type].tch = tHeight / aHsize;

	animation[type].tcx = 0;
	animation[type].tcy = 0;
	animation[type].isUse = false;

}


//アニメーションの更新処理
//
//引数：animation	...Animation構造体のポインタ
//
//		type		...アニメーションの種類
//		frame		...アニメーション更新の速さ
//				frame数が大きければ、更新速度が遅くなる
//
void UpdateAnimations(Animation* animation, int type, int frame)
{
	animation[type].frame++;

	if (animation[type].frame > frame)
	{
		animation[type].frame = 0;
		animation[type].animNo = (animation[type].animNo + 1) % animation[type].animMax;
	}

	animation[type].tcx = (animation[type].animNo % animation[type].animWSize) * animation[type].tcw;
	animation[type].tcy = (animation[type].animNo / animation[type].animWSize) * animation[type].tch;

}

void UpdateAnimations(Animation* animation, int type)
{
	animation[type].tcx = (animation[type].animNo % animation[type].animWSize) * animation[type].tcw;
	animation[type].tcy = (animation[type].animNo / animation[type].animWSize) * animation[type].tch;

}