#include "MainMenuScene.h"

void MainMenuScene::SelectMode()
{
    int key;
    while (true)
    {
        system("cls");
        PrintMainMenu();
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
}

void MainMenuScene::PrintMainMenu() const
{
    std::cout << "1. 시작\n2. 나가기" << std::endl;
}