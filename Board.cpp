//
// Created by asaf on 11/15/17.
//

#include "Board.h"

using namespace std;


Array::Array(const BoardPiece *arr, unsigned int size) {
    this->size = size;
    this->arr = arr;
}

bool Array::valid(unsigned int index) {
    return index >= 0 && index < size;
}

BoardPiece Array::operator[](unsigned int index) {
    assert(this->valid(index));
    return arr[index];
}

Board::Board(unsigned int r = 8, unsigned int c = 8) : rows(r), cols(c) {
    board = new BoardPiece *[rows];
    for (int i = 0; i < rows; i++) {
        board[i] = new BoardPiece[cols];
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            board[i][j] = EMPTY;
        }
    }
    board[rows / 2 - 1][cols / 2 - 1] = O;
    board[rows / 2 - 1][cols / 2] = X;
    board[rows / 2][cols / 2 - 1] = X;
    board[rows / 2][cols / 2] = O;
    xPieces = 2;
    oPieces = 2;
}

Board::Board(const Board &other) {
    this->rows = other.rows;
    this->cols = other.cols;
    board = new BoardPiece *[rows];
    for (int i = 0; i < rows; i++) {
        board[i] = new BoardPiece[cols];
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            board[i][j] = (other.board)[i][j];
        }
    }
    this->xPieces = other.xPieces;
    this->oPieces = other.oPieces;
}


Array Board::operator[](unsigned int i) const {
    assert(i >= 0 && i < rows);
    return Array(board[i], cols);
}

Board::~Board() {
    for (int i = 0; i < rows; i++) {
        delete[] board[i];
    }
    delete[] board;
}


unsigned int Board::numCols() const {
    return cols;
}


unsigned int Board::numRows() const {
    return rows;
}

bool Board::possibleMovesIn(BoardPiece player, int rowDirection, int colDirection, BoardPosition pos) const {
    assert(player == X || player == O);
    assert(rowDirection == -1 || rowDirection == 0 || rowDirection == 1);
    assert(colDirection == -1 || colDirection == 0 || colDirection == 1);
    assert(colDirection != 0 || rowDirection != 0);
    if (!valid(pos.row + rowDirection, pos.col + colDirection))
        return false; // in case pos is the last in this direction
    if (board[pos.row + rowDirection][pos.col + colDirection] != opponent(player)) {
        return false; // in case next board piece isn't opponent's
    }
    int i, j;
    for (i = pos.row + rowDirection, j = pos.col + colDirection;
         valid(i, j); i += rowDirection, j += colDirection) {
        if (board[i][j] == EMPTY)
            return false;
        if (board[i][j] == player)
            break;
    }
    return valid(i, j); // if not valid we stopped because the board ended,
    // if it is valid we stopped because there were opponent's pieces and then player's piece
}


vector<BoardPosition> Board::possibleMoves(BoardPiece player) const {
    assert(player != EMPTY);
    vector<BoardPosition> moves;
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (board[row][col] == EMPTY) {
                BoardPosition bp = {row, col};
                if (possibleMovesIn(player, 0, 1, bp) || possibleMovesIn(player, 0, -1, bp)
                    || possibleMovesIn(player, 1, 0, bp) || possibleMovesIn(player, 1, -1, bp)
                    || possibleMovesIn(player, 1, 1, bp) || possibleMovesIn(player, -1, 0, bp)
                    || possibleMovesIn(player, -1, -1, bp) || possibleMovesIn(player, -1, 1, bp)) {
                    moves.push_back(bp);
                }
            }
        }
    }
    return moves;
}

BoardPiece Board::opponent(BoardPiece player) const {
    assert(player == X || player == O);
    return player == X ? O : X;
}

bool Board::flipInDirection(BoardPiece player, int rowDirection, int colDirection, BoardPosition pos) {
    assert(player == X || player == O);
    assert(rowDirection == -1 || rowDirection == 0 || rowDirection == 1);
    assert(colDirection == -1 || colDirection == 0 || colDirection == 1);
    assert(colDirection != 0 || rowDirection != 0);
    if (!valid(pos.row + rowDirection, pos.col + colDirection))
        return false; // in case pos is the last in this direction
    if (board[pos.row + rowDirection][pos.col + colDirection] != opponent(player)) {
        return false; // in case next board piece isn't opponent's
    }
    int i, j;
    for (i = pos.row + rowDirection, j = pos.col + colDirection;
         valid(i, j); i += rowDirection, j += colDirection) {
        if (board[i][j] == EMPTY)
            return false;
        if (board[i][j] == player)
            break;
    }
    if (!valid(i, j)) {
        // means we got to the end of board, without getting to player's piece. hence, can't flip
        return false;
    }
    // in case we should flip all the pieces we just passed
    for (i = i - rowDirection, j = j - colDirection;
         board[i][j] == opponent(player); i -= rowDirection, j -= colDirection) {
        BoardPosition place = {i, j};
        flip(place);
        /*
         * uncomment if this stupid rules turns out to be true
         */
    }
    return true;
}

void Board::playTurn(BoardPiece who, BoardPosition where) {
    int row = where.row;
    int col = where.col;
    assert(col >= 0 && col < cols);
    assert(who != EMPTY && row >= 0 && row < rows);
    assert(board[row][col] == EMPTY);

    // now turn pieces...
    BoardPiece player = who;
    if (flipInDirection(player, 0, 1, where) || flipInDirection(player, 0, -1, where)
        || flipInDirection(player, -1, 0, where) || flipInDirection(player, -1, 1, where)
        || flipInDirection(player, -1, -1, where) || flipInDirection(player, 1, 1, where)
        || flipInDirection(player, 1, -1, where) || flipInDirection(player, 1, 0, where)) {
        board[where.row][where.col] = who;
        who == X ? xPieces++ : oPieces++;
    }
}

bool Board::IsFull() const {
    return (xPieces + oPieces) == rows * cols;
}

BoardPiece Board::winner() const {
    oPieces > xPieces ? O : (xPieces > oPieces ? X : EMPTY);
}

int Board::getOPieces() const {
    return oPieces;
}

int Board::getXPieces() const {
    return xPieces;
}

bool Board::valid(int row, int col) const {
    return row >= 0 && row < rows && col >= 0 && col < cols;
}

void Board::flip(BoardPosition pos) {
    int row = pos.row, col = pos.col;
    assert(row >= 0 && col >= 0 && row < rows && col < cols);
    assert(board[row][col] != EMPTY);
    if (board[row][col] == X) {
        board[row][col] = O;
        oPieces++;
        xPieces--;
    } else {
        board[row][col] = X;
        xPieces++;
        oPieces--;
    }
}
