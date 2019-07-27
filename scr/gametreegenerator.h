#ifndef GAMETREEGENERATOR_H
#define GAMETREEGENERATOR_H

#include <QMap>
#include <QObject>

#include "board.h"

class GameNode;

class GameTreeGenerator : public QObject
{
    Q_OBJECT
public:
    explicit GameTreeGenerator(QObject *parent = nullptr);

    GameNode *getNode(const Board &board) const;
    void generate();

signals:

public slots:

private:
    QString boardToString(const Board &board) const;
    void recursiveGenerate(GameNode *parent, Board::CellStatus current_player);

    GameNode *_root;
    Board _board;
    QMap<QString, GameNode *> _node_map;
};

#endif // GAMETREEGENERATOR_H
