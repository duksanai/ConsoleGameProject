#include "MainMenuScene.h"


int main()
{
    HWND consoleWindow = GetConsoleWindow();

    // 너비, 높이
    int desiredWidth = 1280;
    int desiredHeight = 720;

    // 모니터 해상도를 가져옴
    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);

    int screenWidth = desktop.right;
    int screenHeight = desktop.bottom;

    // 콘솔 창을 중앙에 배치하기 위한 좌표 계산
    int x = (screenWidth / 2) - (desiredWidth / 2);
    int y = (screenHeight / 2) - (desiredHeight / 2);

    // 콘솔 창의 위치와 크기 설정
    MoveWindow(consoleWindow, x, y, desiredWidth, desiredHeight, TRUE);

    // 초록 화면
    //system("color 2F");

	MainMenuScene mainMenu;
	while (true)
	{
		mainMenu.SelectMode();
	}

	return 0;
}