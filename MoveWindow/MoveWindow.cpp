/* Based on a post by "Null" on Jun 22, 2010 at http://www.cplusplus.com/forum/windows/25280/ */
#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <string>
#include <regex>

//using namespace std;

int x = 0, y = 0, width = -1, height = -1;
std::string title_regex;

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nFunsterStil)
{
	// Usage: MoveWindow.exe title_regex new_x_position new_y_position [new_width [new_height]]

	for (int i = 1; i < __argc; ++i)
	{
		std::string str(__argv[i]);

		switch (i)
		{
		case 1:
			title_regex = str;
			break;
		case 2:
			x = std::stoi(str);
			break;
		case 3:
			y = std::stoi(str);
			break;
		case 4:
			width = std::stoi(str);
			break;
		case 5:
			height = std::stoi(str);
			break;
		default:
			break;
		}
	}

	EnumWindows(EnumWindowsProc, NULL);

	return 0;
}


BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{

	//wchar_t class_name[80];
	wchar_t title[80];
	title[0] = 0;
	//GetClassName(hwnd, class_name, sizeof(class_name));
	GetWindowText(hwnd, title, sizeof(title));
	
	std::wstring titleAsWS(title);
	std::string titleAsStr(titleAsWS.begin(), titleAsWS.end());
	std::regex regexToMatch(title_regex);

	if (std::regex_match(titleAsStr, regexToMatch))
	{
		tagRECT rect;
		GetWindowRect(hwnd, &rect);
		SetWindowPos(hwnd, HWND_TOP, x, y, (width==-1 ? rect.right-rect.left : width), (height==-1 ? rect.bottom - rect.top : height), SWP_SHOWWINDOW);
	}
	return TRUE;
}