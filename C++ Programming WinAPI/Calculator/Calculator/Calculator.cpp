// Calculator.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Calculator.h"
#include "Fraction.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
BOOL CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	hInst = hInstance;
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, WndProc);
}

BOOL CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDB_CALCULATE:
		{
			HWND operand1 = GetDlgItem(hWnd, IDC_OPERAND1);

			HWND operator1 = GetDlgItem(hWnd, IDC_OPERATOR);

			HWND operand2 = GetDlgItem(hWnd, IDC_OPERAND2);

			HWND solution = GetDlgItem(hWnd, IDC_SOLUTION);

			int len = 10;
			TCHAR *t = new TCHAR[len];

			GetWindowText(operand1, t, len);
			Fraction f1(_tstoi(t));

			GetWindowText(operand2, t, len);
			Fraction f2(_tstoi(t));

			GetWindowText(operator1, t, len);
			Fraction f3;
			if (_tcscmp(t, TEXT("+")) == 0)
			{
				f3 = f1 + f2;
			}
			else if (_tcscmp(t, TEXT("-")) == 0)
			{
				f3 = f1 - f2;
			}
			else if (_tcscmp(t, TEXT("*")) == 0)
			{
				f3 = f1 * f2;
			}
			else if (_tcscmp(t, TEXT("/")) == 0)
			{
				f3 = f1 / f2;
			}
			_stprintf_s(t, len ,TEXT("%f"), f3.GetValue());
			SetWindowText(solution, t);
		}
		break;
		case IDM_EXIT:
			EndDialog(hWnd, 0);
			break;
		}
		break;
	}
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		break;
	}
    return 0;
}