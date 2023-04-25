
#ifndef BOARD_H
#define BOARD_H

#include "Move.h"
#include "Errors.h"

enum Player {
  None, // Add None member
  X,
  O
};

class Board {
public:
  Board();

  static const int BOARD_SIZE = 3; 
  char board_[BOARD_SIZE][BOARD_SIZE];

  void applyMove(const Move& move);

  bool checkWin(Player player) const;

  bool isDraw() const;

  bool isGameOver() const;

  Player getCurrentPlayer() const;

  friend std::ostream& operator<<(std::ostream& os, const Board& board);

private:
  char cells_[3][3];

  Player currentPlayer_;

  bool isValidMove(const Move& move) const;

  bool checkRowWin(Player player) const;

  bool checkColWin(Player player) const;

  bool checkDiagonalWin(Player player) const;

  bool isBoardFull() const;
};


// I recommended writing a Board class to manage your game state.
// Here's some space for the class definition; member functions go in Board.cpp.

#endif
