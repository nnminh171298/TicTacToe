#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include <QVector>
#include <QRandomGenerator>
#include <QFuture>
#include <QtConcurrent/QtConcurrentRun>
QT_BEGIN_NAMESPACE
class Node;
QT_END_NAMESPACE

class GameEngine : public QObject
{
    Q_OBJECT
public:
    explicit GameEngine(QObject *parent = nullptr);
    enum CellStatus{Player = 0, Computer, None};
    enum GameStatus{Lose = 0, Win, Tie, Unknown};

signals:
    void displayMove(int cellNumber, bool computerMove, const QList<int> choiceList = QList<int>(), const qint8 heuristicValue = 0);
    void updateBoardStatus(int status);
    void ready();

public slots:
    void start();
    void playerMoveMade(int cellNumber);
    void reset();
    void goFirst(bool computerFirst);

private:
    Node *generateNodes(Node *parentNode, QVector<int> board, const bool computerMove);
    GameStatus getBoardStatus(QVector<int> board);
    qint8 alphaBeta(Node *currentNode, qint8 alpha, qint8 beta, const bool maximizingPlayer = true);
    void makeComputerMove(qint8 heuristicValue);

    const int CELL_COUNT = 10;  // a blank cell at the start for readability
    qint8 MIN = std::numeric_limits<qint8>::min();
    qint8 MAX = std::numeric_limits<qint8>::max();
    QVector<int> board;
    bool playerTurn;
    Node *computerFirstOriginNode = nullptr;
    Node *playerFirstOriginNode = nullptr;
    Node *currentNode;
};

#endif // GAMEENGINE_H
