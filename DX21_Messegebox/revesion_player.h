/*==============================================================================

	�Đ��v���C���̐���[reversion_player.h]

													Author : �}�R�E�`���E
													Date   :

==============================================================================*/
#ifndef REVERSION_PLAYER_H_
#define REVERSION_PLAYER_H_

#include<d3dx9.h>
#include"player.h"

/*-----------------------------------------------------------------------------------------
	�萔�錾
-------------------------------------------------------------------------------------------*/
#define VPLAYER_MAX (3)

void ReversionPlayer_Initialize(void);

void ReversionPlayer_Finalize(void);

void ReversionPlayer_Update(void);

void ReversionPlayer_Draw(void);

#endif // !REVERSION_PLAYER_H__H_