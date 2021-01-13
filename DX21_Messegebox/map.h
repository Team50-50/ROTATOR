/*=======================================================================================

	 マップの制御[map.h]
												author:mgc
												date:2020/12/23
 -----------------------------------------------------------------------------------------

 =========================================================================================*/
#ifndef MAP_H_
#define MAP_H_


#include<d3dx9.h>
#include"collision.h"

 /*-----------------------------------------------------------------------------------------
  定数宣言
 -------------------------------------------------------------------------------------------*/
#define STAGE_WIDTH (1920)
#define STAGE_HEIGHT (960)
#define MAPCHIP_WIDTH (64)								// マップチップの横幅
#define MAPCHIP_HEIGHT (64)								// マップチップの縦幅
#define MAP_XSIZE (STAGE_WIDTH / MAPCHIP_WIDTH)			// MAPの横幅(値はチップ数)
#define MAP_YSIZE (STAGE_HEIGHT / MAPCHIP_HEIGHT)		// MAPの縦幅(値はチップ数)

void InitMap();

void UninitMap();

void UpdateMap();

void DrawMap();

//チップ4辺の接触情報を返す
void GetChipEdgeHit(int rectEdge, int chip_id_x, int chip_id_y, int& contactEdge, float& contactPosition);

int* GetMapchip(void);

int GetKeyCnt(void);

CollisionCircle* Get_KeyCollision(void);

#endif // !MAP_H_

