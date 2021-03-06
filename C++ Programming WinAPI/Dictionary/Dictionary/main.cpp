// Dictionary.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include "Dictionary.h"

#define MAX_LOADTCHAR 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADTCHAR];                  // The title bar text
WCHAR szWindowClass[MAX_LOADTCHAR];            // the main window class name

// Forward declarations of functions included in this code module:
BOOL CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK WndProcAdd(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK WndProcModify(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	hInst = hInstance;
    return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_MAIN), NULL, WndProc);
}

Dictionary dictionary;

const char * pathKey = "../Dictionary/Keyword.txt";
const char * pathDefinition = "../Dictionary/Definition.txt";

int currentSelectedItem = -1;

HWND hMain;

void ShowWordsInList()
{
	HWND list = GetDlgItem(hMain, IDC_LIST);

	int sz = dictionary.GetSize();

	for (int i = 0; i < sz; i++)
	{
		SendMessage(list, LB_ADDSTRING, 0, LPARAM(dictionary.GetTitle(i)));
	}
}

void ClearList()
{
	HWND list = GetDlgItem(hMain, IDC_LIST);

	SendMessage(list, LB_RESETCONTENT, 0, 0);
}

void ShowNewList()
{
	ClearList();
	ShowWordsInList();
}

void Reset()
{
	dictionary.ReadFromFile(pathKey, pathDefinition);

	ShowNewList();
}

BOOL CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hMain = hWnd;
		Reset();
	}
	break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		int notifId = HIWORD(wParam);

		// Parse the menu selections:
		switch (wmId)
		{
		case IDC_BUTTON_ADD:
		{
			if (!dictionary.IsFull())
			{
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_WORD), hWnd, WndProcAdd);
			}
			else
			{
				MessageBox(hWnd, TEXT("Dictionary is full"), TEXT("FAIL"), MB_OK);
			}
		}
		break;
		case IDC_BUTTON_MODIFY:
		{
			if (currentSelectedItem >= 0)
			{
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_WORD), hWnd, WndProcModify);
			}
			else MessageBox(hWnd, TEXT("Please select a word you want to modify first"), TEXT("FAIL"), MB_OK);
		}
		break;
		case IDC_BUTTON_REMOVE:
		{
			if (currentSelectedItem >= 0)
			{
				int opt = MessageBox(hWnd, TEXT("Do you want to remove that entry?"), TEXT("Are you sure?"), MB_YESNO);
				if (opt == IDYES)
				{
					dictionary.RemoveWord(currentSelectedItem);

					ShowNewList();
				}
			}
		}
		break;
		case IDC_BUTTON_SEARCH:
		{
			int len = 100;
			TCHAR *t = new TCHAR[len];
			
			HWND hEdit = GetDlgItem(hWnd, IDC_SEARCHBOX);
			HWND list = GetDlgItem(hMain, IDC_LIST);

			GetWindowText(hEdit, t, len);

			int amount = dictionary.Search(t);

			ClearList();

			for (int i = 0; i < amount; i++)
			{
				SendMessage(list, LB_ADDSTRING, 0, LPARAM(dictionary.GetTitle(dictionary.GetSearchID(i))));
			}
		}
		break;
		case IDC_BUTTON_RESET:
		{
			Reset();
		}
		break;
		case ID_SAVE:
			dictionary.SaveToFile(pathKey, pathDefinition);
			break;
		case ID_QUIT:
		case IDM_EXIT:
			EndDialog(hWnd, 0);
			break;
		}

		switch (notifId)
		{
		case LBN_SELCHANGE:
		{
			currentSelectedItem = SendMessage(GetDlgItem(hWnd, IDC_LIST), LB_GETCURSEL, 0, 0);

			SetWindowText(GetDlgItem(hWnd, IDC_DEFINITION), dictionary.GetDefinition(currentSelectedItem));
		}
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

BOOL CALLBACK WndProcAdd(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);

		// Parse the menu selections:
		switch (wmId)
		{
		case IDOK:
		{
			HWND hKey = GetDlgItem(hWnd, IDC_KEYWORD);
			HWND hDef = GetDlgItem(hWnd, IDC_DEFINITION);

			int len = 100;

			TCHAR *t = new TCHAR[len];
			Word w;

			GetWindowText(hKey, t, len);
			w.SetTitle(t);

			GetWindowText(hDef, t, len);
			w.SetDefinition(t);

			dictionary.AddWord(w);
			dictionary.Sort(true);

			ShowNewList();
			
			delete[] t;

			EndDialog(hWnd, 0);
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

BOOL CALLBACK WndProcModify(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		HWND hKey = GetDlgItem(hWnd, IDC_KEYWORD);
		HWND hDef = GetDlgItem(hWnd, IDC_DEFINITION);

		SetWindowText(hKey, dictionary.GetTitle(currentSelectedItem));
		SetWindowText(hDef, dictionary.GetDefinition(currentSelectedItem));
	}
		break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);

		// Parse the menu selections:
		switch (wmId)
		{
		case IDOK:
		{
			HWND hKey = GetDlgItem(hWnd, IDC_KEYWORD);
			HWND hDef = GetDlgItem(hWnd, IDC_DEFINITION);

			int len = 100;

			TCHAR *t = new TCHAR[len];
			Word w;

			GetWindowText(hKey, t, len);
			dictionary.SetTitle(t, currentSelectedItem, true);

			GetWindowText(hDef, t, len);
			dictionary.SetDefinition(t, currentSelectedItem, true);

			dictionary.Sort(true);

			ShowNewList();

			delete[] t;

			EndDialog(hWnd, 0);
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