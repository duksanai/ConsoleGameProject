#include "MainMenuScene.h"


int main()
{
    srand(time(NULL));
    HWND consoleWindow = GetConsoleWindow();

    // �ʺ�, ����
    int desiredWidth = 1600;
    int desiredHeight = 1000;

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

    CONSOLE_CURSOR_INFO c = { 0 };
    c.dwSize = 1; //�β� : 1
    c.bVisible = 0; //Ŀ�� �����
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &c);

	MainMenuScene mainMenu;
	while (true)
	{
		mainMenu.SelectMode();
	}

	return 0;
}