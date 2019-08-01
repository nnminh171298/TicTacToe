#ifndef ALGO_MINIMAX_H
#define ALGO_MINIMAX_H

#include "algo.h"

class GameNode;
class GameTreeGenerator;

class Algo_minimax : public Algo
{
public:
    explicit Algo_minimax(std::shared_ptr<GameTreeGenerator> generator);
    void setDepth(quint8 depth);

    Board::BoardStatus evaluateBoard(const Board &board) override;
    int getNextMove(const Board &board) override;

private:
    Board::BoardStatus alphaBeta(GameNode *node, quint8 depth, bool maximizing_player = true, Board::BoardStatus alpha = Board::Lose, Board::BoardStatus beta = Board::Win);
    Board flipBoard(const Board &board);
    Board::BoardStatus childStatusToParentStatus(Board::BoardStatus child_status);

    std::shared_ptr<GameTreeGenerator> _generator;
    quint8 _depth;
    GameNode *_current_node;
};

#endif // ALGO_MINIMAX_H
