//
// Created by asaf on 11/15/17.
//

#ifndef REVERSI_CONSOLEDRAWER_H
#define REVERSI_CONSOLEDRAWER_H

#include "Board.h"
#include "Drawer.h"
#include <iostream>
#include <iomanip>


class ConsoleDrawer : public Drawer {
public:

    void requestMove(std::string format) const;

    void drawCurrentBoard(const Board &board) const;

    void drawNoMoveMessage() const;

    void drawInvalidInputMessage(const std::string &format) const;

    void drawPossibleMoves(std::vector<BoardPosition> moves) const;

    void drawMoveMessage(const std::string &name) const;

    void pressAnyKeyToContinue() const;

    void drawWinMessage(std::string winner, const Board& board) const;

    void clearScreen() const;


};


#endif //REVERSI_CONSOLEDRAWER_H
