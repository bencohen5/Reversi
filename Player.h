//
// Created by asaf on 11/15/17.
//

#ifndef REVERSI_PLAYER_H
#define REVERSI_PLAYER_H


#include <string>
#include "Board.h"

class Player {
private:
    // name and piece
    std::string name;
    BoardPiece piece;
public:
    /**
     * constructor.
     * @param name name
     * @param piece piece
     */
    Player(std::string name, BoardPiece piece);

    /**
     * getter.
     * @return  piece
     */
    BoardPiece getPiece() const;

    /**
     * gets a move from the player.
     * @return  - the move
     */
    virtual BoardPosition getMove() const = 0;

    /**
     * getter.
     * @return  name
     */
    std::string getName() const;
    /**
     * press any key to continue.
     */
    virtual void pressAnyKeyToContinue() const = 0;
};


#endif //REVERSI_PLAYER_H
