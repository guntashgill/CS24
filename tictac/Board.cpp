#include "Board.h"
#include "Errors.h"
#include "Move.h"

Board::Board() {
  // Initialize the board cells
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      cells_[i][j] = ' ';
    }
  }
}

void Board::applyMove(const Move& move) {
  // Check if move is valid
  if (!isValidMove(move)) {
    throw InvalidMove("Invalid move");
  }

  // Apply the move
  cells_[move.row][move.col] = static_cast<char>(move.player);
}

bool Board::checkWin(Player player) const {
  return checkRowWin(player) || checkColWin(player) || checkDiagonalWin(player);
}

bool Board::isDraw() const {
  return isBoardFull() && !checkWin(Player::X) && !checkWin(Player::O);
}

bool Board::isGameOver() const {
  return isDraw() || checkWin(Player::X) || checkWin(Player::O);
}

bool Board::isValidMove(const Move& move) const {
  return move.row >= 0 && move.row < 3 && move.col >= 0 && move.col < 3 && cells_[move.row][move.col] == ' ';
}

bool Board::checkRowWin(Player player) const {
  for (int i = 0; i < 3; ++i) {
    if (cells_[i][0] == static_cast<char>(player) && cells_[i][1] == static_cast<char>(player) &&
        cells_[i][2] == static_cast<char>(player)) {
      return true;
    }
  }
  return false;
}

bool Board::checkColWin(Player player) const {
  for (int i = 0; i < 3; ++i) {
    if (cells_[0][i] == static_cast<char>(player) && cells_[1][i] == static_cast<char>(player) &&
        cells_[2][i] == static_cast<char>(player)) {
      return true;
    }
  }
  return false;
}

bool Board::checkDiagonalWin(Player player) const {
  if (cells_[0][0] == static_cast<char>(player) && cells_[1][1] == static_cast<char>(player) &&
      cells_[2][2] == static_cast<char>(player)) {
    return true;
  }

  if (cells_[0][2] == static_cast<char>(player) && cells_[1][1] == static_cast<char>(player) &&
      cells_[2][0] == static_cast<char>(player)) {
    return true;
  }

  return false;
}

bool Board::isBoardFull() const {
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (cells_[i][j] == ' ') {
        return false;
      }
    }
  }
  return true;
}

std::ostream& operator<<(std::ostream& os, const Board& board) {
  os << "   0   1   2" << std::endl;
  for (int i = 0; i < 3; ++i) {
    os << i << " ";
    for (int j = 0; j < 3; ++j) {
      os << " " << board.cells_[i][j] << " ";
      if (j < 2) {
        os << "|";
      }
    }
    os << std::endl;
    if (i < 2) {
      os << "  ---|---|---" << std::endl;
    }
  }
  return os;
}  

// Space for implementing Board functions.