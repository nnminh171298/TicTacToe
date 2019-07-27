#ifndef ALGO_MINIMAX_H
#define ALGO_MINIMAX_H

#include "algo.h"

class GameNode;
class GameTreeGenerator;

class Algo_minimax : public Algo
{
public:
    explicit Algo_minimax(std::shared_ptr<GameTreeGenerator> generator);

    Board::BoardStatus evaluateBoard(const Board &board, bool is_computer_turn) override;
    int getNextMove(const Board &board) override;
    QString getAlgoName() const override;

private:
    Board::BoardStatus alphaBeta(GameNode *node, bool maximizing_player = true, Board::BoardStatus alpha = Board::Lose, Board::BoardStatus beta = Board::Win);
    Board flipBoard(const Board &board);
    std::shared_ptr<GameTreeGenerator> _generator;
    GameNode *_current_node;

};

#endif // ALGO_MINIMAX_H
