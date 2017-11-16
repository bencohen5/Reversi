//
// Created by asaf on 11/15/17.
//

#include "ConsolePlayer.h"
#include <iostream>
#include <limits>

using namespace std;

ConsolePlayer::ConsolePlayer(std::string name, BoardPiece piece) : Player(name, piece) {}


int toInt(string s) {
    int num = 0;
    for (int i = 0; i < s.size(); i++) {
        int temp = s[i] - '0';
        if (temp < 0 || temp > 9) {
            return -1;
        }
        num = num * 10 + temp;
    }
    return num;
}

BoardPosition ConsolePlayer::getMove() const {
    BoardPosition move = {-1, -1};
    string input;
    cin >> input;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (input.length() < 3 || input.find(',') == string::npos) {
        return move;
    }
    unsigned long index = input.find(',');
    move.row = toInt(input.substr(0, index));
    move.col = toInt(input.substr(index + 1, input.length() - index));
    return move;
}


void ConsolePlayer::pressAnyKeyToContinue() const {
    char c;
    cin.get(c);
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
