#include "Board.h"
#include "Errors.h"
#include <iostream>

Board::Board()
{
    moveNumber=0;
    playerTurn='E';
    for(size_t i=0; i<3; ++i)
    {
        for(size_t j=0; j<3; ++j)
        {
            boardCells[i][j]=' ';
        }
    }
}

bool Board::isGameOver()
{
    bool gameOver=false;
    if(hasPlayerWon('X'))
    {
        gameOver=true;
    }
    if(hasPlayerWon('O'))
    {
        gameOver=true;
    }
    bool fullBoard=true;
    for(size_t i=0; i<3; ++i)
    {
        for(size_t j=0; j<3; ++j)
        {
            if(boardCells[i][j]==' ')
            {
                fullBoard=false;
                break;
            }
        }
        if(fullBoard==false)
        {
            break;
        }
    }
    if(fullBoard)
    {
        gameOver=true;
    }
    return gameOver;
}

void Board::gameMove(const Move& move)
{
    if(move.player==playerTurn)
    {
        throw InvalidMove("Wrong turn.");
    }
    moveNumber+=1;
    playerTurn=move.player;
    if(move.number!=moveNumber)
    {
        throw InvalidMove("Wrong move number.");
    }
    if(move.number>9)
    {
        throw InvalidMove("Move number exceeds 9.");
    }
    if(boardCells[move.row-1][move.column-1]!=' ')
    {
        throw InvalidMove("Box is already taken");
    }
    if(isGameOver())
    {
        throw InvalidMove("Game is already over.");
    }
    boardCells[move.row-1][move.column-1]=move.player;
}

bool Board::hasPlayerWon(char player)
{
    bool winStatus=false;
    if((boardCells[0][0]==player)&&(boardCells[0][1]==player)&&(boardCells[0][2]==player))
    {
        winStatus=true;
    }
    if((boardCells[1][0]==player)&&(boardCells[1][1]==player)&&(boardCells[1][2]==player))
    {
        winStatus=true;
    }
    if((boardCells[2][0]==player)&&(boardCells[2][1]==player)&&(boardCells[2][2]==player))
    {
        winStatus=true;
    }
    if((boardCells[0][0]==player)&&(boardCells[1][0]==player)&&(boardCells[2][0]==player))
    {
        winStatus=true;
    }
    if((boardCells[0][1]==player)&&(boardCells[1][1]==player)&&(boardCells[2][1]==player))
    {
        winStatus=true;
    }
    if((boardCells[0][2]==player)&&(boardCells[1][2]==player)&&(boardCells[2][2]==player))
    {
        winStatus=true;
    }
    if((boardCells[0][0]==player)&&(boardCells[1][1]==player)&&(boardCells[2][2]==player))
    {
        winStatus=true;
    }
    if((boardCells[0][2]==player)&&(boardCells[1][1]==player)&&(boardCells[2][0]==player))
    {
        winStatus=true;
    }
    return winStatus;
}

void Board::gameResult()
{
    if(playerTurn=='E')
    {
        std::cout<<"Game in progress: New game.\n";
    }
    else if(!isGameOver() && playerTurn=='O')
    {
        std::cout<<"Game in progress: X's turn.\n";
    }
    else if(!isGameOver() && playerTurn=='X')
    {
        std::cout<<"Game in progress: O's turn.\n";
    }
    else if(hasPlayerWon('X'))
    {
        std::cout<<"Game over: X wins.\n";
    }
    else if(hasPlayerWon('O'))
    {
        std::cout<<"Game over: O wins.\n";
    }
    else if(isGameOver())
    {
        std::cout<<"Game over: Draw.\n";
    }
}
char Board::getPlayerTurn() const {
  return playerTurn;
}