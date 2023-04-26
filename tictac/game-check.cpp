#include <iostream>
#include <string>
#include "Board.h"
#include "Errors.h"

int main()
{
  Board board;
  std::string input;

  try
  {
    while (std::getline(std::cin, input))
    {
      if (!board.isGameOver())
      {

        if (board.getCurrentPlayer() == 'O')
        {
          std::cout << "O's turn." << std::endl;
        }
        else if (board.getCurrentPlayer() == 'X')
        {
          std::cout << "X's turn." << std::endl;
        }

        if (board.isGameOver())
        {
          if (board.checkWin('X'))
          {
            std::cout << "Game over: X wins." << std::endl;
          }
          if (board.checkWin('O'))
          {
            std::cout << "Game over: O wins" << std::endl;
          }
        }
        if (board.isDraw())
        {
          std::cout << "Game over: Draw" << std::endl;
        }
      }
    }
    std::cout << "Game in progress: New game" << std::endl;
  }
  catch (const InvalidMove& e)
  {
    std::cout << "Invalid move." << std::endl;
    return 2;
  }
  catch (const ParseError& e)
  {
    std::cout << "Parse error." << std::endl;
    return 1;
  }

  return 0;
}


 