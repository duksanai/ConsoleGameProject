#include "MainMenuScene.h"

void MainMenuScene::SelectMode()
{
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
