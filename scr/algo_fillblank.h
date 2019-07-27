#ifndef ALGO_FILLBLANK_H
#define ALGO_FILLBLANK_H

#include "algo.h"

class Algo_fillBlank : public Algo
{
public:
    explicit Algo_fillBlank() = default;

    int getNextMove(const Board &board) override;
    QString getAlgoName() const override;
};

#endif // ALGO_FILLBLANK_H
