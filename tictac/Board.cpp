#include "Board.h"
#include "Errors.h"
#include <iostream>
Board::Board() {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      board_[i][j] = ' ';
    }
  }
}

void Board::applyMove(const Move& move) {
  if (!isValidMove(move)) {
    throw InvalidMove("Invalid move.");
  }
  cells_[move.row][move.column] = static_cast<char>(move.player);
  // Update currentPlayer_ based on the current player's move
  if (currentPlayer_ == 'O') {
    currentPlayer_ = 'X';
  } 
  else {
    currentPlayer_ = 'O';
  }
}

bool Board::checkWin(char player) const {
  char p = static_cast<char>(player);
  // Check for row win
  for (int i = 0; i < 3; i++) {
    if (board_[i][0] == p && board_[i][1] == p && board_[i][2] == p) {
      return true;
    }
  }
  // Check for column win
  for (int i = 0; i < 3; i++) {
    if (board_[0][i] == p && board_[1][i] == p && board_[2][i] == p) {
      return true;
    }
  }
  // Check for diagonal win
  if (board_[0][0] == p && board_[1][1] == p && board_[2][2] == p) {
    return true;
  }
  if (board_[0][2] == p && board_[1][1] == p && board_[2][0] == p) {
    return true;
  }
  return false;
}
char Board::getCurrentPlayer() const {
  return currentPlayer_;
}
bool Board::isBoardFull() const {
  for (int row = 0; row < BOARD_SIZE; ++row) {
    for (int col = 0; col < BOARD_SIZE; ++col) {
      if (cells_[row][col] == ' ') {
        return false;
      }
    }
  }
  return true;
}

bool Board::isDraw() const {
  return isBoardFull() && !checkWin('X') && !checkWin('O');
}
bool Board::isGameOver() const {
  return isBoardFull() || checkWin('X') || checkWin('O') || isDraw();
}

std::ostream& operator<<(std::ostream& os, const Board& board) {
  for (int i = 0; i < 3; i++) {
    os << board.cells_[i][0] << " | " << board.cells_[i][1] << " | " << board.cells_[i][2] << std::endl;
    if (i < 2) {
      os << "---------" << std::endl;
    }
  }
  return os;
}

bool Board::isValidMove(const Move& move) const {
  if (move.row < 0 || move.row >= BOARD_SIZE || move.column < 0 || move.column >= BOARD_SIZE) {
    return false;
  }
  if (board_[move.row][move.column] != ' ') {
    return false;
  }
  return true;
}
bool Board::checkRowWin(char player) const {
  char p = static_cast<char>(player);
  for (int i = 0; i < 3; i++) {
    if (cells_[i][0] == p && cells_[i][1] == p && cells_[i][2] == p) {
      return true;
    }
  }
  return false;
}

bool Board::checkColWin(char player) const {
  char p = static_cast<char>(player);
  for (int i = 0; i < 3; i++) {
    if (cells_[0][i] == p && cells_[1][i] == p && cells_[2][i] == p) {
      return true;
    }
  }
  return false;
}



// Space for implementing Board functions.