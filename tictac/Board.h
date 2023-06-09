#ifndef BOARD_H
#define BOARD_H

#include "Move.h"

class Board {
public:
  Board();
  void applyMove(const Move& move);
  bool isGameOver();
  bool isDraw();
  bool hasPlayerWon(char player);

private:
  char grid[3][3];
};

#endif

