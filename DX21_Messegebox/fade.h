#pragma once

// フェードの状態
enum
{
	FADE_NONE = 0,		// 何もない状態
	FADE_IN,			// フェードイン処理
	FADE_OUT,			// フェードアウト処理
	FADE_MAX
};

void InitFade(void);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);

// Fade処理付きのシーン切り替え関数
void SetFade(int fade, int nextScene);