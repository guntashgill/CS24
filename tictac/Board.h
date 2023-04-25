#ifndef BOARD_H
#define BOARD_H

#include "Move.h"
#include "Errors.h"

enum Player {
  None,
  X,
  O
};

class Board {
public:
  Board();
  ~Board();

  static const int BOARD_SIZE = 3; 
  char board_[BOARD_SIZE][BOARD_SIZE];

  void applyMove(const Move& move);

  bool checkWin(Player player) const;

  bool isDraw() const;

  bool isGameOver() const;

  Player getCurrentPlayer() const;

  friend std::ostream& operator<<(std::ostream& os, const Board& board);

private:
  char** cells_;

  Player currentPlayer_;

  bool isValidMove(const Move& move) const;

  bool checkRowWin(Player player) const;

  bool checkColWin(Player player) const;

  bool checkDiagonalWin(Player player) const;

  bool isBoardFull() const;
  Board::Board() {
  // Allocate memory for the 2D array
  cells_ = new char*[BOARD_SIZE];
  for (int i = 0; i < BOARD_SIZE; i++) {
    cells_[i] = new char[BOARD_SIZE];
  }

  // Initialize the cells with default values
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      cells_[i][j] = ' ';
    }
  }
}

Board::~Board() {
  // Deallocate the dynamic memory for the 2D array
  for (int i = 0; i < BOARD_SIZE; i++) {
    delete[] cells_[i];
  }
  delete[] cells_;
}

};


// I recommended writing a Board class to manage your game state.
// Here's some space for the class definition; member functions go in Board.cpp.

#endif
