#include <windows.h> // заголовочный файл, содержащий функции WIN API
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include "resource.h"

// The main window class name.
static TCHAR szWindowClass[] = TEXT("DesktopApp5");

// The string that appears in the application's title bar.
static TCHAR szTitle[] = TEXT("А-13а-19 Кутдусов Руслан ЛР7");

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// HINSTANCE hInst;

HBITMAP hSky, hStar;

const int TIMER_1 = 185;
HWND butt1; const int ID_ANIM = 113;
HWND butt2; const int ID_CREATE = 118;
HWND butt3; const int ID_PLAY = 123;
bool anim = false;

HDC meta_dc;

HDC h_dc, h_comp_dc;

int x_0 = 0;
int y_0 = 0;
int x_h = -5;


int WINAPI WinMain(
	HINSTANCE hInstance,      // дескриптор текущего экземпляра окна
	HINSTANCE hPrevInstance,  // дескриптор предыдущего экземпляра окна
	LPSTR     lpCmdLine,      // указатель на командную строку
	int       nCmdShow        // показывает состояние окна
)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	// hInst = hInstance;
	wcex.hIcon = (HICON)LoadImage(wcex.hInstance, TEXT("icon.ico"), IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = (HICON)LoadImage(wcex.hInstance, TEXT("icon.ico"), IMAGE_ICON, 0, 0, LR_LOADFROMFILE);

	if (!RegisterClassEx(&wcex))
	{ // функция RegisterClassEx регистрирует класс окна для последующего использования
		MessageBox(NULL,
			TEXT("Call to RegisterClassEx failed!"),
			szTitle,
			NULL);
		return 1;
	}

	HWND hWnd = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,       // an optional extended window style
		szWindowClass,                // the name of the application
		szTitle,                      // the text that appears in the title bar
		WS_OVERLAPPEDWINDOW,          // the type of window to create
		100, 100,                       // initial position (x, y)
		810, 550,                     // initial size (width, length)
		NULL,                         // the parent of this window
		NULL,                     // menu bar
		hInstance,                    // the first parameter from WinMain
		NULL                          // not used in this application
	);

	if (!hWnd)
	{
		MessageBox(NULL,
			TEXT("Call to CreateWindow failed!"),
			szTitle,
			NULL);
		return 1;
	}

	butt1 = CreateWindowEx(WS_EX_WINDOWEDGE, _T("BUTTON"), _T("АНИМАЦИЯ"), WS_VISIBLE | WS_CHILD,
		550, 450, 200, 30, hWnd, (HMENU)ID_ANIM, hInstance, NULL);

	butt2 = CreateWindowEx(WS_EX_WINDOWEDGE, _T("BUTTON"), _T("СОЗДАТЬ"), WS_VISIBLE | WS_CHILD,
		550, 400, 200, 30, hWnd, (HMENU)ID_CREATE, hInstance, NULL);
	butt3 = CreateWindowEx(WS_EX_WINDOWEDGE, _T("BUTTON"), _T("ПРОИГРАТЬ"), WS_VISIBLE | WS_CHILD,
		550, 350, 200, 30, hWnd, (HMENU)ID_PLAY, hInstance, NULL);

	hSky = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP2));
	hStar = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP1));

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// Main message loop
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) //  извлекаем сообщения из очереди, посылаемые фу-циями, ОС
	{
		TranslateMessage(&msg); // интерпретируем сообщения
		DispatchMessage(&msg);  // передаём сообщения обратно ОС
	}
	return (int)msg.wParam; // код выхода из приложения
}


LRESULT CALLBACK WndProc(HWND hWnd,     // дескриптор окна
	UINT message,  // сообщение, посылаемое операционной системой
	WPARAM wParam, // параметры
	LPARAM lParam) // сообщений, для последующего обращения
{
	int vmId = LOWORD(wParam);
	// PAINTSTRUCT ps;
	RECT rect;

	switch (message)
	{
	case WM_TIMER:
		if (x_0 <= -750) x_h = -x_h;
		SelectObject(h_comp_dc, hSky);
		BitBlt(h_dc, 0, 0, 810, 550, h_comp_dc, 0, 0, SRCCOPY);
		SelectObject(h_comp_dc, hStar);
		BitBlt(h_dc, 0, 0, 810, 550, h_comp_dc, x_0, y_0, SRCPAINT);
		x_0 += x_h;
		if (x_0 == 0) x_h = -x_h;
		break;
	case WM_COMMAND:
		switch (vmId)
		{
		case ID_ANIM:
			anim = !anim;
			if (anim) {
				h_dc = GetDC(hWnd);
				h_comp_dc = CreateCompatibleDC(h_dc);
				SetTimer(hWnd, TIMER_1, 200, NULL);
			}
			else {
				KillTimer(hWnd, TIMER_1);
				DeleteDC(h_comp_dc);
				ReleaseDC(hWnd, h_dc);
			}
			break;
		case ID_CREATE:
			meta_dc = CreateMetaFile(L"metafile.wmf");
			if (meta_dc != NULL) {
				rect = {0, 0, 400, 400};
				FillRect(meta_dc, &rect, CreateSolidBrush(RGB(255, 255, 0)));
				SelectObject(meta_dc, CreateSolidBrush(RGB(128, 128, 0)));
				SelectObject(meta_dc, CreatePen(PS_SOLID, 2, RGB(255, 0, 255)));
				Ellipse(meta_dc, 10, 10, 100, 100);
				SelectObject(meta_dc, CreateSolidBrush(RGB(128, 0, 128)));
				SelectObject(meta_dc, CreatePen(PS_SOLID, 2, RGB(0, 255, 255)));
				Rectangle(meta_dc, 150, 150, 300, 300);
				CloseMetaFile(meta_dc);
			}
			break;
		case ID_PLAY:
			PlayMetaFile(GetDC(hWnd), GetMetaFile(L"metafile.wmf"));
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;

	/*case WM_PAINT:
		h_dc = BeginPaint(hWnd, &ps);
		if (anim) {
			h_comp_dc = CreateCompatibleDC(h_dc);
			SelectObject(h_comp_dc, hSky);
			BitBlt(h_dc, 0, 0, 810, 550, h_comp_dc, 0, 0, SRCCOPY);
		}
		EndPaint(hWnd, &ps);
		break;*/

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam); // вызывается оконной процедурой по умолчанию, чтобы обеспечить обработку 
															 // по умолчанию любого сообщения окна, которые приложение не обрабатывает
	}
	return 0;
}