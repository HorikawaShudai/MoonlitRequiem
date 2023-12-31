//=========================================================================================================
//
//プロジェクト応用
//Author:堀川萩大
//
//=========================================================================================================
#include "main.h"
#include "Object.h"
//#include "Object2D.h"
#include "Renderer.h"
#include "Manager.h"

//マクロ定義
#define CLASS_NAME "WindowClass"		 //ウィンドウクラスの名前
#define WINDOW_NAME "MoonlitRequiem"	 //ウィンドウの名前
#define ID_BUTTON_FINISH		(101)	 //終了ボタン

//プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void Uninit(void);
void Update(void);
void Draw(void);
bool GetCursorVisibility();
void MoveCursorVisibility(HWND hWnd);
bool CursorVisual;

//=========================================================================================================
//メイン関数
//=========================================================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),				//WNDCLASSEXのメモリサイズ
		CS_CLASSDC,						//ウィンドウのスタイル
		WindowProc,						//ウィンドウプロシージャ
		0,								//0にする
		0,								//0にする
		hInstance,						//インスタンスハンドル
		LoadIcon(NULL,IDI_APPLICATION), //タスクバーのアイコン
		LoadCursor(NULL,IDC_ARROW),		//マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 0),		//クライアント領域の背景色
		NULL,							//メニューバー
		CLASS_NAME,						//ウィンドウクラスの名前
		LoadIcon(NULL,IDI_APPLICATION)	//ファイルのアイコン
	};

	HWND hWnd;	//ウィンドウハンドル(識別子)
	MSG msg;	//メッセージを格納する変数

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	//ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//ウィンドウを生成
	hWnd = CreateWindowEx(0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(rect.right - rect.left),
		(rect.bottom - rect.top),
		NULL,
		NULL,
		hInstance,
		NULL);
	DWORD dwCurrentTime;
	DWORD dwExectLastTime;

	CManager *pManager = NULL;
	pManager = CManager::GetInstance();
	//初期化処理
	if (FAILED(CManager::GetInstance()->Init(hInstance,hWnd, TRUE)))
	{
		return - 1;
	}
	timeBeginPeriod(1);
	dwCurrentTime = 0;
	dwExectLastTime = timeGetTime();
	//ウィンドウの表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (CursorVisual = ShowCursor(FALSE) >= 0);

	//メッセージループ
while (1)
{
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
	{//windowの処理
		if (msg.message == WM_QUIT)
		{
			break;
		}
		else
		{
			//メッセージ設定
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	else
	{//DirectXの処理
		dwCurrentTime = timeGetTime();
		if ((dwCurrentTime - dwExectLastTime) >= (1000 / 60))
		{
			//更新処理
			Update();
			pManager->Update();
			//描画処理
			Draw();
			pManager->Draw();
		}
	}
	MoveCursorVisibility(hWnd);

}

if (pManager != NULL)
{
	pManager->Uninit();
	delete pManager;
	pManager = NULL;
}



//ウィンドウクラスの登録解除
UnregisterClass(CLASS_NAME, wcex.hInstance);
return(int)msg.wParam;
}

//=========================================================================================================
//ウィンドウプロシージャ
//=========================================================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;
	int nAnswer = 0;

	switch (uMsg)
	{
	case WM_DESTROY://ウィンドウ破棄のメッセージ
					//WM_QUITにメッセージを送る
		PostQuitMessage(0);
		break;
		//case WM_CREATE://ボタンウィンドウ生成
		//	SetTimer(hWnd, ID_TIMER, TIMER_INTERVAL, NULL);
		//	break;

	case WM_KEYDOWN://キーが押された時
		switch (wParam)
		{
		case VK_ESCAPE: //ESCが押されたとき
			while (CursorVisual = ShowCursor(TRUE) < 0);

			nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);
			if (nID == IDYES)
			{//YESが押された場合
			 //ウィンドウを破棄する(WM_DESTROYメッセージを送る)
				DestroyWindow(hWnd);
				break;
			}
			else
			{
				while (CursorVisual = ShowCursor(FALSE) >= 0);

			}
		}
		break;

	case WM_CLOSE://×ボタンが押されたとき
		while (CursorVisual = ShowCursor(TRUE) < 0);

		nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);
		if (nID == IDYES)
		{//YESが押された場合
		 //ウィンドウを破棄する(WM_DESTROYメッセージを送る)
			DestroyWindow(hWnd);
		}
		else
		{//それ以外
			while (CursorVisual = ShowCursor(FALSE) >= 0);

			return 0;
		}
		break;

	case WM_LBUTTONDOWN: //マウスクリックのメッセージ
		SetFocus(hWnd);

		break;

	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);//既定の処理を返す
}

//====================================================
//終了処理
//====================================================
void Uninit(void)
{
	//分解能を戻す
	timeEndPeriod(1);
}

//====================================================
//更新処理
//====================================================
void Update(void)
{

}

//====================================================
//描画処理
//====================================================
void Draw(void)
{

}

void MoveCursorVisibility(HWND hWnd)
{
	if (GetCursorVisibility() == false)
	{
		RECT windowRect;
		GetClientRect(hWnd, &windowRect); // クライアント領域の座標を取得

		int centerX = (windowRect.right - windowRect.left) / 2;
		int centerY = (windowRect.bottom - windowRect.top) / 2;

		POINT centerPoint;
		centerPoint.x = centerX;
		centerPoint.y = centerY;

		ClientToScreen(hWnd, &centerPoint); // クライアント座標を画面座標に変換

		SetCursorPos(centerPoint.x, centerPoint.y); // カーソルを中心に移動
	}
	else if (GetCursorVisibility() == true)
	{

	}
	
}
bool GetCursorVisibility()

{
	return CursorVisual;
}