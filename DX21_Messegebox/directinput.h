
#ifndef DIRECTINPUT_H_
#define DIRECTINPUT_H_

#include <dinput.h>

//入力デバイスの初期化
bool InitInput();

//入力デバイスの終了処理
void ReleaseInput();

// 入力インターフェースの作成
bool CreateInputInterface();

// ゲームパッドデバイスの作成
bool CreateGamePadDevice();

LPDIRECTINPUTDEVICE8 GamePad_GetDevice(void);

#endif
