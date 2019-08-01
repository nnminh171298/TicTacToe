#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>

#include "algo.h"
#include "gameengine.h"

class Backend : public QObject
{
    Q_OBJECT
public:
    explicit Backend(QObject *parent = nullptr);

signals:
    void setCellColor(int cell_index, const QString &cell_color, int emitted_sub_board_id = -1);
    void setIndicatorColor(int sub_board_index, const QString &indicator_color);
    void setAnalysisText(const QString &str);
    void setAnalysisNum(const QString &str);
    void setUndoEnable(bool enable);
    void setRedoEnable(bool enable);

public slots:
    void reset(bool computer_first);
    void boardClicked(int index);
    void undoClicked();
    void redoClicked();
    void modeChanged(int index);

private slots:
    void setMainBoard(const Board &board);
    void setSubBoard(int index, const Board &board, Board::BoardStatus board_status);

private:
    void setAnalysisToolbarText(Board::BoardStatus board_status);
    void createAlgorithms();

    GameEngine *_game_engine;
    QList<std::shared_ptr<Algo>> _algo_list;

    const QString _red500{"#f44336"};
    const QString _blue500{"#2196f3"};
    const QString _lime500{"#CDDC39"};
    const QString _gray700{"#616161"};
};

#endif // BACKEND_H
