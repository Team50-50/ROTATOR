/*=======================================================================================

	 �}�b�v�̐���[map.h]
												author:mgc
												date:2020/12/23
 -----------------------------------------------------------------------------------------

 =========================================================================================*/
#ifndef MAP_H_
#define MAP_H_


#include<d3dx9.h>
#include"collision.h"

 /*-----------------------------------------------------------------------------------------
  �萔�錾
 -------------------------------------------------------------------------------------------*/
#define STAGE_WIDTH    (1920)
#define STAGE_HEIGHT   (960)
#define MAPCHIP_WIDTH  (64)								// �}�b�v�`�b�v�̉���
#define MAPCHIP_HEIGHT (64)								// �}�b�v�`�b�v�̏c��
#define MAP_XSIZE (STAGE_WIDTH / MAPCHIP_WIDTH)			// MAP�̉���(�l�̓`�b�v��)
#define MAP_YSIZE (STAGE_HEIGHT / MAPCHIP_HEIGHT)		// MAP�̏c��(�l�̓`�b�v��)

void InitMap();

void UninitMap();

void UpdateMap();

void DrawMap();

//�`�b�v4�ӂ̐ڐG����Ԃ�
void GetChipEdgeHit(int rectEdge, int chip_id_x, int chip_id_y, int& contactEdge, float& contactPosition);

int* GetMapchip(void);

int GetKeyCnt(void);

CollisionCircle* Get_KeyCollision(void);

int& GetplayerKey(void);

#endif // !MAP_H_

