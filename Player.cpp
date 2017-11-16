//
// Created by asaf on 11/15/17.
//

#include "Player.h"

Player::Player(std::string name, BoardPiece piece) : name(name), piece(piece) {}

std::string Player::getName() const {
    return std::string(name);
}


BoardPiece Player::getPiece() const {
    return piece;
}