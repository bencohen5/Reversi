#include "Game.h"
#include "ConsoleDrawer.h"

int main() {
    Board b(8, 8);
    Player *playerO = new ConsolePlayer("O", O), *playerX = new ConsolePlayer("X", X);
    Drawer *drawer = new ConsoleDrawer();
    Game g(drawer, b, playerO, playerX);
    g.play();
    delete drawer;
    delete playerO;
    delete playerX;
    return 0;
}