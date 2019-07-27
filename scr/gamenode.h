#ifndef GAMENODE_H
#define GAMENODE_H

#include <QMap>
#include <QObject>

#include "board.h"

class GameNode : public QObject
{
    Q_OBJECT

public:
    explicit GameNode(Board::BoardStatus status, QObject *parent = nullptr);

    bool isEndNode() const;
    Board::BoardStatus status() const;
    void addChild(GameNode *node_ptr, int leading_move);
    QMap<int, GameNode *> children() const;

private:
    Board::BoardStatus _status{Board::Unknown}; // should be heuristic value but we scan until the end
    QMap<int, GameNode *> _children;
};

#endif // GAMENODE_H
