/*==============================================================================

	Sprite.h
													Author : Ryuichi Tsunoda
													Date   :
==============================================================================*/
#ifndef SPRITE_H_
#define SPRITE_H_

#include <d3dx9.h>

void Sprite_Initialize(void);

void Sprite_Finalize(void);


//スプライトの描画
//＊テクスチャ切り取りサイズのポリゴンで指定座標に描画
//
//引数：textureId...テクスチャ管理番号
//
//		dx       ...描画座標x(左上指定)
//		dy       ...描画座標y(左上指定)
//
void Sprite_Draw(int textureId, float dx, float dy);


//スプライトの描画
//＊テクスチャ切り取りサイズのポリゴンで指定座標に描画
//
//引数：textureId...テクスチャ管理番号
//
//		dx       ...描画座標x(左上指定)
//		dy       ...描画座標y(左上指定)
//		tcx      ...テクスチャ切り取り座標x
//		tcy      ...テクスチャ切り取り座標y
//		tcw      ...テクスチャ切り取り幅
//		tch      ...テクスチャ切り取り高さ
//
void Sprite_Draw(int textureId, float dx, float dy, int tcx, int tcy, int tcw, int tch);


//スプライトの描画
//＊指定テクスチャ切り取りサイズのポリゴンで指定座標に描画
//
//
//引数：textureId...テクスチャ管理番号
//
//		dx       ...描画座標x(左上指定)
//		dy       ...描画座標y(左上指定)
//		dw		 ...ポリゴンのサイズ幅
//		dh		 ...ポリゴンのサイズ高さ
//		tcx      ...テクスチャ切り取り座標x
//		tcy      ...テクスチャ切り取り座標y
//		tcw      ...テクスチャ切り取り幅
//		tch      ...テクスチャ切り取り高さ
//
void Sprite_Draw(int textureId, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch);


//スプライトの描画
//＊指定したテクスチャ切り取りサイズのポリゴンで色を変えて指定座標に描画
//
//
//引数：textureId...テクスチャ管理番号
//
//		dx       ...描画座標x(左上指定)
//		dy       ...描画座標y(左上指定)
//		dw		 ...ポリゴンのサイズ幅
//		dh		 ...ポリゴンのサイズ高さ
//		tcx      ...テクスチャ切り取り座標x
//		tcy      ...テクスチャ切り取り座標y
//		tcw      ...テクスチャ切り取り幅
//		tch      ...テクスチャ切り取り高さ
//		D3DCOLOR color　...テクスチャの色をRGBで設定
//
void Sprite_Draw(int textureId, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch, D3DCOLOR color);


//スプライトの描画
//＊回転機能付き
//
//引数：textureId...テクスチャ管理番号
//
//		dx       ...描画座標x(左上指定)
//		dy       ...描画座標y(左上指定)
//		dw		 ...ポリゴンのサイズ幅
//		dh		 ...ポリゴンのサイズ高さ
//		tcx      ...テクスチャ切り取り座標x
//		tcy      ...テクスチャ切り取り座標y
//		tcw      ...テクスチャ切り取り幅
//		tch      ...テクスチャ切り取り高さ
//		cx		 ...回転の中心座標x
//		cy		 ...回転の中心座標y
//		angle    ...回転角度(ラジアン)
//
void Sprite_Draw(int textureId, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch,
	float cx, float cy, float angle);

void Screen_Draw(int textureId, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch);

void Screen_Draw(int textureId, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch, D3DCOLOR color);

void Sprite_DrawLeft(int textureId, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch);

void Sprite_DrawLeft(int textureId, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch, D3DCOLOR color);

#endif // SPRITE_H_