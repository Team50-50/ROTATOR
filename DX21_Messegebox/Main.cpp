/*==============================================================================

	MAIN
													Author : �g�E�~�����E
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
	�v���g�^�C�v�錾
------------------------------------------------------------------------------*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// �Q�[���̏������֐�
// �߂�l:�������Ɏ��s�����Ƃ�false
static bool Initialize(void);
// �Q�[���̍X�V�֐�
static void Update(void);
// �Q�[���̕`�揈��
static void Draw(void);
// �Q�[���̏I������
static void Finalize(void);

/*------------------------------------------------------------------------------
	�O���[�o���ϐ��錾
------------------------------------------------------------------------------*/
static HWND g_hWnd = NULL;						// �E�C���h�E�n���h��

static int g_FrameCount = 0;
static int g_BaseFrame = 0;
static double g_BaseTime = 0;
static double g_FPS = 0.0;
static double g_ReserveTime = 0.0;

int scene = SCENE_NONE;


/*------------------------------------------------------------------------------
	���C��
------------------------------------------------------------------------------*/
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// �E�C���h�E�N���X�\���̂̌���
	WNDCLASS wc = {};
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = CLASS_NAME; 
	wc.hInstance = hInstance; 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1); 

	RegisterClass(&wc);

	// XOR�Ńr�b�g��������Ƃ��̒��ӓ_
	// ���Ӓl�̉��������r�b�g���m���ɗ����Ă��邱�Ƃ�����

	// �E�C���h�E�̃X�^�C��
	DWORD window_style = WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX;
	// DWORD window_style = WS_OVERLAPPEDWINDOW &~ (WS_THICKFRAME | WS_MAXIMIZEBOX);

	// �s���̂����E�C���h�E�T�C�Y�̎Z�o
	RECT window_rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	AdjustWindowRect(&window_rect, window_style, FALSE);

	int window_width  = window_rect.right - window_rect.left;
	int window_height = window_rect.bottom - window_rect.top;

	// �\������E�C���h�E�̏ꏊ���Z�o����
	// �f�X�N�g�b�v�i�N���C�A���g�̈�j�̎擾

	// �f�o�C�X�i�V�X�e���j���烂�j�^�[�𑜓x���擾
	// �v���C�}�����j�^�[�̉�ʉ𑜓x�̎擾
	int desktop_width = GetSystemMetrics(SM_CXSCREEN);
	int desktop_height = GetSystemMetrics(SM_CYSCREEN);

	int window_x = max((desktop_width - window_width) / 2 , 0);
	int window_y = max((desktop_height - window_height) / 2, 0);

	// �E�C���h�E�̐���
	g_hWnd = CreateWindow(
		CLASS_NAME,
		WINDOW_CAPTION,
		window_style,	// �E�C���h�E�X�^�C��(�r�b�g�t���O)

		window_x,
		window_y,
		// �s���̂����E�C���h�E�T�C�Y��ݒ�
		window_width,
		window_height,

		// OS�ɃE�C���h�E�̍��W�Ƒ傫����C������@
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
		// �E�C���h�E�n���h�������炩�̗��R�Ő����ł��Ȃ�����
		return 0;//	�A�v���P�[�V�����̏I��
	}

	// �w��̃E�C���h�E�n���h���̃E�C���h�E���w��̕��@�ŕ\��
	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	SystemTimer_Initialize();

	
	g_FrameCount = g_BaseFrame = 0;
	g_FPS = 0.0;

	// �Q�[���̏�����
	if (!Initialize()) {
		// ���b�Z�[�W�{�b�N�X�Ŏ��s�������ߏI������|��`����
		MessageBox(NULL, "�������Ɏ��s�������߃A�v���P�[�V�������I�����܂��B", "�G���[", MB_OK);
		return 0;	// �A�v���P�[�V�����I��
	}

	// Windows�Q�[���p���C�����[�v
	MSG msg = {};
	while (WM_QUIT != msg.message)
	{
		double time = SystemTimer_GetTime();
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			// ���b�Z�[�W������ꍇ�̓��b�Z�[�W�D��
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			// �����ŃQ�[������
			
			if ((time - g_ReserveTime) < (1.0f / 60.0f)) {
				Sleep(0);	// CPU���x�܂���
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
   	�I������ 
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
		if (MessageBox(hWnd, "�{���ɏI�����Ă�낵���ł����H", "�m�F", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK) {
			DestroyWindow(hWnd);
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	};

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

// �Q�[���̏������֐�
// �߂�l:�������Ɏ��s�����Ƃ�false
bool Initialize(void)
{
	//�L�[�{�[�h�̏�����
	Keyboard_Initialize();

	//�L�[���K�[�̏�����
	Keylogger_Initialize();

	if (!MyDirect3D_Initialize(g_hWnd)) {
		MessageBox(NULL, "Direct3D�̏������Ɏ��s���܂����B", "�G���[", MB_OK);
		return false;
	}

	if (!InitInput())
	{
		//���̓f�o�C�X�̎擾�Ɏ��s
		MessageBox(NULL, "���̓f�o�C�X�̏����������s���܂���", "�G���[", MB_OK);

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

// �Q�[���̍X�V�֐�
void Update(void)
{
	//�L�[���K�[�̍X�V����
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
		
		//UpdateBG();			      // �w�i�̍X�V����
		//UpdatePlayer();		      // �v���C���[�̍X�V����
		//UpdateEnemy();            // �G�L�����̍X�V����
		//UpdateTama();             // �e�̍X�V����
		//Update_EnemyTama();       // �G�̒e�̍X�V����
		//Playertama_ifHIT_Enemy(); // �v���C���[�̒e�G�ɓ�����������
		//Enemytama_ifHIT_Player(); // �G�̒e�v���C���[�ɓ�����������
		////UpdateBall();		      // Ball�̍X�V����
		////UpdateScore();		      // �X�R�A�̍X�V����
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


	// �v��
	double time = SystemTimer_GetTime();
	if (time - g_BaseTime > 1.0) {
		g_FPS = (g_FrameCount - g_BaseFrame) / (time - g_BaseTime);
		g_BaseTime = time;
		g_BaseFrame = g_FrameCount;
	}
	g_FrameCount++;
}

// �Q�[���̕`�揈��
void Draw(void)
{
	// 1���ϐ��Ɋi�[
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	// �O�̂���pDevice��NULL�łȂ����Ƃ��m�F
	if (!pDevice) {
		return;
	}

	// ��ʂ̃N���A
	pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(100, 100, 100, 255), 1.0f, 0);

	// �`��o�b�`���߂̊J�n
	pDevice->BeginScene();

	// �Q�[���̕`�� *
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

		//UpdateBG();			      // �w�i�̍X�V����
		//UpdatePlayer();		      // �v���C���[�̍X�V����
		//UpdateEnemy();            // �G�L�����̍X�V����
		//UpdateTama();             // �e�̍X�V����
		//Update_EnemyTama();       // �G�̒e�̍X�V����
		//Playertama_ifHIT_Enemy(); // �v���C���[�̒e�G�ɓ�����������
		//Enemytama_ifHIT_Player(); // �G�̒e�v���C���[�ɓ�����������
		////UpdateBall();		      // Ball�̍X�V����
		////UpdateScore();		      // �X�R�A�̍X�V����
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

	// FPS�\��
	char buf[64];
	sprintf_s(buf, "FPS = %.2f", g_FPS);
	DebugFont_Draw(0.0f, 0.0f, buf);

	// �`��o�b�`���߂̏I��
	pDevice->EndScene();

	// �o�b�N�t���b�v(�^�C�~���O��D3DPRESENT_INTERVAL_DEFAULT)
	pDevice->Present(NULL, NULL, NULL, NULL);

}
// �Q�[���̏I������
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
	//�L�[���K�[�̏I������
	Keylogger_Finalize();
	ReleaseInput();
}

//	�V�[��(�X�e�[�W)�̐؂�ւ�����
void SetScene(int scene_no)
{
	// �܂����݂̃X�e�[�W�̏I�����������s
	switch (scene)
	{
	case SCENE_TITLE:
		UninitTitle();
		break;

	case SCENE_STAGECHOICE:
		UninitStageChoice();
		break;

	case SCENE_GAME:
		//UninitBlock();			// Block�̏I������
		//UninitBall();			// Ball�̏I������
		//Uninit_EnemyTama();     // �G�̒e�̏I������
		//UninitTama();           // �e�̏I������
		//UninitEnemy();          // �G�L�����̏I������
		//UninitPlayer();			// �v���C���[�̏I������
		//UninitScore();			// �X�R�A�̏I������
		//UninitBG();				// �w�i�̏I������
		UninitMap();
		UninitExplosion();
		UninitSniper();
		ReversionPlayer_Finalize();
		UninitKey();
		UninitDore();
		UninitBlock();
		UninitPlayer();			// �v���C���[�̏I������
		UninitBG();				// �w�i�̏I������
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
		//InitBG();				// �w�i�̏���������
		////InitScore();			// �X�R�A�̏�����
		//InitPlayer();			// �v���C���[�̏�����
		//InitTama();             // �e�̏�����
		//Init_EnemyTama();       // �G�̒e�̏�����
		////InitBall();				// Ball�̏�����
		////InitBlock();			// Block�̏�����
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