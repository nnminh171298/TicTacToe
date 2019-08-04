#include "algo_minimax.h"
#include "algo_random.h"
#include "gamenode.h"
#include "gametreegenerator.h"

#include <random>
using namespace std;

Algo_minimax::Algo_minimax(std::shared_ptr<GameTreeGenerator> generator)
    : _generator{generator}
{
    _depth = std::numeric_limits<quint8>::max();
}

void Algo_minimax::setDepth(quint8 depth)
{
    _depth = depth;
}

Board::BoardStatus Algo_minimax::evaluateBoard(const Board &board)
{
    if(board.isComputerFirst())
    {
        _current_node = _generator->getNode(board);
        if(_current_node == nullptr)
            return Board::Unknown;
        return alphaBeta(_current_node, _depth, board.isComputerTurn());
    }

    Board flipped_board{flipBoard(board)};
    _current_node = _generator->getNode(flipped_board);
    if(_current_node == nullptr)
        return Board::Unknown;
    auto flipped_status = alphaBeta(_current_node, _depth, flipped_board.isComputerTurn());
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

int Algo_minimax::getNextMove(const Board &board)
{
    auto status = evaluateBoard(board);

    auto child_list = _current_node->children();
    QList<int> chosen_list;
    for(auto iter=begin(child_list); iter!=end(child_list); iter++)
        if(alphaBeta(iter.value(), _depth-1, !board.isComputerTurn()) == status)
            chosen_list.append(iter.key());
    if(chosen_list.length() == 0)
        return Algo_random().getNextMove(board);

    random_device random_device;
    mt19937 generator(random_device());
    shuffle(begin(chosen_list), end(chosen_list), generator);
    return chosen_list.first();
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
