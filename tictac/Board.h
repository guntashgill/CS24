#ifndef BOARD_H
#define BOARD_H

#include "Move.h"

class Board {
public:
  // Default constructor
  Board();

  // Apply a move to the board
  void applyMove(const Move& move);

  // Check if the game is over
  bool isGameOver();

  // Get the current player
  char getCurrentPlayer();

private:
  // Member Variables
  char grid[3][3]; // Represents the game board
  char currentPlayer; // Represents the current player ('X' or 'O')

  // Helper function to check if a player has won
  bool checkWin(char player);

  // Helper function to check if the board is full
  bool isBoardFull();
};

#endif


