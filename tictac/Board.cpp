#include "Errors.h"
#include "Board.h"

Board::Board() {
  // Initialize the game board
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      grid[i][j] = ' ';
    }
  }

  // Player X starts the game
  currentPlayer = 'X';
}

void Board::applyMove(const Move& move) {
  // Check if the move is valid
  if (move.row < 1 || move.row > 3 || move.column < 1 || move.column > 3 ||
      grid[move.row - 1][move.column - 1] != ' ') {
    throw InvalidMove("Invalid move");
  }

  // Apply the move
  grid[move.row - 1][move.column - 1] = move.player;

  // Switch to the next player
  currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

bool Board::isGameOver() {
  // Check if any player has won
  if (checkWin('X')) {
    return true;
  } else if (checkWin('O')) {
    return true;
  }

  // Check if the board is full
  return isBoardFull();
}

bool Board::checkWin(char player) {
  // Check rows
  for (int i = 0; i < 3; ++i) {
    if (grid[i][0] == player && grid[i][1] == player && grid[i][2] == player) {
      return true;
    }
  }

  // Check columns
  for (int i = 0; i < 3; ++i) {
    if (grid[0][i] == player && grid[1][i] == player && grid[2][i] == player) {
      return true;
    }
  }

  // Check diagonals
  if (grid[0][0] == player && grid[1][1] == player && grid[2][2] == player) {
    return true;
  }
  if (grid[0][2] == player && grid[1][1] == player && grid[2][0] == player) {
    return true;
  }

  return false;
}

bool Board::isBoardFull() {
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (grid[i][j] == ' ') {
        return false;
      }
    }
  }
  return true;
}

char Board::getCurrentPlayer() {
  return currentPlayer;
}

