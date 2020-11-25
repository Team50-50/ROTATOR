#pragma once
#include <d3dx9.h>
#include "collision.h"

// ����Max���i�z��̐��j
#define KEY_MAX (8)

// ���̑傫��X
#define KEY_SIZE_X (64.0f)

// ���̑傫��Y
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