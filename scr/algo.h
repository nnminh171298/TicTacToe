#ifndef ALGO_H
#define ALGO_H

#include "board.h"

class Algo
{
public:
    explicit Algo() = default;
    virtual ~Algo() = default;

    virtual Board::BoardStatus evaluateBoard(const Board &board);
    virtual int getNextMove(const Board &board) = 0;
};

#endif // ALGO_H
