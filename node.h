#ifndef NODE_H
#define NODE_H

#include <QObject>

class Node : public QObject
{
    Q_OBJECT
    friend class GameEngine;

public:
    explicit Node(QObject *parent = nullptr);

signals:

public slots:

private:
    qint8 thisMove;
    bool terminateNode = false;
    qint8 heuristicValue = 0;
    QString mapToThisMove = QString();
};

#endif // NODE_H
