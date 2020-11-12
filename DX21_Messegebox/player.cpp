
#include "Main.h"
#include "texture.h"
#include "Sprite.h"
#include "player.h"
#include "block.h"
#include "directinput.h"

//プレイヤーテクスチャー読み込み
static int	g_PlayerTexture;

//ブロック位置
D3DXVECTOR2	BlockPosition[BLOCK_MAX];

//プレイヤー位置情報
D3DXVECTOR2	g_PlayerPosition;

//プレイヤーを画面に描画する位置
D3DXVECTOR2	Draw_PlayerPosition;


static Queue g_qCurrent;
static Queue g_qPrev;
static Stack g_sCurrent;
static Stack g_sPrev;

//ジャンプ時の移動量
float	jump_amount;

//地面にプレイヤーがいるかどうか？
bool on_ground;

void InitPlayer()
{
	//プレイヤーのテクスチャ読み込み
	g_PlayerTexture = Texture_SetTextureLoadFile("asset/player.png");

	//プレイヤーの初期位置の定義
	g_PlayerPosition.x = ((SCREEN_WIDTH - PLAYER_SIZE_X) / 2);
	g_PlayerPosition.y = ((SCREEN_HEIGHT - PLAYER_SIZE_Y) * 7 / 10);

	//ジャンプ時の移動量を初期化
	jump_amount = 0;
	
}


void UninitPlayer()
{
	//テクスチャの解放
	Texture_Release(&g_PlayerTexture,1);

}


void UpdatePlayer()
{

	//Aを押して左に移動
	if (GetKeyState('A') & 0x80)
	{
		g_PlayerPosition.x -= 10.0f;//移動量

	}
	
	//Dを押して左に移動
	if (GetKeyState('D') & 0x80)
	{
		g_PlayerPosition.x += 10.0f;//移動量

	}
	
	//ジャンプ
	if (GetKeyState(VK_SPACE) & 0x80)
	{
		if (on_ground == true)
		{
			jump_amount = 16.0f;//ジャンプ量
		}

	}
	//===========================================
	//コントローラー
	//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
	if (IsButtonPush(LeftButton))
	{
		g_PlayerPosition.x -= 10.0f;//移動量
	}
	if (IsButtonPush(RightButton))
	{
		g_PlayerPosition.x += 10.0f;//移動量
	}
	if (IsButtonDown(ButtonB) || IsButtonPush(ButtonX) || IsButtonUp(ButtonY))
	{
		if (on_ground == true)
		{
			jump_amount = 16.0f;//ジャンプ量
		}
	}
	
	//重力を常に発生させる
	jump_amount -= 1.0f;

	//プレイヤー落下処理
	g_PlayerPosition.y -= jump_amount;
	
	//ブロックの位置座標を取得
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		BlockPosition[i] = GetBlockPosition(i);
	}

	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (g_PlayerPosition.x + PLAYER_SIZE_X > BlockPosition[i].x && g_PlayerPosition.x < BlockPosition[i].x + BLOCK_SIZE_X)
		{
			if (g_PlayerPosition.y >= BlockPosition[i].y - PLAYER_SIZE_Y)
			{
				on_ground = true;
				g_PlayerPosition.y = BlockPosition[i].y - PLAYER_SIZE_Y;
				jump_amount = 0;
			}
			else
			{
				on_ground = false;
			}
		}
		
	}

	//================================================================
	//スタック構造で、プレイヤーのpositionデータの更新処理を行う
	//================================================================
	if (!(GetKeyState('B') & 0x80))
	{
		//逆行してないときにプレイヤーのポジションを記録
		push(&g_sCurrent, g_PlayerPosition);
	}
	if (GetKeyState('B') & 0x80)
	{
		//Bキーを押し続けたら、そのフレームのデータ配列の末尾のプレイヤーpositionを取り出す
		//前のフレームのプレイヤーpositionデータとして記録する
		push(&g_sPrev, pop(&g_sCurrent));
	}

	//===========================================
	//コントローラー
	//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
	if (IsButtonPush(ButtonRT))
	{
		push(&g_sCurrent, g_PlayerPosition);
	}
	if (IsButtonPush(ButtonLT))
	{
		push(&g_sPrev, pop(&g_sCurrent));
	}
	
}


void DrawPlayer()
{
	
	//プレイヤーを画面中央に描画
	Sprite_Draw(g_PlayerTexture, ((SCREEN_WIDTH - PLAYER_SIZE_X) / 2), ((SCREEN_HEIGHT - PLAYER_SIZE_Y) * 7 / 10), PLAYER_SIZE_X, PLAYER_SIZE_Y,
	 0, 0, PLAYER_SIZE_X, PLAYER_SIZE_Y);
	

}


D3DXVECTOR2 GetPlayerPosition()
{
	return g_PlayerPosition;
}

//PUSH...positionデータをスタックに追加する
void push(Stack* stack, D3DXVECTOR2 playerPosition)
{
	if (stack->recordFrame > FRAME_MAX)
	{
		return;
	}
	stack->position_Data[stack->recordFrame] = playerPosition;

	stack->recordFrame++;
}

//POP...positionデータをスタックから取り出す、毎回最後 PUSH した positionデータからを取り出す
D3DXVECTOR2 pop(Stack* stack)
{
	D3DXVECTOR2 ret;

	//データがスタックから全部取り出された場合 (#バグの原因#)
	if (stack->recordFrame == 0)
	{
		return stack->position_Data[stack->recordFrame];
	}

	ret = stack->position_Data[stack->recordFrame - 1];

	stack->recordFrame--;

	return ret;
}

Stack GetstackPrev(void)
{
	return g_sPrev;
}

Stack GetstackCurrent(void)
{
	return g_sCurrent;
}