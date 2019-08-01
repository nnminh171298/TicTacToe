#include "gameengine.h"

#include <QTimer>

using namespace std;

GameEngine::GameEngine(QObject *parent) : QObject(parent)
{
    _make_comp_move_timer = new QTimer(this);
    _make_comp_move_timer->setSingleShot(true);
    _make_comp_move_timer->setInterval(500);
    connect(_make_comp_move_timer, &QTimer::timeout, this, &GameEngine::makeComputerMove);
}

void GameEngine::setAlgo(std::shared_ptr<Algo> algo)
{
    _algo = algo;
}

void GameEngine::reset(bool computer_first)
{
    stopMakeCompMoveTimer();
    _last_move_ptr = -1;
    _move_history.clear();
    _board.reset();
    _board.setComputerFirst(computer_first);

    if(isComputerTurn())
        startMakeCompMoveTimer();
    emit setMainBoard(_board);
    sendSubBoards();
}

int GameEngine::getMoveNum() const
{
    return _last_move_ptr+2;
}

bool GameEngine::isComputerTurn() const
{
    return _board.isComputerTurn();
}

bool GameEngine::isUndoAvailable() const
{
    return _last_move_ptr != -1;
}

bool GameEngine::isRedoAvailable() const
{
    return _move_history.length() != _last_move_ptr+1;
}

void GameEngine::undo()
{
    if(_is_making_comp_move || !isUndoAvailable())
        return;
    _board.setCell(_move_history[_last_move_ptr--], Board::CellStatus::None);
    emit setMainBoard(_board);
    sendSubBoards();
}

void GameEngine::redo()
{
    if(_is_making_comp_move)
        return;

    if(!isRedoAvailable())
        return;
    boardClicked(_move_history[_last_move_ptr+1]);
}

void GameEngine::boardClicked(int index)
{
    if(_is_making_comp_move || _board.status() != Board::Unknown || _board.at(index) != Board::CellStatus::None)
        return;

    // set clicked cell
    if(isComputerTurn())
        _board.setCell(index, Board::CellStatus::Computer);
    else
        _board.setCell(index, Board::CellStatus::Player);

    // update move history
    _last_move_ptr++;
    if(_move_history.length() == _last_move_ptr)
        _move_history.append(index);
    else
        _move_history[_last_move_ptr] = index;

    emit setMainBoard(_board);
    sendSubBoards();
    if(_board.status() == Board::Unknown && isComputerTurn())
        startMakeCompMoveTimer();
}

void GameEngine::startMakeCompMoveTimer()
{
    _is_making_comp_move = true;
    _make_comp_move_timer->start();
}

void GameEngine::stopMakeCompMoveTimer()
{
    _make_comp_move_timer->stop();
    _is_making_comp_move = false;
}

void GameEngine::makeComputerMove()
{
    int chosen_index = _algo->getNextMove(_board);
    if(chosen_index < 0)
        return;
    _is_making_comp_move = false;
    boardClicked(chosen_index);
}

void GameEngine::sendSubBoards()
{
    Board empty_board;

    // get current player
    Board::CellStatus current_player;
    if(isComputerTurn())
        current_player = Board::CellStatus::Computer;
    else
        current_player = Board::CellStatus::Player;

    // loop through all subBoards
    for(int i=0; i<Board::CELL_COUNT; i++)
        if(_board.status() == Board::Unknown && _board.at(i) == Board::CellStatus::None)
        {
            _board.setCell(i, current_player);
            emit setSubBoard(i, _board, _algo->evaluateBoard(_board));
            _board.setCell(i, Board::CellStatus::None);
        }
        else
            emit setSubBoard(i, empty_board, Board::Unknown);

}
