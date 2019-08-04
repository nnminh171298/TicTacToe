#include "algo_minimax.h"
#include "algo_random.h"
#include "gamenode.h"
#include "gametreegenerator.h"

#include <random>
#include <QDebug>
using namespace std;

Algo_minimax::Algo_minimax(std::shared_ptr<GameTreeGenerator> generator)
    : _generator{generator}
{
    setMaxDepth();
}

void Algo_minimax::setMaxDepth(quint8 max_depth)
{
    _depth = max_depth;
}

Board::BoardStatus Algo_minimax::evaluateBoard(const Board &board)
{
    // interface for game engine to call, always call for sub boards
    return evaluateBoardWithDepth(board, _depth - 1);
}

int Algo_minimax::getNextMove(Board board)
{
    Board::BoardStatus max_status = Board::Lose;
    QList<int> chosen_list;
    Board::CellStatus current_player = board.isComputerTurn() ? Board::CellStatus::Computer : Board::CellStatus::Player;

    for(int i=0; i<Board::CELL_COUNT; i++)
    {
        if(board.at(i) != Board::CellStatus::None)
            continue;

        board.setCell(i, current_player);
        auto sub_board_status = evaluateBoardWithDepth(board, _depth-1);
        if(sub_board_status == max_status)
            goto TO_BE_CONSIDERED;
        if(sub_board_status < max_status)
            goto RESET_BOARD;

        chosen_list.clear();
        max_status = sub_board_status;

    TO_BE_CONSIDERED:
        chosen_list.append(i);
    RESET_BOARD:
        board.setCell(i, Board::CellStatus::None);
    }
    if(chosen_list.length() == 0)
        return Algo_random().getNextMove(board);
    qDebug() << chosen_list;

    random_device random_device;
    mt19937 generator(random_device());
    shuffle(begin(chosen_list), end(chosen_list), generator);
    return chosen_list.first();
}

Board::BoardStatus Algo_minimax::evaluateBoardWithDepth(const Board &board, quint8 depth)
{
    if(board.isComputerFirst())
    {
        auto node = _generator->getNode(board);
        if(node == nullptr)
            return Board::Unknown;
        return alphaBeta(node, depth, board.isComputerTurn());
    }

    Board flipped_board{flipBoard(board)};
    auto node = _generator->getNode(flipped_board);
    if(node == nullptr)
        return Board::Unknown;
    auto flipped_status = alphaBeta(node, depth, flipped_board.isComputerTurn());
    switch(flipped_status)
    {
    case Board::Win:
        return Board::Lose;
    case Board::SubWin:
        return Board::SubLose;
    case Board::SubLose:
        return Board::SubWin;
    case Board::Lose:
        return Board::Win;
    default:
        return flipped_status;
    }
}

Board::BoardStatus Algo_minimax::alphaBeta(GameNode *node, quint8 depth, bool maximizing_player, Board::BoardStatus alpha, Board::BoardStatus beta)
{
    if(node->isEndNode() || depth <= 0)
        return node->status();

    if(maximizing_player)
    {
        Board::BoardStatus best_status = Board::Lose;
        auto child_list = node->children();
        for(auto iter=begin(child_list); iter!=end(child_list); iter++)
        {
            auto child_status = alphaBeta(iter.value(), depth-1, false, alpha, beta);
            best_status = qMax(best_status, childStatusToParentStatus(child_status));
            alpha = qMax(alpha, best_status);
            if(alpha >= beta)
                break;
        }
        return best_status;
    }
    else
    {
        Board::BoardStatus worst_status = Board::Win;
        auto child_list = node->children();
        for(auto iter=begin(child_list); iter!=end(child_list); iter++)
        {
            auto child_status = alphaBeta(iter.value(), depth-1, true, alpha, beta);
            worst_status = qMin(worst_status, childStatusToParentStatus(child_status));
            beta = qMin(beta, worst_status);
            if(alpha >= beta)
                break;
        }
        return worst_status;
    }
}

Board Algo_minimax::flipBoard(const Board &board)
{
    Board flipped_board;
    flipped_board.setComputerFirst(!board.isComputerFirst());
    for(int i=0; i<Board::CELL_COUNT; i++)
    {
        switch(board.at(i))
        {
        case Board::CellStatus::Computer:
            flipped_board.setCell(i, Board::CellStatus::Player);
            break;
        case Board::CellStatus::Player:
            flipped_board.setCell(i, Board::CellStatus::Computer);
            break;
        case Board::CellStatus::None:
            flipped_board.setCell(i, Board::CellStatus::None);
            break;
        }
    }
    return flipped_board;
}

Board::BoardStatus Algo_minimax::childStatusToParentStatus(Board::BoardStatus child_status)
{
    switch(child_status)
    {
    case Board::Win:
        return Board::SubWin;
    case Board::Lose:
        return Board::SubLose;
    default:
        return child_status;
    }
}
