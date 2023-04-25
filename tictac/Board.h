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

  friend std::ostream& operator<<(std::ostream& os, const Board& board);

private:
  char cells_[3][3];

  bool isValidMove(const Move& move) const;

  bool checkRowWin(Player player) const;

  bool checkColWin(Player player) const;

  bool checkDiagonalWin(Player player) const;

  bool isBoardFull() const;
};

#endif
