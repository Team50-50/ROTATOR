/*==============================================================================

	ブロックの制御[block.cpp]

													Author : トウ ミンヨウ　& マコウチュウ
													Date   :


==============================================================================*/
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "block.h"
#include "player.h"
#include "camera.h"
#include "sniper.h"
#include "explosion.h"
#include "data_control.h"
#include "controller.h"

/*----------------------------------------------------------------------------------------
  グローバル変数
 ----------------------------------------------------------------------------------------*/
static const char* TextureFileNames[] = {
	"asset/testblock.jpg",
	"asset/block.png"
};

static const int TextureCnt = ARRAYSIZE(TextureFileNames);

//ブロックのテクスチャの読み込み
static int	g_BlockTexture[TextureCnt];

//ブロックの位置座標
Block g_Blocks[BLOCK_MAX];

int Block_Count = 0;


static DataStorage g_Current[BLOCK_MAX];
static DataStorage g_Prev[BLOCK_MAX];

static bool flag1 = false;
static bool flag2 = false;


/*-----------------------------------------------------------------------------------------
 関数定義
-------------------------------------------------------------------------------------------*/
void InitBlock()
{
	for (int i = 0; i < TextureCnt; i++)
	{
		g_BlockTexture[i] = Texture_SetTextureLoadFile(TextureFileNames[i]);
	}

	for (int i = 0; i < BLOCK_MAX; i++)
	{
		g_Blocks[i].use = false;
		g_Blocks[i].fall = false;
		g_Blocks[i].a = 255;
		g_Blocks[i].lifeFrame = 0;
	}

}

void UninitBlock()
{
	for (int i = 0; i < TextureCnt; i++)
	{
		Texture_Release(&g_BlockTexture[i], 1);
	}
}

void UpdateBlock()
{
	Rocket* rocket = Get_Rocket();

	float speed = 0.1f;
	int contact_edge = EDGENONE;
	float contact_pos = 0.0f;

	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (!g_Blocks[i].use) continue;

		g_Blocks[i].start = g_Blocks[i].position;
		g_Blocks[i].end = {
			g_Blocks[i].position.x + BLOCK_SIZE_X * g_Blocks[i].Width_Quantity,
			g_Blocks[i].position.y + BLOCK_SIZE_Y * g_Blocks[i].High_Quantity
		};


		//進行方向を長さ1にする
		D3DXVec2Normalize(&g_Blocks[i].direction, &g_Blocks[i].direction);

		//落下ブロックの処理
		if (g_Blocks[i].type == BLOCK_TYPE::BLOCK_OFFSETY)
		{
			g_Blocks[i].rect = {
				{g_Blocks[i].position.x,g_Blocks[i].position.y},
				{g_Blocks[i].position.x + BLOCK_SIZE_X * g_Blocks[i].Width_Quantity,g_Blocks[i].position.y + BLOCK_SIZE_Y * g_Blocks[i].High_Quantity}
			};

			//落下ブロックとマップチップの判定を行う
			if (!Collision_RectAndMapchipEdgeHit(g_Blocks[i].rect, { 0.0f, g_Blocks[i].direction.y }, contact_edge, contact_pos))
			{
				g_Blocks[i].position.y += g_Blocks[i].direction.y;
			}
			else
			{
				SetBlockMapPos(contact_edge, contact_pos, i);
			}

		}


		//===============================================================================
		//ブロックの記録&&逆再生
		//===============================================================================
		if (g_Current[i].Adata_tail == 0)
		{
			flag1 = false;
			flag2 = true;

		}
		if (g_Current[i].Adata_tail == 360)
		{
			flag1 = true;
		}

		if (flag2)
		{
			DataRecord(&g_Current[i], g_Blocks[i].a);

			deq_aData(&g_Prev[i]);

		}
		if (g_Current[i].Adata_tail > 360)
		{
			deq_aData(&g_Current[i]);
		}

		if (flag1)
		{
			if (GetKeyState('B') & 0x80 || JoystickPress(ButtonRT))
			{
				flag2 = false;
				
				DataRecord(&g_Prev[i], pop_aData(&g_Current[i]));

				for (int j = 0; j < g_Prev[i].Adata_tail; j++)
				{
					g_Blocks[i].a = g_Prev[i].aData[j];
				}
			}
		}



		//ロケットとブロックの衝突判定
		for (int j = 0; j < ROCKET_MAX; j++)
		{
			if (!rocket[j].enable || g_Blocks[i].a == 0) continue;

			if (rocket[j].position.x + 32.0f > g_Blocks[i].position.x &&
				rocket[j].position.x < g_Blocks[i].position.x + BLOCK_SIZE_X * g_Blocks[i].Width_Quantity &&
				rocket[j].position.y + ROCKET_WIDTH > g_Blocks[i].position.y &&
				rocket[j].position.y < g_Blocks[i].position.y + BLOCK_SIZE_Y * g_Blocks[i].High_Quantity)
			{
				rocket[j].enable = false;
				Explosion_Spawn(rocket[j].position.x - 50.0f, rocket[j].position.y - 50.0f);

				if (g_Blocks[i].type == BLOCK_TYPE::BLOCK_NORMAL)
				{
					g_Blocks[i].a = 0;
				}

				if (g_Blocks[i].type == BLOCK_TYPE::BLOCK_OFFSETY)
				{
					g_Blocks[i].fall = true;
				}

			}
		}

		//ブロックの落下
		if (g_Blocks[i].fall)
		{
			g_Blocks[i].direction.y += speed;
		}
	}
}

void DrawBlock()
{
	// ブロックを描画
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (g_Blocks[i].use)
		{
			if (g_Blocks[i].type == BLOCK_TYPE::BLOCK_NORMAL)
			{
				Sprite_Draw(g_BlockTexture[BLOCK_TYPE::BLOCK_NORMAL],
					g_Blocks[i].position.x, g_Blocks[i].position.y,
					BLOCK_SIZE_X * g_Blocks[i].Width_Quantity, BLOCK_SIZE_Y * g_Blocks[i].High_Quantity,
					0, 0, 64 * g_Blocks[i].Width_Quantity, 64 * g_Blocks[i].High_Quantity,
					D3DCOLOR_RGBA(255, 255, 255, g_Blocks[i].a));
			}

			if (g_Blocks[i].type == BLOCK_TYPE::BLOCK_OFFSETY)
			{
				Sprite_Draw(g_BlockTexture[BLOCK_TYPE::BLOCK_OFFSETY],
					g_Blocks[i].position.x, g_Blocks[i].position.y,
					BLOCK_SIZE_X * g_Blocks[i].Width_Quantity, BLOCK_SIZE_Y * g_Blocks[i].High_Quantity,
					0, 0, 64 * g_Blocks[i].Width_Quantity, 64 * g_Blocks[i].High_Quantity);
			}
		}
	}

}

void SetBlock(float x, float y, int w, int h, int type)
{

	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (g_Blocks[i].use == false)
		{
			g_Blocks[i].use = true;
			g_Blocks[i].position.x = x;
			g_Blocks[i].position.y = y;
			g_Blocks[i].Width_Quantity = w;
			g_Blocks[i].High_Quantity = h;
			g_Blocks[i].type = type;
			g_Blocks[i].a = 255;
			g_Blocks[i].lifeFrame = 0;
			break;
		}
	}

}

Block* GetBlockPosition()
{
	return g_Blocks;
}

// マップチップの辺の位置に座標を調整する
void SetBlockMapPos(int contact_edge, float contact_pos, int index)
{
	switch (contact_edge)
	{
	case TOPEDGE:	//チップの上の辺に当たった時の処理
		g_Blocks[index].position.y = contact_pos - BLOCK_SIZE_Y * g_Blocks[index].High_Quantity;
		break;
	}
}