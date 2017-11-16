//
// Created by asaf on 11/15/17.
//

#ifndef REVERSI_CONSOLEPLAYER_H
#define REVERSI_CONSOLEPLAYER_H


#include "Player.h"
#include "Board.h"

class ConsolePlayer : public Player {
public:
    /**
     * constructor.
     * @param name the name
     * @param piece - his piece
     */
    ConsolePlayer(std::string name, BoardPiece piece);

    /**
     * gets the move from the player.
     * @return the move
     */
    BoardPosition getMove() const;

    /**
     * presses the key.
     */
    void pressAnyKeyToContinue() const;
};


#endif //REVERSI_CONSOLEPLAYER_H
