#include "MainMenuScene.h"

void MainMenuScene::SelectMode()
{
    system("cls");
    PrintMainMenu();
    int key;
    key = _getch();
    switch (key)
    {
    case 49:
        system("cls");
        deckSelectScene.SelectDeck();
    case 50:
        exit(0);
    }
}

void MainMenuScene::PrintMainMenu() const
{
    std::cout << "1. 시작\n2. 나가기" << std::endl;
}