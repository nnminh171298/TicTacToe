#ifndef ALGO_H
#define ALGO_H

#include "board.h"

class Algo
{
public:
    explicit Algo() = default;
    virtual ~Algo() = default;

    virtual Board::BoardStatus evaluateBoard(const Board &board, bool is_computer_turn);
    virtual QString getAlgoName() const = 0;
    virtual int getNextMove(const Board &board) = 0;
};

#endif // ALGO_H
