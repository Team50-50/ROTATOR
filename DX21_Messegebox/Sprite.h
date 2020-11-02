/*==============================================================================

	TITLE
													Author : Ryuichi Tsunoda
													Date   :
==============================================================================*/
#ifndef SPRITE_H_
#define SPRITE_H_

void Sprite_Initialize(void);

void Sprite_Finalize(void);

void Sprite_Draw(int textureId, float dx, float dy);

void Sprite_Draw(int textureId, float dx, float dy, int tcx, int tcy, int tcw, int tch);

void Sprite_Draw(int textureId, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch);

void Sprite_Draw(int textureId, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch ,D3DCOLOR color);

void Sprite_Draw(int textureId, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch,
	float cx, float cy, float angle);

#endif // SPRITE_H_