#ifndef BOARD_H
#define BOARD_H

#include <QObject>

class Board : public QObject
{
    Q_OBJECT
public:
    explicit Board(QObject *parent = nullptr);
    Board(const Board &board);
    constexpr static const int CELL_COUNT{9};
    enum CellStatus : quint8 {Player, Computer, None};
    enum BoardStatus: quint8 {Lose, SubLose, Tie, Unknown, SubWin, Win};

    void        reset();
    int         at(int index) const;
    void        setCell(int index, CellStatus value);

    BoardStatus status() const;

private:
    QVector<CellStatus> _board;
};

#endif // BOARD_H
