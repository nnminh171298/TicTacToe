#include "algo_fillblank.h"

int Algo_fillBlank::getNextMove(const Board &board)
{
    for(int i=0; i<Board::CELL_COUNT; i++)
        if(board.at(i) == Board::CellStatus::None)
            return i;
    return -1;
}
