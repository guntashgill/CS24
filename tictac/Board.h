#ifndef BOARD_H
#define BOARD_H

#include "Move.h"
#include "Errors.h"

enum class Player { X, O };

class Board {
public:
  Board();

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
