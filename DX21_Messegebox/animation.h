/*=======================================================================================

	 アニメーション制御[animation.h]
												author:mgc
												date:2020/12/03
 -----------------------------------------------------------------------------------------

 =========================================================================================*/
#ifndef ANIMATION_H_
#define ANIMATION_H_

typedef struct Animation_tag
{
	int frame;
	int texWidth;
	int texHeight;
	int animNo;
	int animWSize;
	int animHSize;
	int animMax;
	int tcw;
	int tch;
	int tcx;
	int tcy;

	bool isUse;

}Animation;


//アニメーションの種類
enum {
	DEFAULT,
	WALKING,
	TYPE_MAX
};

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
void InitAnimations(Animation* animation, int type, int tWidth, int tHeight, int aWsize, int aHsize, int aMax);


//アニメーションの更新処理
//
//引数：animation	...Animation構造体のポインタ
//
//		type		...アニメーションの種類
//		frame		...アニメーション更新の速さ
//				frame数が大きければ、更新速度が遅くなる
//
void UpdateAnimations(Animation* animation, int type, int frame);


void UpdateAnimations(Animation* animation, int type);


#endif // !ANIMATION_H_


