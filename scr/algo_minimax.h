#ifndef ALGO_MINIMAX_H
#define ALGO_MINIMAX_H

#include "algo.h"

class GameNode;
class GameTreeGenerator;

class Algo_minimax : public Algo
{
public:
    explicit Algo_minimax(std::shared_ptr<GameTreeGenerator> generator);
    void setMaxDepth(quint8 max_depth = std::numeric_limits<quint8>::max());

    Board::BoardStatus evaluateBoard(const Board &board) override;
    int getNextMove(Board board) override;

private:
    Board::BoardStatus evaluateBoardWithDepth(const Board &board, quint8 depth);
    Board::BoardStatus alphaBeta(GameNode *node, quint8 depth, bool maximizing_player = true, Board::BoardStatus alpha = Board::Lose, Board::BoardStatus beta = Board::Win);
    Board flipBoard(const Board &board);
    Board::BoardStatus childStatusToParentStatus(Board::BoardStatus child_status);

    std::shared_ptr<GameTreeGenerator> _generator;
    quint8 _depth;
};

#endif // ALGO_MINIMAX_H
