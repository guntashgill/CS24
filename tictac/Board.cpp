#include "Board.h"

Board::Board() {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      grid[i][j] = ' ';
    }
  }
}

void Board::applyMove(const Move& move) {
  grid[move.row][move.column] = move.player;
}

bool Board::isGameOver() {
  // Check rows
  for (int i = 0; i < 3; i++) {
    if (grid[i][0] != ' ' && grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2]) {
      return true;
    }
  }

  // Check columns
  for (int j = 0; j < 3; j++) {
    if (grid[0][j] != ' ' && grid[0][j] == grid[1][j] && grid[1][j] == grid[2][j]) {
      return true;
    }
  }

  // Check diagonals
  if (grid[0][0] != ' ' && grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2]) {
    return true;
  }
  if (grid[0][2] != ' ' && grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0]) {
    return true;
  }

  return false;
}

bool Board::isDraw() {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (grid[i][j] == ' ') {
        return false;
      }
    }
  }
  return true;
}

bool Board::hasPlayerWon(char player) {
  // Check rows
  for (int i = 0; i < 3; i++) {
    if (grid[i][0] == player && grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2]) {
      return true;
    }
  }

  // Check columns
  for (int j = 0; j < 3; j++) {
    if (grid[0][j] == player && grid[0][j] == grid[1][j] && grid[1][j] == grid[2][j]) {
      return true;
    }
  }

  // Check diagonals
  if (grid[0][0] == player && grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2]) {
    return true;
  }
  if (grid[0][2] == player && grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0]) {
    return true;
  }

  return false;
}
