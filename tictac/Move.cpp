#include "Errors.h"
#include "Move.h"
#include <cctype>
Move::Move(const std::string& input){
  size_t indArr[4];
  size_t ind = 0;
  size_t commInd = 0;
  for (size_t i = 0; i < input.size(); ++i){
    if (ind < 4){
      if (!isspace(input[i])){
        indArr[ind] = i;
      }
    }
    else{
      if (!isspace(input[i])){
        if (input[i] == '#'){
          commInd = i;
          break;
        }
        else {
          throw ParseError("There is a character after column that isn't a whitespace.");
        }
      }
    }
  }
  if (ind != 4) {
    throw ParseError("Index array doesn't have 4 values.");
  }
  size_t numInd = indArr[0];
  size_t playerInd= indArr[1];
  size_t rowInd = indArr[2];
  size_t colInd = indArr[3];
  if ((input[numInd] < '1') || (input[numInd] > '9')){
    throw ParseError("Move number is not a digit between 1 and 9.");
  }
  if ((toupper(input[playerInd]) != 'X') && (toupper(input[playerInd]) != 'O')){
    throw ParseError("Player is not either 'X' or 'O'.");
  }
  if ((toupper(input[rowInd]) != 'A') && (toupper(input[rowInd]) != 'B') && (toupper(input[rowInd]) != 'C')){
    throw ParseError("Row is not either 'A', 'B', or 'C'.");
  }
  if ((!isdigit(input[colInd])) || (input[colInd] < '1') || (input[colInd] > '3')){
    throw ParseError("Column is not a digit between 1 and 3.");
  }
  if(numInd != 0){
    throw ParseError("First value cannot be a whitespace.");
  }
  if(((int)indArr[1] - (int)indArr[0]) < 2){
    throw ParseError("There is no whitespace between move number ad player.");
  }
  if(((int)indArr[2] - (int)indArr[1]) < 2){
    throw ParseError("There is no whitespace between player and row.");
  }
  if(((int)indArr[3] - (int)indArr[2]) < 1){
    throw ParseError("There is no whitespace between row and column.");
  }
  if (commInd != 0){
    if (((int)commInd - (int)indArr[3]) <2){
      throw ParseError("There is no whitespace before comment.");
    }
  }
  number = input[numInd] - '0';
  player = toupper(input[playerInd]);
  row = toupper(input[rowInd]) -'@';
  column = input[colInd] - '0';
}
std::ostream& operator <<(std::ostream& stream, const Move& move){
  stream << move.number << " ";
  stream << move.player << " ";
  stream << (char)(move.row + 64);
  stream << move.column;
  return stream;

}

