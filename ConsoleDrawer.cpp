//
// Created by asaf on 11/15/17.
//

#include "ConsoleDrawer.h"


using namespace std;



void drawBoard(const Board& board) {
    unsigned int cols = board.numCols(), rows = board.numRows();
    cout << " ";
    for (int j = 0; j < cols; j++)
        cout << " | " << j + 1;
    cout << " |" << endl;
    cout << string(2 + 4 * cols, '-') << endl;
    for (int i = 0; i < rows; i++) {
        cout << setw(2) << i + 1;
        bool skip_space = true;
        for (int j = 0; j < cols; j++) {
            if (skip_space) {
                skip_space = false;
            } else {
                cout << " ";
            }
            cout << "|";
            BoardPiece c = board[i][j];
            cout << " " << (char) c;
        }
        cout << " |" << endl;
        cout << string(2 + 4 * cols, '-') << endl;
    }
}

void ConsoleDrawer::drawCurrentBoard(const Board &board) const {
    cout << "Current Board:" << endl << endl;
    drawBoard(board);
}

void ConsoleDrawer::drawInvalidInputMessage(const string &format) const {
    cout << "invalid input, please enter move in format " << format << "." << endl;
}

void ConsoleDrawer::drawPossibleMoves(vector<BoardPosition> moves) const {
    cout << "Your possible moves: ";
    bool first = true;
    for (vector<BoardPosition>::const_iterator it = moves.begin(); it != moves.end(); ++it) {
        BoardPosition move = *it;
        int row = move.row, col = move.col;
        if (!first) {
            cout << ",";
        }
        first = false;
        cout << "(" << row + 1 << "," << col + 1 << ")";
    }
    cout << endl;
}


void ConsoleDrawer::drawNoMoveMessage() const {
    cout << "No possible Moves. Play passes back to the other player" << endl;
}

void ConsoleDrawer::drawMoveMessage(const string &name) const {
    cout << name << ": It's your move." << endl;
}


void ConsoleDrawer::requestMove(string format) const {
    cout << "Please enter your move " << format << ": ";
}

void ConsoleDrawer::pressAnyKeyToContinue() const {
    cout << "press any key followed by enter to continue." << endl;
}


void ConsoleDrawer::drawWinMessage(string winner, const Board &board) const {
    cout << "final board::" << endl << endl;
    drawBoard(board);
    cout << endl;
    if (winner == "TIE") {
        cout << "It's a tie." << endl;
        return;
    }
    cout << "The winner is: " << winner << endl;
}

void ConsoleDrawer::clearScreen() const {
    cout << string(100, '\n');
}