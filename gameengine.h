#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include <QVector>
#include <QRandomGenerator>
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

public slots:
    void playerMoveMade(int cellNumber);
    void reset();
    void goFirst(bool computerFirst);

private:
    void generateNodes(Node *parentNode, const bool computerMove);
    GameStatus getBoardStatus();
    qint8 alphaBeta(Node *currentNode, qint8 alpha, qint8 beta, const bool maximizingPlayer = true);
    void makeComputerMove(qint8 heuristicValue);

    const int CELL_COUNT = 10;  // a blank cell at the start for readability
    qint8 MIN = std::numeric_limits<qint8>::min();
    qint8 MAX = std::numeric_limits<qint8>::max();
    QVector<int> board;
    bool playerTurn;
    Node *originNode = nullptr;
    Node *currentNode;
};

#endif // GAMEENGINE_H
