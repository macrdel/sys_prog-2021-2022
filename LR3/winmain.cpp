#include <windows.h> // заголовочный файл, содержащий функции WIN API
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

// The main window class name.
static TCHAR szWindowClass[] = TEXT("DesktopApp3");

// The string that appears in the application's title bar.
static TCHAR szTitle[] = TEXT("А-13а-19 Кутдусов Руслан ЛР3");

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK RCN(HWND hWnd, LPARAM lParam);
BOOL CALLBACK RAW(HWND hWnd, LPARAM lParam);

const int IDM_LR2_VIS = 130;
const int IDM_BUILDER_VIS = 135;
const int IDM_DOTNET_VIS = 140;
const int IDM_LR2_ENAB = 145;
const int IDM_BUILDER_ENAB = 150;
const int IDM_DOTNET_ENAB = 155;
const int IDM_DOTNET_CL = 160;

HWND lr2;
HWND builder;
HWND dotnet;

HWND butt1; const int ID_LR2_POINT1 = 165;
HWND butt2; const int ID_LR2_POINT2 = 170;
HWND butt3; const int ID_LR2_POINT5 = 175;
HWND butt4; const int ID_RENAMEALL = 180;
bool window_move = false;
int count = 0;

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

	HMENU hMenubar = CreateMenu();
	HMENU hMenu1 = CreateMenu();
	HMENU hMenu2 = CreateMenu();

	AppendMenu(hMenu1, MF_STRING, IDM_LR2_VIS, _T("LR2"));
	AppendMenu(hMenu1, MF_STRING, IDM_BUILDER_VIS, _T("BUILDER"));
	AppendMenu(hMenu1, MF_STRING, IDM_DOTNET_VIS, _T("C#"));

	AppendMenu(hMenu2, MF_STRING, IDM_LR2_ENAB, _T("LR2"));
	AppendMenu(hMenu2, MF_STRING, IDM_BUILDER_ENAB, _T("BUILDER"));
	AppendMenu(hMenu2, MF_STRING, IDM_DOTNET_ENAB, _T("C#"));

	AppendMenu(hMenubar, MF_POPUP | MF_STRING, (UINT_PTR)hMenu1, _T("VISIBLE"));
	AppendMenu(hMenubar, MF_POPUP | MF_STRING, (UINT_PTR)hMenu2, _T("ENABLE"));
	AppendMenu(hMenubar, MF_STRING, IDM_DOTNET_CL, _T("CLOSE C#"));

	HWND hWnd = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,       // an optional extended window style
		szWindowClass,                // the name of the application
		szTitle,                      // the text that appears in the title bar
		WS_OVERLAPPEDWINDOW,          // the type of window to create
		50, 50,                       // initial position (x, y)
		400, 320,                     // initial size (width, length)
		NULL,                         // the parent of this window
		hMenubar,                     // menu bar
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

	butt1 = CreateWindowEx(WS_EX_WINDOWEDGE, _T("BUTTON"), _T("ВОЗВЕСТИ LR2"), WS_VISIBLE | WS_CHILD,
		30, 30, 150, 30, hWnd, (HMENU)ID_LR2_POINT1, hInstance, NULL);
	butt2 = CreateWindowEx(WS_EX_WINDOWEDGE, _T("BUTTON"), _T("ABOUT LR2"), WS_VISIBLE | WS_CHILD,
		30, 90, 150, 30, hWnd, (HMENU)ID_LR2_POINT2, hInstance, NULL);
	butt3 = CreateWindowEx(WS_EX_WINDOWEDGE, _T("BUTTON"), _T("Переименовать LR2"), WS_VISIBLE | WS_CHILD,
		30, 150, 150, 30, hWnd, (HMENU)ID_LR2_POINT5, hInstance, NULL);
	butt4 = CreateWindowEx(WS_EX_WINDOWEDGE, _T("BUTTON"), _T("Переименовать ВСЁ"), WS_VISIBLE | WS_CHILD,
		30, 210, 150, 30, hWnd, (HMENU)ID_RENAMEALL, hInstance, NULL);


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
	HWND lr2butt;
	HMENU lr2menu;
	POINT p;

	switch (message)
	{
	case WM_COMMAND:
		switch (vmId)
		{
		case IDM_LR2_VIS:
			if (!lr2) { // если дескриптор пустой, то ищем требуемое окно
				lr2 = FindWindow(/*L"DesktopApp2"*/ NULL, _T("А-13а-19 Кутдусов Руслан ЛР2"));
				if (lr2)
					ShowWindow(lr2, SW_SHOWDEFAULT); // и отображаем, если нашли
			}
			else
				if (!IsWindowVisible(lr2)) ShowWindow(lr2, SW_SHOWDEFAULT);
				else ShowWindow(lr2, SW_HIDE);
			break;
		case IDM_BUILDER_VIS:
			if (!builder) {
				builder = FindWindow(NULL, _T("Builder"));
				if (builder)
					ShowWindow(builder, SW_SHOWDEFAULT);
			}
			else
				if (!IsWindowVisible(builder)) ShowWindow(builder, SW_SHOWDEFAULT);
				else ShowWindow(builder, SW_HIDE);
			break;
		case IDM_DOTNET_VIS:
			if (!dotnet) {
				dotnet = FindWindow(NULL, _T("DotNET"));
				if (dotnet)
					ShowWindow(dotnet, SW_SHOWDEFAULT);
			}
			else
				if (!IsWindowVisible(dotnet)) ShowWindow(dotnet, SW_SHOWDEFAULT);
				else ShowWindow(dotnet, SW_HIDE);
			break;
		case IDM_LR2_ENAB:
			if (!lr2) {
				lr2 = FindWindow(/*L"DesktopApp2"*/ NULL, _T("А-13а-19 Кутдусов Руслан ЛР2"));
				if (lr2)
					ShowWindow(lr2, SW_SHOWDEFAULT);
			}
			else
				if (!IsWindowEnabled(lr2)) EnableWindow(lr2, true);
				else EnableWindow(lr2, false);
			break;
		case IDM_BUILDER_ENAB:
			if (!builder) {
				builder = FindWindow(NULL, _T("Builder"));
				if (builder)
					ShowWindow(builder, SW_SHOWDEFAULT);
			}
			else
				if (!IsWindowEnabled(builder)) EnableWindow(builder, true);
				else EnableWindow(builder, false);
			break;
		case IDM_DOTNET_ENAB:
			if (!dotnet) {
				dotnet = FindWindow(NULL, _T("DotNET"));
				if (dotnet)
					ShowWindow(dotnet, SW_SHOWDEFAULT);
			}
			else
				if (!IsWindowEnabled(dotnet)) EnableWindow(dotnet, true);
				else EnableWindow(dotnet, false);
			break;
		case IDM_DOTNET_CL:
			if (dotnet && IsWindowEnabled(dotnet)) {
				SendMessage(dotnet, WM_DESTROY, 0, 0);
				dotnet = NULL;
			}
			break;
		case ID_LR2_POINT1:
			if (lr2 && IsWindowEnabled(lr2)) {
				lr2butt = FindWindowEx(lr2, NULL, NULL, _T("ВОЗВЕСТИ"));
				if (lr2butt) {
					// 1
					/*SendMessage(lr2butt, WM_LBUTTONDOWN, MK_LBUTTON, 0);
					SendMessage(lr2butt, WM_LBUTTONUP, 0, 0);*/
					// 2
					// SendMessage(lr2butt, BM_CLICK, 0, 0);
					// 3
					SendMessage(lr2butt, BM_SETSTATE, 1, 0);
					Sleep(100);
					SendMessage(lr2, WM_COMMAND, GetWindowLong(lr2butt, GWL_ID), 0);
					SendMessage(lr2butt, BM_SETSTATE, 0, 0);
				}
			}
			break;
		case ID_LR2_POINT2:
			if (lr2 && IsWindowEnabled(lr2)) {
				lr2menu = GetMenu(lr2);
				if (lr2menu)
					SendMessage(lr2, WM_COMMAND, GetMenuItemID(lr2menu, 0), 0);
			}
			break;
		case ID_LR2_POINT5:
			if (lr2 && IsWindowEnabled(lr2)) {
				EnumChildWindows(lr2, &RCN, 0);
				count = 0;
			}
			break;
		case ID_RENAMEALL:
			EnumWindows(&RAW, 0);
			count = 0;
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_RBUTTONDOWN:
		if (lr2 && IsWindowEnabled(lr2)) {
			p.x = LOWORD(lParam);
			p.y = HIWORD(lParam);
			ClientToScreen(hWnd, &p);
			ScreenToClient(lr2, &p);
			SendMessage(lr2, WM_RBUTTONDOWN, 0, MAKELONG(p.x, p.y));
		}
		break;
	case WM_LBUTTONDOWN:
		if (lr2 && IsWindowEnabled(lr2)) {
			window_move = true; // включаем флажок
			p.x = LOWORD(lParam);
			p.y = HIWORD(lParam);
			ClientToScreen(hWnd, &p);
			ScreenToClient(lr2, &p);
			SendMessage(lr2, WM_LBUTTONDOWN, 0, MAKELONG(p.x, p.y));
		}
		break;
	case WM_LBUTTONUP:
		window_move = false; // выключаем
		SendMessage(lr2, WM_LBUTTONUP, 0, 0);
		break;
	case WM_MOUSEMOVE:
		if (window_move) {
			p.x = LOWORD(lParam);
			p.y = HIWORD(lParam);
			ClientToScreen(hWnd, &p);
			ScreenToClient(lr2, &p);
			SendMessage(lr2, WM_MOUSEMOVE, 0, MAKELONG(p.x, p.y));
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam); // вызывается оконной процедурой по умолчанию, чтобы обеспечить обработку 
															 // по умолчанию любого сообщения окна, которые приложение не обрабатывает
	}
	return 0;
}

BOOL CALLBACK RCN(HWND hWnd, LPARAM lParam)
{
	++count;
	TCHAR buf[100] = { 0 };
	_itoa_s(count, buf, 10);
	strcat_s(buf, _T(" дочернее"));
	SendMessage(hWnd, WM_SETTEXT, 0, LPARAM(LPCSTR(buf)));
	return TRUE;
}

BOOL CALLBACK RAW(HWND hWnd, LPARAM lParam)
{
	++count;
	TCHAR buf[100] = { 0 };
	_itoa_s(count, buf, 10);
	strcat_s(buf, _T(" родительское"));
	SendMessage(hWnd, WM_SETTEXT, 0, LPARAM(LPCSTR(buf)));
	EnumChildWindows(hWnd, &RCN, 0);
	return TRUE;
}