#include "algo.h"

Board::BoardStatus Algo::evaluateBoard(const Board &board, bool)
{
    return board.status();
}
