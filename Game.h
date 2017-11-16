//
// Created by asaf on 11/15/17.
//

#ifndef REVERSI_GAME_H
#define REVERSI_GAME_H

#include <iostream>
#include "Board.h"
#include "ConsolePlayer.h"
#include "Drawer.h"



class Game {
private:
    // the board, drawer, x and o player and pointer to currently playing player.
    Board board;
    Drawer *drawer;
    Player *playerX, *playerO;
    Player *currentTurn;
    bool done;
    bool passedOnce;
    std::string inputFormat;

    /**
     * passing the turn.
     * @param tells us if the player played this turn
     */
    void passTurn(bool played);

    /**
     * plays a single turn
     */
    void playTurn();

    /**
     * tells us if a move is valid
     * @param move the move
     * @param possibleMoves vector of valid moves
     * @return true if valid, false otherwise
     */
    bool valid(BoardPosition move, std::vector<BoardPosition> possibleMoves);

    /**
     * asks to press enter to continue.
     */
    void endTurn();

public:
    /**
     * constructor.
     * @param drawer
     * @param board
     * @param playerO
     * @param playerX
     */
    Game(Drawer *drawer, const Board &board, Player *playerO, Player *playerX);

    /**
     * plays.
     */
    void play();
};


#endif //REVERSI_GAME_H
