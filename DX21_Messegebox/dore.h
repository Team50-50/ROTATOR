#pragma once
#include <d3dx9.h>

// ����Max���i�z��̐��j
#define DORE_MAX (8)

// ���̑傫��X
#define DORE_SIZE_X (64.0f)

// ���̑傫��Y
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