#include <windows.h> // заголовочный файл, содержащий функции WIN API
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

// The main window class name.
static TCHAR szWindowClass[] = L"DesktopApp1";

// The string that appears in the application's title bar.
static TCHAR szTitle[] = L"А-13а-19 Кутдусов Руслан ЛР1";

// идентификатор управляющих элементов
const int UNIQUE_ID = 101; // для пункта меню
const int UQID_BUTT1 = 110; HWND butt1; // кнопка 1
const int UQID_BUTT2 = 111; HWND butt2; // кнопка 2
const int UQID_ED1 = 120; HWND ed1;  // поле ввода
const int UQID_ST1 = 125; HWND st1;  // поле вывода

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void ButtonMove(HWND);

int WINAPI WinMain(
   HINSTANCE hInstance,      // дескриптор текущего экземпляра окна
   HINSTANCE hPrevInstance,  // дескриптор предыдущего экземпляра окна
   LPSTR     lpCmdLine,      // указатель на командную строку
   int       nCmdShow        // показывает состояние окна
)
{ 
   WNDCLASSEX wcex;                                                  // структура WNDCLASSEX содержит информацию о классе окна
                                                                     // она используется с функциями RegisterClassEx и GetClassInfoEx
   wcex.cbSize         = sizeof(WNDCLASSEX);                         // устанавливает размер этой структуры, в байтах
   wcex.style          = CS_HREDRAW | CS_VREDRAW;                    // устанавливает стиль(и) класса
   wcex.lpfnWndProc    = WndProc;                                    // указатель на оконную процедуру
   wcex.cbClsExtra     = 0;                                          // устанавливает число дополнительных байт, которые размещаются вслед за структурой класса окна
   wcex.cbWndExtra     = 0;                                          // устанавливает число дополнительных байтов, которые размещаются вслед за экземпляром окна
   wcex.hInstance      = hInstance;                                  // дескриптор экземпляра, который содержит оконную процедуру для класса   
   wcex.hIcon          = (HICON)LoadImage(wcex.hInstance, L"icon2.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE);  
   // дескриптор значка класса. Этот член структуры должен быть дескриптором ресурса значка
   wcex.hIconSm        = (HICON)LoadImage(wcex.hInstance, L"icon1.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE);  
   // дескриптор маленького значка, который связан с классом окна
   wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);                // дескриптор курсора класса. Этот член структуры должен быть дескриптором ресурса курсора
   wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);                   // дескриптор кисти фона класса
   wcex.lpszMenuName   = NULL;                                       // указатель на символьную строки, которая устанавливает имя ресурса меню класса, которое как имя показывается в файле ресурса
   wcex.lpszClassName  = szWindowClass;                              // символьная строка, она задает имя класса окна

   if (!RegisterClassEx(&wcex))
   { // функция RegisterClassEx регистрирует класс окна для последующего использования
      MessageBox(NULL,
         L"Call to RegisterClassEx failed!",
         szTitle,
         NULL);
      return 1;
   }

   HMENU hmn = CreatePopupMenu();
   AppendMenu(hmn, MF_CHECKED, UNIQUE_ID, L"NEW MARK");

   HWND hWnd = CreateWindowEx(
      WS_EX_OVERLAPPEDWINDOW,       // an optional extended window style
      szWindowClass,                // the name of the application
      szTitle,                      // the text that appears in the title bar
      WS_OVERLAPPEDWINDOW,          // the type of window to create
      50, 50,                       // initial position (x, y)
      400, 300,                     // initial size (width, length)
      NULL,                         // the parent of this window
      hmn,                          // menu bar
      hInstance,                    // the first parameter from WinMain
      NULL                          // not used in this application
   );

   if (!hWnd)
   {
      MessageBox(NULL,
         L"Call to CreateWindow failed!",
         szTitle,
         NULL);

      return 1;
   }

        butt1 = CreateWindowEx(WS_EX_WINDOWEDGE, L"BUTTON", L"ВЫПОЛНИТЬ 1", WS_VISIBLE | WS_CHILD,
            50, 50, 100, 100, hWnd, (HMENU)UQID_BUTT1, hInstance, NULL);
        butt2 = CreateWindowEx(WS_EX_WINDOWEDGE, L"BUTTON", L"ВЫПОЛНИТЬ 2", WS_VISIBLE | WS_CHILD,
            50, 200, 100, 100, hWnd, (HMENU)UQID_BUTT2, hInstance, NULL);
        ed1   = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"input", WS_VISIBLE | WS_CHILD | ES_LEFT,
            200, 50, 200, 30, hWnd, (HMENU)UQID_ED1, hInstance, NULL);
        st1   = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"output", WS_VISIBLE | WS_CHILD | ES_LEFT,
            200, 200, 200, 40, hWnd, (HMENU)UQID_ST1, hInstance, NULL);

   RECT WRect;
   const int g_1 = 150;
   const int g_2 = 100;
   GetWindowRect(hWnd, &WRect); // получим координаты окна 
   HRGN Rgn1 = CreateEllipticRgn(-g_1, -g_1, WRect.right - WRect.left + g_1, WRect.bottom - WRect.top);
   HRGN Rgn2 = CreateEllipticRgn(g_1 + g_2, g_1, WRect.bottom - WRect.top - g_1 + g_2, WRect.bottom - WRect.top - g_1);
   CombineRgn(Rgn1, Rgn1, Rgn2, RGN_XOR); // наложение регионов друг на друга и удаление кружка
   SetWindowRgn(hWnd, Rgn1, FALSE);

   // hWnd: the value returned from CreateWindow
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

//  processes messages for the main window
LRESULT CALLBACK WndProc(HWND hWnd,     // дескриптор окна
                         UINT message,  // сообщение, посылаемое операционной системой
                         WPARAM wParam, // параметры
                         LPARAM lParam) // сообщений, для последующего обращения
{
   TCHAR buf[100] = { 0 }; 
   switch (message)
   {
   case WM_CREATE: 
      SetWindowText(st1, _T("CREATE"));
      MoveWindow(
          hWnd, // дескриптор окна
          100,  // новая позиция по горизонтали
          100,  // новая позиция по вертикали
          450,  // новая ширина
          400,  // новая высота
          FALSE // флажок перекраски
      );
      break;
   case WM_RBUTTONDOWN:
      SetWindowText(st1, _T("RIGHT MOUSE BUTTON"));
      SetParent(butt1, hWnd);
      MoveWindow(butt1, 50, 50, 100, 100, FALSE);
      break;
   case WM_LBUTTONDOWN:
      SetWindowText(st1, _T("LEFT MOUSE BUTTON"));
      SetWindowPos(butt1, HWND_TOP, 0, 0, 100, 100, SWP_SHOWWINDOW);
      SetParent(butt1, NULL);
      ButtonMove(butt1);
      break;
   case WM_COMMAND:
       switch (wParam)
       {
       case UQID_BUTT1: // первая кнопка
           GetWindowText(ed1, buf, 100); // читаем из поля ввода
           SetWindowText(st1, buf);      // записываем в поле вывода
           break;
       case UQID_BUTT2: // вторая кнопка
           GetWindowText(hWnd, buf, 100); // читаем заголовок главного окна
           SetWindowText(st1, buf); // записываем заголовок в поле вывода
           break;
       case UNIQUE_ID:
           SetWindowText(st1, _T("NEW MARK")); // кликаем на пункт меню
       default:
           return DefWindowProc(hWnd, message, wParam, lParam);
       }
       break;
   case WM_DESTROY:
      SetWindowText(st1, _T("DESTROY"));
      PostQuitMessage(0);
      break;
   default:
      return DefWindowProc(hWnd, message, wParam, lParam); // вызывается оконной процедурой по умолчанию, чтобы обеспечить обработку 
                                                           // по умолчанию любого сообщения окна, которые приложение не обрабатывает
   }
   return 0;
}

void ButtonMove(HWND button)
{
    int i = 0;
    for (; i <= 750; ++i)
    {
      SetWindowTextW(button, L"Выполнить 1");
      MoveWindow(button, i, i, 100, 100, FALSE);
      Sleep(10);

    }       
    for (; i >= 0; --i)
    {
      SetWindowTextW(button, L"Выполнить 1");
      MoveWindow(button, i, i, 100, 100, FALSE);
      Sleep(10);
    }
}
