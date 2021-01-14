#include <Windows.h>  
#include <d3d9.h> 
#include <d3dx9.h> 

#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT 720

enum {

	SCENE_TITLE,
	SCENE_STAGECHOICE,
	SCENE_GAME,
	SCENE_NONE,

};

void SetScene(int stage_no);