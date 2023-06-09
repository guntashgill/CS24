#include "Errors.h"
#include "Move.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

Move::Move() {
  number = 0;
  player = ' ';
  row = 0;
  column = 0;
}

Move::Move(const std::string& input) {
  std::istringstream iss(input);
  try {
    if (isdigit(input[0]) == 0) {
        throw ParseError("Invalid move number format");
    }

    std::string moveNumber;
    iss >> moveNumber;

    if (moveNumber.length() > 1) {
        throw ParseError("Invalid move number format");
    }

    number = std::stoi(moveNumber);

    if (number < 1 || number > 9) {
        throw ParseError("Invalid move number above 1 or 9");
    }
  } 
  catch (std::invalid_argument const&) {
    throw ParseError("Invalid move number");
  }

  std::string afterMoveNumber = "";
  iss >> afterMoveNumber;

  while (isspace(afterMoveNumber[0])) {
      afterMoveNumber = afterMoveNumber.substr(1);
  }

  if (afterMoveNumber[0] != 'X' && afterMoveNumber[0] != 'O' && afterMoveNumber[0] != 'x' && afterMoveNumber[0] != 'o') {
      throw ParseError("Invalid player");
  } else {
      player = toupper(afterMoveNumber[0]);
  }

  try {
      std::string afterPlayer = "";
      iss >> afterPlayer;

      if (afterPlayer.length() != 2) {
          throw ParseError("Invalid row or column");
      }

      row = int(toupper(afterPlayer[0])) - 64;
      column = int(toupper(afterPlayer[1])) - 48;

      if (row < 1 || row > 3 || column < 1 || column > 3) {
          throw ParseError("Invalid row or column");
      }
  } catch (std::invalid_argument const&) {
      throw ParseError("Invalid row or column");
  }

  std::string afterMove = "";
  iss >> afterMove;

  if (afterMove != "") {
      if (afterMove[0] != '#') {
          throw ParseError("Invalid move");
      }
  }
}

std::ostream& operator << (std::ostream& stream, const Move& move) {
  stream << move.number << ' ' << move.player << ' ' << static_cast<char>(move.row + 64) << move.column;
  return stream;
}


