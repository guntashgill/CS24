#include "Move.h"
#include "Errors.h"
#include <iostream>
#include <sstream>
#include <cctype>

using namespace std;

Move::Move(const std::string& input) {
  // Use a string stream to parse the input string
  std::stringstream ss(input);
  std::string temp;


  // Extract move number
  ss >> number;
  if (number == ' '){
    throw ParseError("number empty");
  }

  if (number > 9 || number < 1){
    throw ParseError("Number out of range");
  }


  // Extract player code
  ss >> player;

  if (!(player == 'X' || player == 'O' || player == 'x' || player == 'o')){
    throw ParseError("player out of range");
  }

  // Extract square code
  std::string squareCode;
  ss >> squareCode;
  if (squareCode.length() > 2){
    throw ParseError("Move out of range");
  }
  // Extract row and column from square code
  row = toupper(squareCode[0]) - 'A' + 1;
  column = squareCode[1] - '0';
  if (row < 1 || row > 3 || column < 1 || column > 3){
    throw ParseError("Row or column out of range"); 
  }

  // Ignore any remaining whitespace and comments
  string comment; 
  ss >> comment; 
  if (comment != "") {
    if (comment[0] != '#'){
      throw ParseError("Invalid Comment Start");
    }
  }

}

std::ostream& operator<<(std::ostream& stream, const Move& move) {
  // Print move in the expected format
  stream << move.number << " " << move.player << " "
         << static_cast<char>(move.row + 'A' - 1) << move.column;
  return stream;
}
