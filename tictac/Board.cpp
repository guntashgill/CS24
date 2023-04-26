#include "Board.h"
#include "Errors.h"
#include <iostream>

Board::Board() {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      cells_[i][j] = ' ';
    }
  }
}

void Board::applyMove(const Move& move) {
  if (!isValidMove(move)) {
    throw InvalidMove("Invalid move.");
  }
  cells_[move.row][move.column] = static_cast<char>(move.player);
  if (currentPlayer_ == Player::X) {
    currentPlayer_ = Player::O;
  } 
  else {
    currentPlayer_ = Player::X;
  }
}

bool Board::checkWin(Player player) const {
  char p = static_cast<char>(player);
  // Check for row win
  for (int i = 0; i < 3; i++) {
    if (cells_[i][0] == p && cells_[i][1] == p && cells_[i][2] == p) {
      return true;
    }
  }
  // Check for column win
  for (int i = 0; i < 3; i++) {
    if (cells_[0][i] == p && cells_[1][i] == p && cells_[2][i] == p) {
      return true;
    }
  }
  // Check for diagonal win
  if (cells_[0][0] == p && cells_[1][1] == p && cells_[2][2] == p) {
    return true;
  }
  if (cells_[0][2] == p && cells_[1][1] == p && cells_[2][0] == p) {
    return true;
  }
  return false;
}
Player Board::getCurrentPlayer() const {
  // Getter function for current player
  return currentPlayer_;
}
bool Board::isBoardFull() const {
  for (int row = 0; row < BOARD_SIZE; ++row) {
    for (int col = 0; col < BOARD_SIZE; ++col) {
      if (board_[row][col] == Player::None) {
        return false;
      }
    }
  }
  // If all squares are claimed but no player has formed a line, return true
  return true;
}

bool Board::isDraw() const {
  return isBoardFull() && !checkWin(Player::X) && !checkWin(Player::O);
}

bool Board::isGameOver() const {
  return isBoardFull() || checkWin(Player::X) || checkWin(Player::O);
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
  return move.row >= 0 && move.row < 3 && move.column >= 0 && move.column < 3 &&
         cells_[move.row][move.column] == ' ';
}

bool Board::checkRowWin(Player player) const {
  char p = static_cast<char>(player);
  for (int i = 0; i < 3; i++) {
    if (cells_[i][0] == p && cells_[i][1] == p && cells_[i][2] == p) {
      return true;
    }
  }
  return false;
}

bool Board::checkColWin(Player player) const {
  char p = static_cast<char>(player);
  for (int i = 0; i < 3; i++) {
    if (cells_[0][i] == p && cells_[1][i] == p && cells_[2][i] == p) {
      return true;
    }
  }
  return false;
}


// Space for implementing Board functions.