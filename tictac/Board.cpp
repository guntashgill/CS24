#include "Board.h"
#include "Errors.h"
#include <iostream>

Board::Board(){
  moveNumber = 0;
  playerTurn = 'E';
  for (size_t i = 0; i<3; ++i){
    for (size_t j = 0; j<3; ++i){
      boardCells[i][j] = ' ';
    }
  }
}
bool Board::isGameOver(){
  bool gameOver = false;
  if (hasPlayerWon('X')==true){
    gameOver = true;
  }
  if (hasPlayerWon('O')==true){
    gameOver = true;
  }
  bool fullBoard = true;
  for (size_t i = 0; i < 3; ++i){
    for (size_t j = 0; j < 3; ++i){
      if (boardCells[i][j]== ' '){
        fullBoard = false;
        break;
      }
    }
    if (fullBoard == false){
      break;
    }
  }
  if (fullBoard == true){
    gameOver = true;
  }
  return gameOver;
}
void Board::gameMove(const Move& move){
  if (move.player == playerTurn){
    throw InvalidMove("Wrong turn.");
  }
  moveNumber +=1;
  playerTurn = move.player;
  if (move.number != moveNumber){
    throw InvalidMove("Wrong move number.");
  }
  if (boardCells[move.row-1][move.column-1] != ' '){
    throw InvalidMove("Box is already taken");
  }
  if (isGameOver() == true){
    throw InvalidMove("Game is already over.");
  }
  boardCells[move.row-1][move.column-1] = move.player;
}
bool Board::hasPlayerWon(char player){
  bool winStatus = false;
  if ((boardCells[0][0] == player) && (boardCells[0][1] == player) && (boardCells[0][2] == player)){
    winStatus = true;
  }
  if ((boardCells[1][0] == player) && (boardCells[1][1] == player) && (boardCells[1][2] == player)){
    winStatus = true;
  }
  if ((boardCells[2][0] == player) && (boardCells[2][1] == player) && (boardCells[2][2] == player)){
    winStatus = true;
  }
  if ((boardCells[0][0] == player) && (boardCells[1][0] == player) && (boardCells[2][0] == player)){
    winStatus = true;
  }
  if ((boardCells[0][1] == player) && (boardCells[1][1] == player) && (boardCells[2][1] == player)){
    winStatus = true;
  }
  if ((boardCells[0][2] == player) && (boardCells[1][2] == player) && (boardCells[2][2] == player)){
    winStatus = true;
  }
  if ((boardCells[0][0] == player) && (boardCells[1][1] == player) && (boardCells[2][2] == player)){
    winStatus = true;
  }
  if ((boardCells[0][2] == player) && (boardCells[1][1] == player) && (boardCells[2][0] == player)){
    winStatus = true;
  }
  return winStatus;
}
void Board::gameResult() {
  if (playerTurn == 'E'){
    std::cout << "Game in progress: New game.\n";
  }
  else if ((isGameOver() == false) && (playerTurn == 'O')){
    std::cout << "Game in progress: X's turn.\n";
  }
  else if ((isGameOver() == false) && (playerTurn == 'X')){
    std::cout << "Game in progress: O's turn.\n";
  }
  else if (hasPlayerWon('X') == true){
    std::cout << "Game over: X wins.\n";
  }
  else if (hasPlayerWon('O') == true){
    std::cout << "Game over: O wins.\n";
  }
  else if (isGameOver() == true){
    std::cout << "Game over: Draw.\n";
  }
}
