#include <windows.h> // заголовочный файл, содержащий функции WIN API
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

// The main window class name.
static TCHAR szWindowClass[] = TEXT("DesktopApp2");

// The string that appears in the application's title bar.
static TCHAR szTitle[] = TEXT("А-13а-19 Кутдусов Руслан ЛР2");

const int UQID_BUTT1 = 110; HWND butt1;   // кнопка 1
const int UQID_BUTT2 = 111; HWND butt2;   // кнопка 2
const int UQID_ED1 = 120; HWND ed1;       // поле ввода
const int UQID_ST1 = 125; HWND st1;       // поле вывода 1
const int UQID_ST2 = 130; HWND st2;	      // поле вывода 2
const int UQID_ST3 = 135; HWND st3;       // поле вывода 3

static TCHAR msgs[1000] = { 0 }; // сюда запоминаются события левой кноки мыши
static int wm_nci_n = 0; // счётчик событий WM_NCHITTEST
static bool window_move = false; // флаг говорит о том, что левая клавиши мыши зажата
static POINT start;				 // стартовая точка для определения смещения

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

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

	HWND hWnd = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,       // an optional extended window style
		szWindowClass,                // the name of the application
		szTitle,                      // the text that appears in the title bar
		WS_OVERLAPPEDWINDOW,          // the type of window to create
		50, 50,                       // initial position (x, y)
		360, 400,                     // initial size (width, length)
		NULL,                         // the parent of this window
		NULL,                          // menu bar
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

	butt1 = CreateWindowEx(WS_EX_WINDOWEDGE, _T("BUTTON"), _T("ВОЗВЕСТИ"), WS_VISIBLE | WS_CHILD, 
		30, 30, 90, 30, hWnd, (HMENU)UQID_BUTT1, hInstance, NULL);
	butt2 = CreateWindowEx(WS_EX_WINDOWEDGE, _T("BUTTON"), _T("КНОПКА 2"), WS_VISIBLE | WS_CHILD,
		30, 80, 90, 30, hWnd, (HMENU)UQID_BUTT2, hInstance, NULL);
	ed1 = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T("1"), WS_VISIBLE | WS_CHILD | ES_LEFT,
		150, 30, 100, 30, hWnd, (HMENU)UQID_ED1, hInstance, NULL);
	st1 = CreateWindowEx(WS_EX_CLIENTEDGE, _T("STATIC"), _T("1"), WS_VISIBLE | WS_CHILD | ES_LEFT,
		150, 80, 100, 30, hWnd, (HMENU)UQID_ST1, hInstance, NULL);
	st2 = CreateWindowEx(WS_EX_CLIENTEDGE, _T("STATIC"), _T(""), WS_VISIBLE | WS_CHILD,
		30, 150, 280, 150, hWnd, (HMENU)UQID_ST2, hInstance, NULL);
	st3 = CreateWindowEx(WS_EX_CLIENTEDGE, _T("STATIC"), _T(""), WS_VISIBLE | WS_CHILD,
		30, 310, 280, 30, hWnd, (HMENU)UQID_ST3, hInstance, NULL);


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
	TCHAR number[100] = { 0 };
	int vmId = LOWORD(wParam);
	int num = 0;
	POINT p;				// переменная для хранения координат
	TCHAR x[20] = { 0 };
	TCHAR y[10] = { 0 };
	TCHAR nci[20] = { 0 };
	RECT rect;				// переменная для хранения прямоугольника окна
	switch (message)
	{
	case WM_COMMAND:
		switch (vmId)
		{
		case UQID_BUTT1:
			GetWindowText(ed1, number, 100);
			num = atoi(number);
			_itoa_s(num * num, number, 10);
			SetWindowText(st1, number);
			break;
		case UQID_BUTT2:
			// 1
			/*SendMessage(butt1, WM_LBUTTONDOWN, MK_LBUTTON, 0);
			SendMessage(butt1, WM_LBUTTONUP, 0, 0);*/
			// 2
			SendMessage(butt1, BM_CLICK, 0, 0);
			// 3
			/*SendMessage(hWnd, WM_COMMAND, UQID_BUTT1, 0);
			SendMessage(butt1, BM_SETSTATE, 1, 0);
			Sleep(100);
			SendMessage(butt1, BM_SETSTATE, 0, 0);*/
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_RBUTTONDOWN:
		p.x = LOWORD(lParam);
		p.y = HIWORD(lParam);
		_itoa_s(p.x, x, 10);
		_itoa_s(p.y, y, 10);
		strcat_s(x, _T(" - x; "));
		strcat_s(y, _T(" - y."));
		strcat_s(x, y);
		SetWindowText(st2, x);
		break;
	case WM_LBUTTONDOWN:
		window_move = true; // включаем флажок
		GetWindowRect(hWnd, &rect); // координаты прямоугольника окна
		start.x = LOWORD(lParam) - rect.left; // определяем стартовую позицию
		start.y = HIWORD(lParam) - rect.top;
		ClientToScreen(hWnd, &start);         // клиентские координты стартовой точки в экранные
		strcat_s(msgs, _T("LBUTTONDOWN\n"));
		SetWindowText(st2, msgs);
		break;
	case WM_LBUTTONUP:
		window_move = false; // выключаем флажок
		strcat_s(msgs, _T("LBUTTONUP\n"));
		SetWindowText(st2, msgs);
		break;
	case WM_LBUTTONDBLCLK:
		strcat_s(msgs, _T("LBUTTONDBLCLK\n"));
		SetWindowText(st2, msgs);
		break;
	case WM_NCHITTEST:
		wm_nci_n++;
		_itoa_s(wm_nci_n, nci, 10);
		strcat_s(nci, _T(" NCHITTEST"));
		SetWindowText(st3, nci);
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	case WM_MOUSEMOVE:
		if (window_move) {
			p.x = LOWORD(lParam);			// текущие координаты курсора
			p.y = HIWORD(lParam);
			ClientToScreen(hWnd, &p);		// переводим в экранные
			SetWindowPos(hWnd, HWND_TOP, p.x - start.x, p.y - start.y, 0, 0, SWP_NOSIZE | SWP_SHOWWINDOW);
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