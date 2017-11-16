//
// Created by asaf on 11/15/17.
//

#ifndef REVERSI_DRAWER_H
#define REVERSI_DRAWER_H

#include <string>
#include "Board.h"

class Drawer {
public:
    /**
     * requests move.
     * @param format - move format
     */
    virtual void requestMove(std::string format) const = 0;

    /**
     * draws the board.
     * @param board - the board
     */
    virtual void drawCurrentBoard(const Board &board) const = 0;

    /**
     * tells the player that there is no move possible for him.
     */
    virtual void drawNoMoveMessage() const = 0;

    /**
     * tells the player that his move's format is invalid.
     * @param format - the format he needs to enter
     */
    virtual void drawInvalidInputMessage(const std::string &format) const = 0;

    /**
     * tell the player what moves can he play.
     * @param moves - the moves
     */
    virtual void drawPossibleMoves(std::vector<BoardPosition> moves) const = 0;

    /**
     * tells the player to play.
     * @param name - player's name
     */
    virtual void drawMoveMessage(const std::string &name) const = 0;

    /**
     *press any key to contine;
     */
    virtual void pressAnyKeyToContinue() const = 0;

    /**
     * tells us who won.
     * @param winner - the winner's name
     */
    virtual void drawWinMessage(std::string winner, const Board& board) const = 0;

    /**
     * clears the screen.
     */
    virtual void clearScreen() const = 0;


};



#endif //REVERSI_DRAWER_H
