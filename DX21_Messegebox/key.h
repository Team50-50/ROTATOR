#pragma once
#include <d3dx9.h>
#include "collision.h"

// 鍵のMax数（配列の数）
#define KEY_MAX (8)

// 鍵の大きさX
#define KEY_SIZE_X (64.0f)

// 鍵の大きさY
#define KEY_SIZE_Y (64.0f)


typedef struct {

	bool  use;
	bool  InPlayer;
	D3DXVECTOR2 xy;

} Key;


void InitKey();

void UninitKey();

void UpdateKey();

void DrawKey();

void SetKey(float x, float y);

CollisionCircle GameKey_GetCollision(int index);

Key* GetKeys();

int GetPlayerKeyPossession();