
#ifndef BOARD_H
#define BOARD_H

#include "Move.h"
#include "Errors.h"


class Board {
public:
  Board();

  static const int BOARD_SIZE = 3; 
  char board_[BOARD_SIZE][BOARD_SIZE];

  void applyMove(const Move& move);

  bool checkWin(char player) const;

  bool isDraw() const;

  bool isGameOver() const;

  char getCurrentPlayer() const;

  friend std::ostream& operator<<(std::ostream& os, const Board& board);

private:
  char cells_[3][3];

  char currentPlayer_;

  bool isValidMove(const Move& move) const;

  bool checkRowWin(char player) const;

  bool checkColWin(char player) const;

  bool checkDiagonalWin(char player) const;

  bool isBoardFull() const;
};


// I recommended writing a Board class to manage your game state.
// Here's some space for the class definition; member functions go in Board.cpp.

#endif
