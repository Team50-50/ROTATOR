/*==============================================================================

	MAIN
													Author : トウミンヨウ
													Date   : 2020 / 07 / 21
													

==============================================================================*/
#include <stdio.h>
#include "Config.h"
#include "debug_font.h"
#include "Mydirect3d.h"
#include "system_timer.h"
#include "directinput.h"
#include "controller.h"
#include "keyboard.h"
#include "keylogger.h"
#include "Sprite.h"
#include "Main.h"
#include "stage.h"
#include "block.h"
#include "key.h"
#include "dore.h"
#include "revesion_player.h"

#include "bg.h"
#include "fade.h"
#include "title.h"
#include "stagechoice.h"
#include "player.h"
#include "camera.h"
#include "sniper.h"
#include "explosion.h"
#include "map.h"

/*------------------------------------------------------------------------------
	プロトタイプ宣言
------------------------------------------------------------------------------*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// ゲームの初期化関数
// 戻り値:初期化に失敗したときfalse
static bool Initialize(void);
// ゲームの更新関数
static void Update(void);
// ゲームの描画処理
static void Draw(void);
// ゲームの終了処理
static void Finalize(void);

/*------------------------------------------------------------------------------
	グローバル変数宣言
------------------------------------------------------------------------------*/
static HWND g_hWnd = NULL;						// ウインドウハンドル

static int g_FrameCount = 0;
static int g_BaseFrame = 0;
static double g_BaseTime = 0;
static double g_FPS = 0.0;
static double g_ReserveTime = 0.0;

int scene = SCENE_NONE;


/*------------------------------------------------------------------------------
	メイン
------------------------------------------------------------------------------*/
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// ウインドウクラス構造体の決定
	WNDCLASS wc = {};
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = CLASS_NAME; 
	wc.hInstance = hInstance; 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1); 

	RegisterClass(&wc);

	// XORでビットを下げるときの注意点
	// 左辺値の下げたいビットが確実に立っていることが条件

	// ウインドウのスタイル
	DWORD window_style = WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX;
	// DWORD window_style = WS_OVERLAPPEDWINDOW &~ (WS_THICKFRAME | WS_MAXIMIZEBOX);

	// 都合のいいウインドウサイズの算出
	RECT window_rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	AdjustWindowRect(&window_rect, window_style, FALSE);

	int window_width  = window_rect.right - window_rect.left;
	int window_height = window_rect.bottom - window_rect.top;

	// 表示するウインドウの場所を算出する
	// デスクトップ（クライアント領域）の取得

	// デバイス（システム）からモニター解像度を取得
	// プライマリモニターの画面解像度の取得
	int desktop_width = GetSystemMetrics(SM_CXSCREEN);
	int desktop_height = GetSystemMetrics(SM_CYSCREEN);

	int window_x = max((desktop_width - window_width) / 2 , 0);
	int window_y = max((desktop_height - window_height) / 2, 0);

	// ウインドウの生成
	g_hWnd = CreateWindow(
		CLASS_NAME,
		WINDOW_CAPTION,
		window_style,	// ウインドウスタイル(ビットフラグ)

		window_x,
		window_y,
		// 都合のいいウインドウサイズを設定
		window_width,
		window_height,

		// OSにウインドウの座標と大きさを任せる方法
		/*CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,*/

		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (g_hWnd == NULL) {
		// ウインドウハンドルが何らかの理由で生成できなかった
		return 0;//	アプリケーションの終了
	}

	// 指定のウインドウハンドルのウインドウを指定の方法で表示
	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	SystemTimer_Initialize();

	
	g_FrameCount = g_BaseFrame = 0;
	g_FPS = 0.0;

	// ゲームの初期化
	if (!Initialize()) {
		// メッセージボックスで失敗したため終了する旨を伝える
		MessageBox(NULL, "初期化に失敗したためアプリケーションを終了します。", "エラー", MB_OK);
		return 0;	// アプリケーション終了
	}

	// Windowsゲーム用メインループ
	MSG msg = {};
	while (WM_QUIT != msg.message)
	{
		double time = SystemTimer_GetTime();
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			// メッセージがある場合はメッセージ優先
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			// ここでゲーム処理
			
			if ((time - g_ReserveTime) < (1.0f / 60.0f)) {
				Sleep(0);	// CPUを休ませる
				continue;
			}

			g_ReserveTime = time;

			Update();
			Draw();
		}
	}

	Finalize();

	return (int)msg.wParam;
}


/*------------------------------------------------------------------------------
   	終了注意 
------------------------------------------------------------------------------*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) {
			SendMessage(hWnd, WM_CLOSE, 0, 0);
		}
	case WM_ACTIVATEAPP:
	case WM_SYSKEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
		Keyboard_ProcessMessage(uMsg, wParam, lParam);
		break;

	case WM_CLOSE:
		if (MessageBox(hWnd, "本当に終了してよろしいですか？", "確認", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK) {
			DestroyWindow(hWnd);
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	};

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

// ゲームの初期化関数
// 戻り値:初期化に失敗したときfalse
bool Initialize(void)
{
	//キーボードの初期化
	Keyboard_Initialize();

	//キーロガーの初期化
	Keylogger_Initialize();

	if (!MyDirect3D_Initialize(g_hWnd)) {
		MessageBox(NULL, "Direct3Dの初期化に失敗しました。", "エラー", MB_OK);
		return false;
	}

	if (!InitInput())
	{
		//入力デバイスの取得に失敗
		MessageBox(NULL, "入力デバイスの初期化が失敗しました", "エラー", MB_OK);

	}

	InitController();

	InitFade();
	SetScene(SCENE_TITLE);

	/*InitBG();
	InitPlayer();
	InitBlock();
	InitKey();
	InitDore();
	InitStage();
	ReversionPlayer_Initialize();
	InitSniper();
	InitExplosion();
	InitMap();*/

	Sprite_Initialize();
	DebugFont_Initialize();

	return true;
}

// ゲームの更新関数
void Update(void)
{
	//キーロガーの更新処理
	Keylogger_Update();

	switch (scene)
	{
	case SCENE_TITLE:
		UpdateTitle();
		break;

	case SCENE_STAGECHOICE:
		UpdateStageChoice();
		break;

	case SCENE_GAME:
		
		//UpdateBG();			      // 背景の更新処理
		//UpdatePlayer();		      // プレイヤーの更新処理
		//UpdateEnemy();            // 敵キャラの更新処理
		//UpdateTama();             // 弾の更新処理
		//Update_EnemyTama();       // 敵の弾の更新処理
		//Playertama_ifHIT_Enemy(); // プレイヤーの弾敵に当たった判定
		//Enemytama_ifHIT_Player(); // 敵の弾プレイヤーに当たった判定
		////UpdateBall();		      // Ballの更新処理
		////UpdateScore();		      // スコアの更新処理
		GameCamera_Update();
		UpdateController();
		UpdatePlayer();
		UpdateBlock();
		UpdateKey();
		UpdateDore();
		ReversionPlayer_Update();
		UpdateSniper();
		UpdateExplosion();
		UpdateMap();
		break;

	case SCENE_NONE:
		break;
	}

	//Game_Update();
	UpdateFade();


	// 計測
	double time = SystemTimer_GetTime();
	if (time - g_BaseTime > 1.0) {
		g_FPS = (g_FrameCount - g_BaseFrame) / (time - g_BaseTime);
		g_BaseTime = time;
		g_BaseFrame = g_FrameCount;
	}
	g_FrameCount++;
}

// ゲームの描画処理
void Draw(void)
{
	// 1次変数に格納
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	// 念のためpDeviceがNULLでないことを確認
	if (!pDevice) {
		return;
	}

	// 画面のクリア
	pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(100, 100, 100, 255), 1.0f, 0);

	// 描画バッチ命令の開始
	pDevice->BeginScene();

	// ゲームの描画 *
	//int* Gamemord = GetGamemord();

	switch (scene)
	{
	case SCENE_TITLE:
		DrawTitle();
		break;

	case SCENE_STAGECHOICE:
		DrawStageChoice();
		break;

	case SCENE_GAME:

		//UpdateBG();			      // 背景の更新処理
		//UpdatePlayer();		      // プレイヤーの更新処理
		//UpdateEnemy();            // 敵キャラの更新処理
		//UpdateTama();             // 弾の更新処理
		//Update_EnemyTama();       // 敵の弾の更新処理
		//Playertama_ifHIT_Enemy(); // プレイヤーの弾敵に当たった判定
		//Enemytama_ifHIT_Player(); // 敵の弾プレイヤーに当たった判定
		////UpdateBall();		      // Ballの更新処理
		////UpdateScore();		      // スコアの更新処理
		DrawBG();
		DrawMap();
		DrawPlayer();
		DrawBlock();
		DrawKey();
		DrawDore();
		ReversionPlayer_Draw();
		DrawSniper();
		DrawExplosion();
		break;

	case SCENE_NONE:
		break;
	}

	DrawFade();

	// FPS表示
	char buf[64];
	sprintf_s(buf, "FPS = %.2f", g_FPS);
	DebugFont_Draw(0.0f, 0.0f, buf);

	// 描画バッチ命令の終了
	pDevice->EndScene();

	// バックフリップ(タイミングはD3DPRESENT_INTERVAL_DEFAULT)
	pDevice->Present(NULL, NULL, NULL, NULL);

}
// ゲームの終了処理
void Finalize(void)
{
	//Game_Finalize();


	UninitBG();
	UninitPlayer();
	UninitBlock();
	UninitDore();
	UninitKey();
	ReversionPlayer_Finalize();
	UninitSniper();
	UninitExplosion();
	UninitMap();

	Sprite_Finalize();
	MyDirect3D_Finalize();
	//キーロガーの終了処理
	Keylogger_Finalize();
	ReleaseInput();
}

//	シーン(ステージ)の切り替え処理
void SetScene(int scene_no)
{
	// まず現在のステージの終了処理を実行
	switch (scene)
	{
	case SCENE_TITLE:
		UninitTitle();
		break;

	case SCENE_STAGECHOICE:
		UninitStageChoice();
		break;

	case SCENE_GAME:
		//UninitBlock();			// Blockの終了処理
		//UninitBall();			// Ballの終了処理
		//Uninit_EnemyTama();     // 敵の弾の終了処理
		//UninitTama();           // 弾の終了処理
		//UninitEnemy();          // 敵キャラの終了処理
		//UninitPlayer();			// プレイヤーの終了処理
		//UninitScore();			// スコアの終了処理
		//UninitBG();				// 背景の終了処理
		UninitMap();
		UninitExplosion();
		UninitSniper();
		ReversionPlayer_Finalize();
		UninitKey();
		UninitDore();
		UninitBlock();
		UninitPlayer();			// プレイヤーの終了処理
		UninitBG();				// 背景の終了処理
		break;

	case SCENE_NONE:
		break;
	}

	scene = scene_no;

	switch (scene)
	{
	case SCENE_TITLE:
		InitTitle();
		break;

	case SCENE_STAGECHOICE:
		InitStageChoice();
		break;

	case SCENE_GAME:
		//InitBG();				// 背景の初期化処理
		////InitScore();			// スコアの初期化
		//InitPlayer();			// プレイヤーの初期化
		//InitTama();             // 弾の初期化
		//Init_EnemyTama();       // 敵の弾の初期化
		////InitBall();				// Ballの初期化
		////InitBlock();			// Blockの初期化
		InitBG();
		InitPlayer();
		InitBlock();
		InitKey();
		InitDore();
		InitStage();
		ReversionPlayer_Initialize();
		InitSniper();
		InitExplosion();
		InitMap();
		break;

	case SCENE_NONE:
		break;
	}
}