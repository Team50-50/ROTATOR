
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "block.h"
#include "player.h"
#include "camera.h"
#include "sniper.h"
#include "explosion.h"


/*----------------------------------------------------------------------------------------
  �O���[�o���ϐ�
 ----------------------------------------------------------------------------------------*/
static const char* TextureFileNames[] = {
	"asset/testblock.jpg",
	"asset/block.png"
};

static const int TextureCnt = ARRAYSIZE(TextureFileNames);

//�u���b�N�̃e�N�X�`���̓ǂݍ���
static int	g_BlockTexture[TextureCnt];


//�u���b�N�̈ʒu���W
Block g_Blocks[BLOCK_MAX];

int Block_Count = 0;

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

		//�i�s�����𒷂�1�ɂ���
		D3DXVec2Normalize(&g_Blocks[i].direction, &g_Blocks[i].direction);

		//�����u���b�N�̏���
		if (g_Blocks[i].type == BLOCK_TYPE::BLOCK_OFFSETY)
		{
			g_Blocks[i].rect = {
				{g_Blocks[i].position.x,g_Blocks[i].position.y},
				{g_Blocks[i].position.x + BLOCK_SIZE_X * g_Blocks[i].Width_Quantity,g_Blocks[i].position.y + BLOCK_SIZE_Y * g_Blocks[i].High_Quantity}
			};

			//�����u���b�N�ƃ}�b�v�`�b�v�̔�����s��
			if (!Collision_RectAndMapchipEdgeHit(g_Blocks[i].rect, { 0.0f, g_Blocks[i].direction.y }, contact_edge, contact_pos))
			{
				g_Blocks[i].position.y += g_Blocks[i].direction.y;
			}
			else
			{
				SetBlockMapPos(contact_edge, contact_pos, i);
			}

		}

		//���P�b�g�ƃu���b�N�̏Փ˔���
		for (int j = 0; j < ROCKET_MAX; j++)
		{
			if (!rocket[j].enable) continue;

			if (rocket[j].position.x + 32.0f > g_Blocks[i].position.x &&
				rocket[j].position.x < g_Blocks[i].position.x + BLOCK_SIZE_X * g_Blocks[i].Width_Quantity &&
				rocket[j].position.y + ROCKET_WIDTH > g_Blocks[i].position.y &&
				rocket[j].position.y < g_Blocks[i].position.y + BLOCK_SIZE_Y * g_Blocks[i].High_Quantity)
			{
				rocket[j].enable = false;
				Explosion_Spawn(rocket[j].position.x - 50.0f, rocket[j].position.y - 50.0f);

				if (g_Blocks[i].type == BLOCK_TYPE::BLOCK_NORMAL)
				{
					g_Blocks[i].use = false;
				}

				if (g_Blocks[i].type == BLOCK_TYPE::BLOCK_OFFSETY)
				{
					g_Blocks[i].fall = true;
				}

			}
		}

		//�u���b�N�̗���
		if (g_Blocks[i].fall)
		{
			g_Blocks[i].direction.y += speed;
		}
	}
}

void DrawBlock()
{
	// �u���b�N��`��
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (g_Blocks[i].use)
		{
			if (g_Blocks[i].type == BLOCK_TYPE::BLOCK_NORMAL)
			{
				Sprite_Draw(g_BlockTexture[BLOCK_TYPE::BLOCK_NORMAL],
					g_Blocks[i].position.x, g_Blocks[i].position.y,
					BLOCK_SIZE_X * g_Blocks[i].Width_Quantity, BLOCK_SIZE_Y * g_Blocks[i].High_Quantity,
					0, 0, 64 * g_Blocks[i].Width_Quantity, 64 * g_Blocks[i].High_Quantity);
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
			break;
		}
	}

}

Block* GetBlockPosition()
{
	return g_Blocks;
}

// �}�b�v�`�b�v�̕ӂ̈ʒu�ɍ��W�𒲐�����
void SetBlockMapPos(int contact_edge, float contact_pos, int index)
{
	switch (contact_edge)
	{
	case TOPEDGE:	//�`�b�v�̏�̕ӂɓ����������̏���
		g_Blocks[index].position.y = contact_pos - BLOCK_SIZE_Y * g_Blocks[index].High_Quantity;
		break;
	}
}


