#include <windows.h> // заголовочный файл, содержащий функции WIN API
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

// The main window class name.
static TCHAR szWindowClass[] = TEXT("DesktopApp5");

// The string that appears in the application's title bar.
static TCHAR szTitle[] = TEXT("А-13а-19 Кутдусов Руслан ЛР5");

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void RUS(HWND, HDC, int, int, int, int);
void draw_move_ellipse(HWND, HDC);

HWND dotnet;
HDC hDC;

HWND dsktp_wnd;

bool flag_1 = false;
bool flag_2 = false;
COLORREF main_color = (COLORREF)RGB(0, 255, 255);

HWND butt1; const int ID_RUSSIA = 113;
HWND butt2; const int ID_WND = 120;
HWND butt3; const int ID_WND_CLIENT = 125;
HWND butt4; const int ID_CSHARP = 130;
HWND butt5; const int ID_CSHARP_CLIENT = 135;
HWND butt6; const int ID_DSKTP_CLIENT = 140;
HWND butt9; const int ID_DSKTP = 142;
HWND butt7; const int ID_DRAWZONE = 145;
HWND butt8; const int ID_COLOR = 150;
HINSTANCE hInst;

bool clicked = false;
POINT point, old;
RECT draw_rect;
RECT r;
const int TIMER_1 = 155;
const int TIMER_2 = 160;
const int TIMER_3 = 165;
const int TIMER_4 = 170;
const int TIMER_5 = 175;
const int TIMER_6 = 180;
bool timer_1 = false;
bool timer_2 = false;
bool timer_3 = false;
bool timer_4 = false;
bool timer_5 = false;
bool timer_6 = false;

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
	
	hInst = hInstance;

	HWND hWnd = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,       // an optional extended window style
		szWindowClass,                // the name of the application
		szTitle,                      // the text that appears in the title bar
		WS_OVERLAPPEDWINDOW,          // the type of window to create
		100, 100,                       // initial position (x, y)
		700, 550,                     // initial size (width, length)
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

	butt1 = CreateWindowEx(WS_EX_WINDOWEDGE, _T("BUTTON"), _T("ФЛАГ"), WS_VISIBLE | WS_CHILD,
		150, 30, 200, 30, hWnd, (HMENU)ID_RUSSIA, hInst, NULL);
	butt2 = CreateWindowEx(WS_EX_WINDOWEDGE, _T("BUTTON"), _T("КРУГ КЛИЕНТ"), WS_VISIBLE | WS_CHILD,
		150, 90, 150, 30, hWnd, (HMENU)ID_WND, hInst, NULL);
	butt3 = CreateWindowEx(WS_EX_WINDOWEDGE, _T("BUTTON"), _T("КРУГ ПОВ-ТЬ"), WS_VISIBLE | WS_CHILD,
		150, 150, 150, 30, hWnd, (HMENU)ID_WND_CLIENT, hInst, NULL);
	butt4 = CreateWindowEx(WS_EX_WINDOWEDGE, _T("BUTTON"), _T("КРУГ КЛИЕНТ C#"), WS_VISIBLE | WS_CHILD,
		150, 210, 150, 30, hWnd, (HMENU)ID_CSHARP, hInst, NULL);
	butt5 = CreateWindowEx(WS_EX_WINDOWEDGE, _T("BUTTON"), _T("КРУГ ПОВ-ТЬ C#"), WS_VISIBLE | WS_CHILD,
		150, 270, 150, 30, hWnd, (HMENU)ID_CSHARP_CLIENT, hInst, NULL);
	butt6 = CreateWindowEx(WS_EX_WINDOWEDGE, _T("BUTTON"), _T("КРУГ РАБ. СТОЛ"), WS_VISIBLE | WS_CHILD,
		150, 330, 150, 30, hWnd, (HMENU)ID_DSKTP, hInst, NULL);
	butt7 = CreateWindowEx(WS_EX_WINDOWEDGE, _T("BUTTON"), _T("РИС. ОБЛАСТЬ"), WS_VISIBLE | WS_CHILD,
		150, 400, 150, 30, hWnd, (HMENU)ID_DRAWZONE, hInst, NULL);
	butt8 = CreateWindowEx(WS_EX_WINDOWEDGE, _T("BUTTON"), _T("СМЕНИТЬ ЦВ."), WS_VISIBLE | WS_CHILD,
		150, 460, 150, 30, hWnd, (HMENU)ID_COLOR, hInst, NULL);
	butt9 = CreateWindowEx(WS_EX_WINDOWEDGE, _T("BUTTON"), _T("РАБ. СТОЛ ПОВЕРХНОСТЬ"), WS_VISIBLE | WS_CHILD,
		320, 330, 150, 30, hWnd, (HMENU)ID_DSKTP, hInst, NULL);
	

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
	HDC dsktp_dc;
	COLORREF col_1;
	HPEN my_pen_1;
	HBRUSH my_brush_1;
	RECT rect;
	POINT cur;
	

	switch (message)
	{
	case WM_CREATE:
		dsktp_wnd = GetDesktopWindow();
		break;
	case WM_COMMAND:
		switch (vmId)
		{
		case ID_RUSSIA:
			if (dsktp_wnd) {
				RUS(hWnd, GetDC(hWnd), 350, 350, 470, 470);
				RUS(hWnd, GetWindowDC(hWnd), 0, 0, 120, 120);
				RUS(dsktp_wnd, GetDC(dsktp_wnd), 0, 0, 120, 120);
			}
			break;
		case ID_WND_CLIENT: // клиентская область главного окна
			if (!timer_1) {
				timer_1 = true;
				r.left = r.top = 0;
				r.right = r.bottom = 50;
				SetTimer(hWnd, TIMER_1, 200, NULL);
			}
			else {
				timer_1 = false;
				KillTimer(hWnd, TIMER_1);
				InvalidateRect(hWnd, &r, true);
				UpdateWindow(hWnd);
			}
			break;
		case ID_WND: // поверхность главного окна
			if (!timer_2) {
				timer_2 = true;
				r.left = r.top = 0;
				r.right = r.bottom = 50;
				SetTimer(hWnd, TIMER_2, 200, NULL);
			}
			else {
				timer_2 = false;
				KillTimer(hWnd, TIMER_2);
			}
			break;
		case ID_CSHARP_CLIENT: // клиентская область окна C#
			if (!dotnet) {
				dotnet = FindWindow(NULL, _T("DotNET"));
				if (dotnet)
					ShowWindow(dotnet, SW_SHOWDEFAULT);
			}
			else {
				if (!timer_3) {
					timer_3 = true;
					r.left = r.top = 0;
					r.right = r.bottom = 50;
					SetTimer(hWnd, TIMER_3, 200, NULL);
				}
				else {
					timer_3 = false;
					KillTimer(hWnd, TIMER_3);
				}
			}
			break;
		case ID_CSHARP: // поверхность C#
			if (!dotnet) {
				dotnet = FindWindow(NULL, _T("DotNET"));
				if (dotnet)
					ShowWindow(dotnet, SW_SHOWDEFAULT);
			}
			else {
				if (!timer_4) {
					timer_4 = true;
					r.left = r.top = 0;
					r.right = r.bottom = 50;
					SetTimer(hWnd, TIMER_4, 200, NULL);
				}
				else {
					timer_4 = false;
					KillTimer(hWnd, TIMER_4);
				}
			}
			break;
		case ID_DSKTP_CLIENT: // клиентская область окна рабочего стола
			if (!timer_5) {
				timer_5 = true;
				r.left = r.top = 0;
				r.right = r.bottom = 50;
				SetTimer(hWnd, TIMER_5, 200, NULL);
			}
			else {
				timer_5 = false;
				KillTimer(hWnd, TIMER_5);
			}
			break;
		case ID_DSKTP: // поверхность окна рабочего стола
			if (!timer_6) {
				timer_6 = true;
				r.left = r.top = 0;
				r.right = r.bottom = 50;
				SetTimer(hWnd, TIMER_6, 200, NULL);
			}
			else {
				timer_6 = false;
				KillTimer(hWnd, TIMER_6);
			}
			break;
		case ID_DRAWZONE:
			if (hDC) {
				/*rect = RECT{ 330, 90, 650, 480 };
				InvalidateRect(hWnd, &rect, true);*/
				SetROP2(hDC, R2_COPYPEN);
				SelectObject(hDC, CreatePen(PS_SOLID, 3, RGB(0, 0, 0)));
				SelectObject(hDC, CreateSolidBrush(RGB(255, 255, 255)));
				Rectangle(hDC, 330, 90, 650, 480);
			}
			break;
		case ID_COLOR:
			if (main_color == (COLORREF)RGB(0, 255, 255)) {
				main_color = (COLORREF)RGB(255, 255, 0);
			}
			else {
				main_color = (COLORREF)RGB(0, 255, 255);
			}
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;

	case WM_LBUTTONDOWN:
		if (hDC) {
			point.x = LOWORD(lParam);
			point.y = HIWORD(lParam);
			if (point.x >= 330 && point.x <= 650 && point.y <= 480 && point.y >= 90) {
				clicked = true;
				MoveToEx(hDC, point.x, point.y, NULL);
				SelectObject(hDC, CreatePen(PS_SOLID, 2, main_color));
				SetROP2(hDC, R2_NOTXORPEN);
			}
			old.x = point.x;
			old.y = point.y;
		}
		break;
	case WM_MOUSEMOVE:
		if (clicked) {
			cur.x = LOWORD(lParam);
			cur.y = HIWORD(lParam);
			if (cur.x >= 330 && cur.x <= 650 && cur.y <= 480 && cur.y >= 90) {
				LineTo(hDC, old.x, old.y);
				MoveToEx(hDC, point.x, point.y, NULL);
				LineTo(hDC, cur.x, cur.y);
				MoveToEx(hDC, point.x, point.y, NULL);
			}
			old.x = cur.x;
			old.y = cur.y;
		}
		break;
	case WM_LBUTTONUP:
		clicked = false;
		break;
	case WM_PAINT:
		PAINTSTRUCT ps;
		hDC = BeginPaint(hWnd, &ps);
		if (dsktp_wnd && flag_1) {
			dsktp_dc = GetDC(dsktp_wnd);
			col_1 = GetPixel(dsktp_dc, 50, 800);
			SelectObject(hDC, CreatePen(PS_SOLID, 8, RGB(0, 255, 255)));
			SelectObject(hDC, CreateSolidBrush(RGB(0, 255, 0)));
			GetWindowRect(hWnd, &rect);
			rect.top = rect.left = 0;
			FillRect(hDC, &rect, CreateSolidBrush(col_1));
			Rectangle(hDC, 100, 100, 200, 200);
			MoveToEx(hDC, 310, 310, NULL);
			LineTo(hDC, 200, 200);
			Ellipse(hDC, 300, 300, 400, 400);
			SetTextColor(hDC, RGB(255, 0, 0));
			TextOutW(hDC, 356, 126, L"TEXT", 30);
			ReleaseDC(dsktp_wnd, dsktp_dc);
		}
		EndPaint(hWnd, &ps);
		// ReleaseDC(hWnd, hDC);
		break;
	case WM_TIMER:
		switch (vmId) {
		case TIMER_1:
			draw_move_ellipse(hWnd, GetDC(hWnd));
			break;
		case TIMER_2:	
			draw_move_ellipse(hWnd, GetWindowDC(hWnd));
			break;
		case TIMER_3:
			draw_move_ellipse(dotnet, GetDC(dotnet));
			break;
		case TIMER_4:
			draw_move_ellipse(dotnet, GetWindowDC(dotnet));
			break;
		case TIMER_5:
			draw_move_ellipse(dsktp_wnd, GetDC(dsktp_wnd));
			break;
		case TIMER_6:
			draw_move_ellipse(dsktp_wnd, GetWindowDC(dsktp_wnd));
			break;
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

void RUS(HWND hWnd, HDC hDC, int x1, int y1, int x2, int y2)
{
	SelectObject(hDC, CreatePen(PS_SOLID, 1, RGB(0, 0, 0)));
	SelectObject(hDC, CreateSolidBrush(RGB(255, 255, 255)));
	Rectangle(hDC, x1, y1, x2, y2 - int(2 * (y2 - y1) / 3));
	SelectObject(hDC, CreateSolidBrush(RGB(0, 0, 255)));
	Rectangle(hDC, x1, y1 + int((y2 - y1) / 3), x2, y2 - int((y2 - y1) / 3));
	SelectObject(hDC, CreateSolidBrush(RGB(255, 0, 0)));
	Rectangle(hDC, x1, y1 + int( 2 * (y2 - y1) / 3), x2, y2);
	ReleaseDC(hWnd, hDC);
}

void draw_move_ellipse(HWND hWnd, HDC hDC)
{
	InvalidateRect(hWnd, &r, true);
	UpdateWindow(hWnd);
	SelectObject(hDC, CreatePen(PS_SOLID, 3, RGB(0, 255, 0)));
	SelectObject(hDC, CreateSolidBrush(RGB(255, 0, 0)));
	r.left += 2;
	r.right += 2;
	r.bottom += 2;
	r.top += 2;
	Ellipse(hDC, r.left, r.top, r.right, r.bottom);
	ReleaseDC(hWnd, hDC);
}