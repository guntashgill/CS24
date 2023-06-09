#ifndef BOARD_H
#define BOARD_H

#include "Move.h"

class Board {
public:
  Board();
  void gameMove(const Move& move);
  bool isGameOver();
  void gameResult();
  bool hasPlayerWon(char player);
  char getPlayerTurn() const;

private:
  char boardCells[3][3];
  char playerTurn;
  int moveNumber;
};

#endif


