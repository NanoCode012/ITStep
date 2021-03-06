// WINDOWS.H file contains the definitions, macros and structures
// used during writing of applications for Windows
#include "stdafx.h"
//window procedure prototype
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
TCHAR szClassWindow[] = TEXT("framework application");
/* Name of window class*/
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR
	lpszCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG lpMsg;
	WNDCLASSEX wcl;
	/* 1. Definition of window class */
	wcl.cbSize = sizeof(wcl);// размер структуры WNDCLASSEX
							 // Redraw the whole window if size was changed horizontally
							 // or vertically
	wcl.style = CS_HREDRAW | CS_VREDRAW;
	// CS(Class Style) – class style of window
	wcl.lpfnWndProc = WindowProc; // address of window procedure
	wcl.cbClsExtra = 0; // Windows is used
	wcl.cbWndExtra = 0; // Windows is used
	wcl.hInstance = hInst; // handle of this application
						   // loading of standard icon
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	// loading of standard cursor
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);
	// filling of window with white color
	wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcl.lpszMenuName = NULL; //application does not contain the menu
	wcl.lpszClassName = szClassWindow; //window class name
	wcl.hIconSm = NULL; // absence of small icon
						/* 2. Registry of window class */
	if (!RegisterClassEx(&wcl))
		return 0; // in case of unsuccessful registry – exit
				  /* 3. Window creation */
				  // creating a window and a variable hWnd is assigned
				  // with window handle
	hWnd = CreateWindowEx(
		0, // enhanced window style
		szClassWindow, // name of window class
		TEXT("Framework of Windows application"), // window header
		WS_OVERLAPPEDWINDOW, // window style
							 /* Header, frame, which allows changing the sizes, system
							 menu, buttons of window deployment and folding */
		CW_USEDEFAULT, // х-coordinate of upper left corner
					   // of the window
		CW_USEDEFAULT, // y-coordinate of upper left corner
					   // of the window
		CW_USEDEFAULT, // window width
		CW_USEDEFAULT, // window height
		NULL, // parent window handle
		NULL, // window menu handle
		hInst, // application ID, that created the window
		NULL); // pointer to the area of application data
			   /* 4. Window showing */
	ShowWindow(hWnd, nCmdShow);
	MoveWindow(hWnd, 0, 0, 500, 500, false);

	CreateWindowEx(0, TEXT("BUTTON"), TEXT("Hello"), WS_CHILD | WS_VISIBLE, 125, 125, 100, 100, hWnd, NULL, hInst, NULL);

	UpdateWindow(hWnd);// window redraw
					   /* 5. Start of messages processing cycle*/
					   // receiving another message from messages queue
	while (GetMessage(&lpMsg, NULL, 0, 0))
	{
		TranslateMessage(&lpMsg);// message translation
		DispatchMessage(&lpMsg); // message dispatching
	}
	return lpMsg.wParam;
}

static WORD x = 0;
static WORD y = 0;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam,
	LPARAM lParam)
{
	HDC hdc;
	HPEN hpen;
	WORD tempX, tempY;
	hdc = GetDC(hWnd);
	hpen = CreatePen(PS_DOT, 1, RGB(255, 0, 0));
	SelectObject(hdc, hpen);
	switch (uMessage)
	{
	/*case WM_PAINT:
		MoveToEx(hdc, 12, 12, NULL);
		TextOut(hdc, 35, 35, TEXT("Hi"), 3);
		LineTo(hdc, 100, 100);
		TextOut(hdc, 100, 100, TEXT("Hi"), 2);
		DefWindowProc(hWnd, uMessage, wParam, lParam);
		break;*/
	case WM_LBUTTONDOWN:
		/*Click twice to draw line
		tempX = LOWORD(lParam);
		tempY = HIWORD(lParam);
		if (x != 0 && y != 0)
		{
			MoveToEx(hdc, x, y, NULL);
			LineTo(hdc, tempX, tempY);
			x = 0;
			y = 0;
		}
		else
		{
			x = tempX;
			y = tempY;
		}*/
		
		/*Click and drag to draw line*/
		if (x == 0 && y == 0)
		{
			x = LOWORD(lParam);
			y = HIWORD(lParam);
		}
		DefWindowProc(hWnd, uMessage, wParam, lParam);
		break;
	case WM_LBUTTONUP:
		x = 0;
		y = 0;
		DefWindowProc(hWnd, uMessage, wParam, lParam);
		break;
	case WM_MOUSEMOVE:
		if (x != 0 && y != 0)
		{
			tempX = LOWORD(lParam);
			tempY = HIWORD(lParam);
			MoveToEx(hdc, x, y, NULL);
			LineTo(hdc, tempX, tempY);
			x = tempX;
			y = tempY;
			
		}
		DefWindowProc(hWnd, uMessage, wParam, lParam);
		break;
	case WM_DESTROY: // Quit message
		PostQuitMessage(0); // message sending WM_QUIT
		break;
	default:
		// all messages, which are not processing in this window
		// function return to Windows for default processing
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
	return 0;
}