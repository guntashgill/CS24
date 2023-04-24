#include <iostream>
#include <cctype>
#include <string>
#include "Move.h"
#include "Errors.h"

using namespace std;

// Function to check if a character is a valid player code (X or O)
bool isValidPlayerCode(char c) {
    return c == 'X' || c == 'O' || c == 'x' || c == 'o';
}

// Function to check if a character is a valid square code (A, B, C, D) as row and (1, 2, 3) as column
bool isValidSquareCode(char c) {
    return c == 'A' || c == 'B' || c == 'C' || c == 'D' ||
           c == 'a' || c == 'b' || c == 'c' || c == 'd';
}

// Function to print a move in the required format
void printMove(const Move& move) {
    cout << move.number << ' ' << toupper(move.player) << ' ' << static_cast<char>('A' + move.row) << move.col + 1;
    if (!move.comment.empty()) {
        cout << ' ' << move.comment;
    }
    cout << endl;
}

