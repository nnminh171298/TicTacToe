#include "algo_fillblank.h"
#include "algo_minimax.h"
#include "algo_random.h"
#include "backend.h"
#include "gametreegenerator.h"

Backend::Backend(QObject *parent) : QObject(parent)
{
    createAlgorithms();
    _game_engine = new GameEngine(this);
    _game_engine->setAlgo(_algo_list.first());
    connect(_game_engine, &GameEngine::setMainBoard, this, &Backend::setMainBoard);
    connect(_game_engine, &GameEngine::setSubBoard, this, &Backend::setSubBoard);
}

void Backend::reset(bool computer_first)
{
    _game_engine->reset(computer_first);
}

void Backend::boardClicked(int index)
{
    _game_engine->boardClicked(index);
}

void Backend::undoClicked()
{
    _game_engine->undo();
}

void Backend::redoClicked()
{
    _game_engine->redo();
}

void Backend::modeChanged(int index)
{
    _game_engine->setAlgo(_algo_list[index]);
}

void Backend::setMainBoard(const Board &board)
{
    for(int i=0; i<Board::CELL_COUNT; i++)
    {
        switch(board.at(i))
        {
        case Board::CellStatus::Player:
            emit setCellColor(i, _red500);
            break;
        case Board::CellStatus::Computer:
            emit setCellColor(i, _blue500);
            break;
        case Board::CellStatus::None:
            emit setCellColor(i, _gray700);
            break;
        }
    }
    setAnalysisToolbarText(board.status());
    emit setUndoEnable(_game_engine->isUndoAvailable());
    emit setRedoEnable(_game_engine->isRedoAvailable());
}

void Backend::setSubBoard(int index, const Board &board, Board::BoardStatus board_status)
{
    for(int i=0; i<Board::CELL_COUNT; i++)
    {
        switch(board.at(i))
        {
        case Board::CellStatus::Player:
            emit setCellColor(i, _red500, index);
            break;
        case Board::CellStatus::Computer:
            emit setCellColor(i, _blue500, index);
            break;
        case Board::CellStatus::None:
            emit setCellColor(i, _gray700, index);
            break;
        }
    }

    switch(board_status)
    {
    case Board::BoardStatus::Unknown:
        emit setIndicatorColor(index, _gray700);
        break;
    case Board::BoardStatus::Win:
    case Board::BoardStatus::SubWin:
        emit setIndicatorColor(index, _blue500);
        break;
    case Board::BoardStatus::Tie:
        emit setIndicatorColor(index, _lime500);
        break;
    case Board::BoardStatus::Lose:
    case Board::BoardStatus::SubLose:
        emit setIndicatorColor(index, _red500);
        break;
    }
}

void Backend::setAnalysisToolbarText(Board::BoardStatus board_status)
{
    switch(board_status)
    {
    case Board::BoardStatus::Tie:
        emit setAnalysisText("It's a tie");
        break;
    case Board::BoardStatus::Win:
        emit setAnalysisText("Computer win");
        break;
    case Board::BoardStatus::Lose:
        emit setAnalysisText("Player win");
        break;
    default:
        if(_game_engine->isComputerTurn())
            emit setAnalysisText("Computer turn");
        else
            emit setAnalysisText("Player turn");
        break;
    }
    emit setAnalysisNum(QString("%1").arg(_game_engine->getMoveNum()));
}

void Backend::createAlgorithms()
{
    auto generator = std::make_shared<GameTreeGenerator>();
    generator->generate();

    auto algo_minimax = std::make_shared<Algo_minimax>(generator);
    algo_minimax->setDepth(2);
    _algo_list.append(algo_minimax);

    auto algo_fillBlank = std::make_shared<Algo_fillBlank>();
    _algo_list.append(algo_fillBlank);

    auto algo_random = std::make_shared<Algo_random>();
    _algo_list.append(algo_random);
}
