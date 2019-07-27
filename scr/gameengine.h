#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>

#include "algo.h"
#include "board.h"

QT_BEGIN_NAMESPACE
class QTimer;
QT_END_NAMESPACE

class GameEngine : public QObject
{
    Q_OBJECT
public:
    explicit GameEngine(QObject *parent = nullptr);
    void setAlgo(std::shared_ptr<Algo> algo);

    void reset(bool computer_first);
    int getMoveNum() const;
    bool isComputerTurn() const;
    bool isUndoAvailable() const;
    bool isRedoAvailable() const;
    void undo();
    void redo();
    void boardClicked(int index);

signals:
    void setMainBoard(const Board &board);
    void setSubBoard(int index, const Board &board, Board::BoardStatus board_status);

private:
    void startMakeCompMoveTimer();
    void stopMakeCompMoveTimer();
    void makeComputerMove();
    void sendSubBoards();

    std::shared_ptr<Algo> _algo;
    Board _board;
    QList<int> _move_history;

    QTimer *_make_comp_move_timer;
    bool _is_making_comp_move;
    bool _computer_first;
    int _last_move_ptr;
};

#endif // GAMEENGINE_H
