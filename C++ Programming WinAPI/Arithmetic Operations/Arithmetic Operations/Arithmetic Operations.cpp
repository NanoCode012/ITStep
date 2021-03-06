// Arithmetic Operations.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Arithmetic Operations.h"
#include "RandomGenerator.h"

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

int sz = -1;
int arr[20];

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
				if (sz != -1)
				{
					LRESULT res = SendMessage(GetDlgItem(hWnd, IDC_RADIO1), BM_GETCHECK, 0, 0);
					HWND edit = GetDlgItem(hWnd, IDC_EDIT_SOLUTION);
					int len = 20;
					TCHAR *t = new TCHAR[len];
					if (res == BST_CHECKED)
					{
						int sum = 0;
						for (int i = 0; i < sz; i++) sum += arr[i];
					
						_stprintf_s(t, len, TEXT("%d"), sum);
						SetWindowText(edit, t);
					}
					else
					{
						res = SendMessage(GetDlgItem(hWnd, IDC_RADIO2), BM_GETCHECK, 0, 0);
						if (res == BST_CHECKED)
						{
							int product = 1;
							for (int i = 0; i < sz; i++) product *= arr[i];

							_stprintf_s(t, len, TEXT("%d"), product);
							SetWindowText(edit, t);
						}
						else
						{
							res = SendMessage(GetDlgItem(hWnd, IDC_RADIO3), BM_GETCHECK, 0, 0);
							if (res == BST_CHECKED)
							{
								int sum = 0;
								for (int i = 0; i < sz; i++) sum += arr[i];

								float average = (float)sum / (float)sz;
								_stprintf_s(t, len, TEXT("%0.2f"), average);
								SetWindowText(edit, t);
							}
						}
					}
				}
				break;
			}
			break;
			case IDB_RANDOMIZE:
			{
				HWND list = GetDlgItem(hWnd, IDC_LIST1);
				SendMessage(list, LB_RESETCONTENT, 0, 0);

				sz = RandomGenerator::GetRandomNumber(10, 20);

				int num = 0;
				TCHAR *t = new TCHAR[10];
				for (int i = 0; i < sz; i++)
				{
					num = RandomGenerator::GetRandomNumber(-10, 10);

					while(num == 0) num = RandomGenerator::GetRandomNumber(-10, 10);

					arr[i] = num;

					_stprintf_s(t, 10, TEXT("%d"), num);

					SendMessage(list, LB_ADDSTRING, 0, LPARAM(t));
				}

				delete[] t;
			}
				break;
			case IDCANCEL:
				EndDialog(hWnd, 0);
				break;
            }
        }
        break;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		break;
    }
    return 0;
}