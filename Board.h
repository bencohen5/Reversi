//
// Created by asaf on 11/15/17.
//

#ifndef REVERSI_BOARD_H
#define REVERSI_BOARD_H

#include <vector>
#include <cassert>

/**
 * represents a place on the board
 */
typedef struct {
    int row;
    int col;
} BoardPosition;
/**
 * represents one piece on the board
 */
enum BoardPiece {
    X = 'X',
    O = 'O',
    EMPTY = ' '
};

/**
 * this class is one array, will be only used for operator overloading in Board class.
 */
class Array {
private:
    unsigned int size;
    const BoardPiece *arr;
public:
    Array(const BoardPiece *arr, unsigned int size);


    BoardPiece operator[](unsigned int index);

    bool valid(unsigned int index);
};

/**
 * this is the Reversi Board class.
 */
class Board {
private:
    // the board
    BoardPiece **board;
    // number of pieces x, and o have
    int xPieces;
    int oPieces;
    // number of rows, cols
    unsigned int rows, cols;

    /**
     * there are 8 possible directions to turn opponent's pieces.
     * every direction can be represented by (rowDirection, colDirection) while colDirection and
     * rowDirection are in (0,-1,1). for example, (-1,1) means lower in rows (-1) and higher in cols(1), i.e. lower left.
     * (0,1) is just left. we have |(0,-1,1)| x |(0,-1,-1)| = 3*3 = 9 combinations, but (0,0) is not allowed -> 8 possible directions.
     * @param player X or O.
     * @param rowDirection can be either (0,-1,1)
     * @param colDirection can be either (0,-1,1)
     * @return true if it's putting player's piece in pos will turn anything in (rowDirection,colDirection)
     * direction or false, otherwise.
     */
    bool possibleMovesIn(BoardPiece player, int rowDirection, int colDirection, BoardPosition pos) const;

    /**
     * turns opponents pieces in (rowDirection, colDirection) direction, assuming player just played at pos.
     * @param player - the player
     * @param rowDirection - row direction
     * @param colDirection - col direction
     * @param pos - positon of piece player's just put
     * @return - true if a piece was flipped, or false otherwise.
     */
    bool flipInDirection(BoardPiece player, int rowDirection, int colDirection, BoardPosition pos);

public:
    /**
     * constructor.
     * @param r  - rows
     * @param c  - cols
     */
    Board(unsigned int r, unsigned int c);

    /**
     * copy constructor.
     * @param other  - board
     */
    Board(const Board &other);

    /**
     * operator overloading. now we can get a cell of the board with syntax board[i][j]
     * while board is an instance of Board class.
     * @param i  - the row
     * @return the i'th row Array, which will be overloaded with [] again
     */
    Array operator[](unsigned int i) const;

    /**
     * destructor.
     */
    ~Board();

    /**
     * getter.
     * @return number of cols
     */
    unsigned int numCols() const;

    /**
     * getter.
     * @return number of rows
     */
    unsigned int numRows() const;

    /**
     * returns a vector of possible moves
     * @param player the player
     * @return the moves
     */
    std::vector<BoardPosition> possibleMoves(BoardPiece player) const;

    /**
     * places a piece of who at where (if it's a legit move) and flips pieces corresponding to where it was put.
     * @param who  the player
     * @param where  - the position
     */
    void playTurn(BoardPiece who, BoardPosition where);

    /**
     *
     * @return true if the board is full, false otherwise
     */
    bool IsFull() const;

    /**
     * returns the winner.
     * @return X,O or Empty- in case of tie.
     */
    BoardPiece winner() const;

    /**
     * getter.
     * @return the x pieces
     */
    int getXPieces() const;

    /**
     * returns true if {row,col} is a place on the board.
     * @param row  - the row
     * @param col  - the col
     * @return bool
     */
    bool valid(int row, int col) const;

    /**
     * getter.
     * @return - the number of o pieces
     */
    int getOPieces() const;

    /**
     * returns the opponent of a player.
     * @param player - the player
     * @return the opponent
     */
    BoardPiece opponent(BoardPiece player) const;

    /**
     * flips a cell on the board (must not be empty).
     * @param pos - the position
     */
    void flip(BoardPosition pos);
};


#endif //REVERSI_BOARD_H
