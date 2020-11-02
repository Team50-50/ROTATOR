#pragma once


#define BLOCK_MAX 100	// ブロックのMax数（配列の数）

struct BLOCK			// ブロック構造体
{
	Float2	Position;
	int		Type;
	bool	Use;
};


void InitBlock();
void UninitBlock();
void UpdateBlock();
void DrawBlock();

// ブロックを配置する関数
void SetBlock(float x, float y, int type);

// ブロック構造体の先頭アドレスを返す関数
BLOCK *GetBlock();


