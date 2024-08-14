#include "MainMenuScene.h"

void MainMenuScene::SelectMode()
{
    PrintMainMenu();
    int key;
    key = _getch();
    switch (key)
    {
    case 49:
        deckSelectScene.SelectDeck();
    case 50:
        return;
    }
}

void MainMenuScene::PrintMainMenu() const
{
    std::cout << "1. 시작\n2. 나가기" << std::endl;
}