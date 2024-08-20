#include "MainMenuScene.h"


int main()
{
    HWND consoleWindow = GetConsoleWindow();

    // �ʺ�, ����
    int desiredWidth = 1280;
    int desiredHeight = 720;

    // ����� �ػ󵵸� ������
    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);

    int screenWidth = desktop.right;
    int screenHeight = desktop.bottom;

    // �ܼ� â�� �߾ӿ� ��ġ�ϱ� ���� ��ǥ ���
    int x = (screenWidth / 2) - (desiredWidth / 2);
    int y = (screenHeight / 2) - (desiredHeight / 2);

    // �ܼ� â�� ��ġ�� ũ�� ����
    MoveWindow(consoleWindow, x, y, desiredWidth, desiredHeight, TRUE);

    // �ʷ� ȭ��
    //system("color 2F");

	MainMenuScene mainMenu;
	while (true)
	{
		mainMenu.SelectMode();
	}

	return 0;
}