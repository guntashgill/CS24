#include "Board.h"
#include "Errors.h"
#include "Move.h"
#include <iostream>


int main(int argc, char** argv){
  bool verbose = false;
  if (argc ==2 && std::string(argv[1]) == "-v"){
    verbose = true;
  }
  if (verbose){
    std::cout << "> ";
  }
  std::string line;
  Board gameBoard;
  while(std::getline(std::cin, line)){
    try{
      Move move(line);
      gameBoard.gameMove(move);
    }
    catch(const ParseError& e){
      if (verbose){
        std::cout << "Parse error: " << e.what() << "\n";
      }
      else{
        std::cout << "Parse error.\n";
      }
      return 1;
    }
    catch(const InvalidMove& e){
      if(verbose) {
        std::cout << "Invalid move: " << e.what() << "\n";
      }
      else{
        std::cout << "Invalid move.\n";
      }
      return 2;
    }
  }
  gameBoard.gameResult();
  return 0;
}