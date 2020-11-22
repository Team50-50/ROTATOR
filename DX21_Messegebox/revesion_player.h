#ifndef REVERSION_PLAYER_H_
#define REVERSION_PLAYER_H_

#include<d3dx9.h>
#include"player.h"
#define VPLAYER_MAX (3)

typedef struct Virtual_player_tag
{
	D3DXVECTOR2 position;
	int frame;
	bool enable = false;
}ReversionPlayer;

void ReversionPlayer_Initialize(void);

void ReversionPlayer_Finalize(void);

void ReversionPlayer_Update(void);

void ReversionPlayer_Draw(void);

ReversionPlayer GetReversionPlayer(void);

#endif // !REVERSION_PLAYER_H__H_