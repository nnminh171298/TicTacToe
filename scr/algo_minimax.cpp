#include "algo_minimax.h"
#include "algo_random.h"
#include "gamenode.h"
#include "gametreegenerator.h"

#include <random>
using namespace std;

Algo_minimax::Algo_minimax(std::shared_ptr<GameTreeGenerator> generator) : _generator{generator}
{

}

Board::BoardStatus Algo_minimax::evaluateBoard(const Board &board, bool is_computer_turn)
{
    _current_node = _generator->getNode(board);
    if(_current_node != nullptr)
        return alphaBeta(_current_node, is_computer_turn);

    _current_node = _generator->getNode(flipBoard(board));
    if(_current_node != nullptr)
    {
        auto flipped_status = alphaBeta(_current_node, !is_computer_turn);
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

    return Board::Unknown;
}

int Algo_minimax::getNextMove(const Board &board)
{
    auto status = evaluateBoard(board, true);
    if(status == Board::Unknown)
        return Algo_random().getNextMove(board);

    auto child_list = _current_node->children();
    QList<int> chosen_list;
    for(auto iter=begin(child_list); iter!=end(child_list); iter++)
    {
        if(iter.value()->isEndNode() == true && iter.value()->status() == Board::Win)
            return iter.key();
        if(alphaBeta(iter.value(), _generator->getNode(board) == nullptr) == status)
            chosen_list.append(iter.key());
    }
    if(chosen_list.length() == 0)
        return Algo_random().getNextMove(board);

    random_device random_device;
    mt19937 generator(random_device());
    shuffle(begin(chosen_list), end(chosen_list), generator);
    return chosen_list.first();
}

QString Algo_minimax::getAlgoName() const
{
    return "Minimax";
}

Board::BoardStatus Algo_minimax::alphaBeta(GameNode *node, bool maximizing_player, Board::BoardStatus alpha, Board::BoardStatus beta)
{
    if(node->isEndNode())
        return node->status();

    if(maximizing_player)
    {
        Board::BoardStatus best_status = Board::Lose;
        auto child_list = node->children();
        for(auto iter=begin(child_list); iter!=end(child_list); iter++)
        {
            best_status = qMax(best_status, alphaBeta(iter.value(), false, alpha, beta));
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
            worst_status = qMin(worst_status, alphaBeta(iter.value(), true, alpha, beta));
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
