#include "board.h"

using namespace std;

Board::Board(QObject *parent) : QObject(parent)
{
    _board = QVector<CellStatus>(CELL_COUNT);
    reset();
}

Board::Board(const Board &board)
{
    _board = board._board;
}

void Board::reset()
{
    fill(begin(_board), end(_board), CellStatus::None);
}

Board::BoardStatus Board::status() const
{
    const QVector<QVector<int>> win_poses = {{0,1,2}, {3,4,5}, {6,7,8}, {0,4,8},
                                            {0,3,6}, {1,4,7}, {2,5,8}, {2,4,6}};
    for(int pos = 0; pos < win_poses.length(); pos++)
    {
        if(_board.at(win_poses.at(pos).at(0)) != CellStatus::None
                && _board.at(win_poses.at(pos).at(0)) == _board.at(win_poses.at(pos).at(1))
                && _board.at(win_poses.at(pos).at(0)) == _board.at(win_poses.at(pos).at(2)))
        {
            if(_board.at(win_poses.at(pos).at(0)) == CellStatus::Player)
                return BoardStatus::Lose;
            if(_board.at(win_poses.at(pos).at(0)) == CellStatus::Computer)
                return BoardStatus::Win;
        }
    }

    // out of for loop, check for tie
    if(none_of(begin(_board), end(_board), [](CellStatus cell){ return cell == CellStatus::None; }))
        return BoardStatus::Tie;

    // none of the previous statuses matched
    return BoardStatus::Unknown;
}

int Board::at(int index) const
{
    return _board.at(index);
}

void Board::setCell(int index, Board::CellStatus value)
{
    _board[index] = value;
}

void Board::setComputerFirst(bool computer_first)
{
    _computer_first = computer_first;
}

bool Board::isComputerFirst() const
{
    return _computer_first;
}

bool Board::isComputerTurn() const
{
    auto computer_count = count(begin(_board), end(_board), CellStatus::Computer);
    auto player_count = count(begin(_board), end(_board), CellStatus::Player);
    if(computer_count == player_count)
        return _computer_first;
    else
        return player_count > computer_count;
}
