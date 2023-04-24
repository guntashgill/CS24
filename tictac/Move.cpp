#include <iostream>
#include <cctype>
#include <string>
#include "move.h"
#include "errors.h"

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
    cout << move.number << ' ' << toupper(move.player) << ' ' << static_cast<char>('A' + move.row) << move.column + '0';
    if (!move.comment.empty()) {
        cout << ' ' << move.comment;
    }
    cout << endl;
}

int main() {
    int moveNumber;
    char playerCode;
    char rowCode;
    char columnCode;
    string comment;

    cout << "Enter move number: ";
    cin >> moveNumber;

    // Validate move number
    if (moveNumber < 1 || moveNumber > 9) {
        throw InvalidMove("Invalid move number. Please enter a number between 1 and 9.");
    }

    cout << "Enter player code (X/O): ";
    cin >> playerCode;

    // Validate player code
    if (!isValidPlayerCode(playerCode)) {
        throw InvalidMove("Invalid player code. Please enter 'X' or 'O'.");
    }

    cout << "Enter row code (A/B/C/D): ";
    cin >> rowCode;

    // Validate row code
    if (!isValidSquareCode(rowCode)) {
        throw InvalidMove("Invalid row code. Please enter 'A', 'B', 'C', or 'D'.");
    }

    cout << "Enter column code (1/2/3): ";
    cin >> columnCode;

    // Validate column code
    if (columnCode < '1' || columnCode > '3') {
        throw InvalidMove("Invalid column code. Please enter a number between 1 and 3.");
    }

    cin.ignore(); // Ignore any remaining whitespace in the input buffer

    cout << "Enter optional comment (if any): ";
    getline(cin, comment);

    Move move(moveNumber, playerCode, rowCode, columnCode - '0', comment);

    printMove(move);

    return 0;
}
