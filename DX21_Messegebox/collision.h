/*=======================================================================================

	 collision判定[collision.h]
												author:mgc
												date:2020/07/23
 -----------------------------------------------------------------------------------------

 =========================================================================================*/
#ifndef COLLISION_H
#define COLLISION_H

#include <d3dx9.h>

//円のcollision
typedef struct CollisionCircle_tag
{
	D3DXVECTOR2 center;
	float radius;

}CollisionCircle;

//矩形のcollision
typedef struct CollisionRect_tag
{
	D3DXVECTOR2 start;	//左上の座標
	D3DXVECTOR2 end;	//右下の座標

}CollisionRect;

//矩形の辺の種類
enum {
	EDGENONE = -1,
	LEFTEDGE,
	RIGHTEDGE,
	TOPEDGE,
	BOTTOMEDGE,
	EDGE_MAX
};

//円と円の衝突判定
bool Collision_CircleAndCircleHit(const CollisionCircle* pA, const CollisionCircle* pB);

//矩形とマップチップの辺の衝突判定
bool Collision_RectAndMapchipEdgeHit(const CollisionRect& rect, D3DXVECTOR2 vec, int& contactEdge, float& contactEdgePosition);

#endif