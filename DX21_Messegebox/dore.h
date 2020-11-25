#pragma once
#include <d3dx9.h>

// 扉のMax数（配列の数）
#define DORE_MAX (8)

// 扉の大きさX
#define DORE_SIZE_X (64.0f)

// 扉の大きさY
#define DORE_SIZE_Y (128.0f)


typedef struct {

	bool  use;
	D3DXVECTOR2 xy;

} Dore;


void InitDore();

void UninitDore();

void UpdateDore();

void DrawDore();

void SetDore(float x, float y);

void DelDore(int num);

Dore* GetDores();