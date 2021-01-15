/*==============================================================================

	再生プレイヤの制御[reversion_player.h]

													Author : マコウチュウ
													Date   :

==============================================================================*/
#ifndef REVERSION_PLAYER_H_
#define REVERSION_PLAYER_H_

#include<d3dx9.h>
#include"player.h"

/*-----------------------------------------------------------------------------------------
	定数宣言
-------------------------------------------------------------------------------------------*/
#define VPLAYER_MAX (3)

void ReversionPlayer_Initialize(void);

void ReversionPlayer_Finalize(void);

void ReversionPlayer_Update(void);

void ReversionPlayer_Draw(void);

#endif // !REVERSION_PLAYER_H__H_