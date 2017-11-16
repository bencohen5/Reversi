//
// Created by asaf on 11/15/17.
//

#include "Game.h"

Game::Game(Drawer *drawer, const Board &board, Player *playerO, Player *playerX) :
        board(board), playerO(playerO), playerX(playerX), drawer(drawer), currentTurn(playerX) {
    inputFormat = "row,col";
    done = false;
    passedOnce = false;
}


void Game::passTurn(bool played) {
    currentTurn->getPiece() == X ? currentTurn = playerO : currentTurn = playerX;
    if (!played) {
        if (passedOnce)
            done = true;
        passedOnce = true;
    } else
        passedOnce = false;
}

void Game::playTurn() {
    drawer->drawMoveMessage(currentTurn->getName());
    std::vector<BoardPosition> possibleMoves = board.possibleMoves(currentTurn->getPiece());
    if (possibleMoves.empty()) {
        drawer->drawNoMoveMessage();
        passTurn(false);
        return;
    }
    drawer->drawPossibleMoves(possibleMoves);
    BoardPosition move;
    bool firstTime = true; // haven't inserted invalid input yet
    do {
        if (!firstTime)
            drawer->drawInvalidInputMessage(inputFormat);
        drawer->requestMove(inputFormat);
        firstTime = false;
        move = currentTurn->getMove();
        move.row--;
        move.col--;
    } while (!valid(move, possibleMoves));
    board.playTurn(currentTurn->getPiece(), move);
    passTurn(true);
}

bool Game::valid(BoardPosition move, std::vector<BoardPosition> possibleMoves) {
    if (!board.valid(move.row, move.col)) {
        return false;
    }
    for (std::vector<BoardPosition>::const_iterator it = possibleMoves.begin(); it != possibleMoves.end(); ++it) {
        if (it->row == move.row && it->col == move.col) {
            return true;
        }
    }
    return false;
}


void Game::endTurn() {
    drawer->pressAnyKeyToContinue();
    currentTurn->pressAnyKeyToContinue();
    drawer->clearScreen();
}

void Game::play() {
    while (!done) {
        drawer->drawCurrentBoard(board);
        playTurn();
        endTurn();
        if (board.IsFull())
            done = true;
    }
    std::string name;// = board.winner() == X ? playerX.getName() : (board.winner() == O ? playerO.getName() : "TIE");
    if (board.getOPieces() > board.getXPieces())
        name = playerO->getName();
    else if (board.getXPieces() > board.getOPieces())
        name = playerX->getName();
    else
        name = "TIE";
    drawer->drawWinMessage(name, board);
}

