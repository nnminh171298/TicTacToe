#ifndef ALGO_RANDOM_H
#define ALGO_RANDOM_H

#include "algo.h"

class Algo_random : public Algo
{
public:
    explicit Algo_random() = default;

    int getNextMove(const Board &board) override;
};

#endif // ALGO_RANDOM_H
