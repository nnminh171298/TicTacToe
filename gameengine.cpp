#include "gameengine.h"
#include "node.h"
#include <QDebug>
#include <QElapsedTimer>

GameEngine::GameEngine(QObject *parent) : QObject(parent)
{
}

void GameEngine::playerMoveMade(int cellNumber)
{
    if(board.at(cellNumber) != None || !playerTurn)
        return;

    playerTurn = false;
    emit displayMove(cellNumber, false);
    GameStatus status = getBoardStatus();
    emit updateBoardStatus(status);

    board[cellNumber] = Player;

    QList<Node *> childList = currentNode->findChildren<Node *>(QString(), Qt::FindDirectChildrenOnly);
    int childIndex = board.mid(1, cellNumber).count(None);
    currentNode = childList.at(childIndex);

    if(status == Unknown)
        makeComputerMove(alphaBeta(currentNode, MIN, MAX, true));
}

void GameEngine::reset()
{
    playerTurn = false;
    if(originNode)
    {
        delete originNode;
        originNode = nullptr;
    }
    originNode = new Node;
    currentNode = originNode;
    board.fill(None, CELL_COUNT);
}

void GameEngine::goFirst(bool computerFirst)
{
    generateNodes(originNode, computerFirst);
    if(computerFirst)
        makeComputerMove(alphaBeta(currentNode, MIN, MAX, true));
    else
        playerTurn = true;
}

void GameEngine::generateNodes(Node *parentNode, const bool computerMove)
{
    for(int i=1; i<CELL_COUNT; i++)
    {
        if(board.at(i) == None)
        {
            Node *childNode = new Node(parentNode);

            childNode->thisMove = i;
            childNode->mapToThisMove = parentNode->mapToThisMove + QString("%1").arg(childNode->thisMove);
            if(computerMove)
                board[i] = Computer;
            else
                board[i] = Player;

            GameStatus status = getBoardStatus();
            switch(status)
            {
            case Win:
                childNode->terminateNode = true;
                childNode->heuristicValue = MAX;
                break;
            case Lose:
                childNode->terminateNode = true;
                childNode->heuristicValue = MIN;
                break;
            case Tie:
                childNode->terminateNode = true;
                break;
            case Unknown:
                generateNodes(childNode, !computerMove);
            }
            board[i] = None;
        }
    }
}

GameEngine::GameStatus GameEngine::getBoardStatus()
{
    const QVector<QVector<int>> winPositions = {{1,2,3}, {4,5,6}, {7,8,9}, {1,5,9},
                                                {1,4,7}, {2,5,8}, {3,6,9}, {3,5,7}};

    for(int position = 0; position < winPositions.length(); position++)
    {
        if(board.at(winPositions[position][0]) != None &&
                board.at(winPositions[position][0]) == board.at(winPositions[position][1]) &&
                board.at(winPositions[position][0]) == board.at(winPositions[position][2]))
        {
            if(board.at(winPositions[position][0]) == Player)
                return Lose;
            if(board.at(winPositions[position][0]) == Computer)
                return Win;
        }
    }

    // out of for loop, check for tie
    int noneCellCount = 0;
    for(int i = 1; i < CELL_COUNT; i++)
        if(board.at(i) == None)
            noneCellCount++;
    if(noneCellCount == 0)
        return Tie;

    // none of the previous statuses matched
    return Unknown;
}

qint8 GameEngine::alphaBeta(Node *currentNode, qint8 alpha, qint8 beta, const bool maximizingPlayer)
{
    if(currentNode->terminateNode)
        return currentNode->heuristicValue;

    if(maximizingPlayer)
    {
        qint8 heuristicValue = MIN;
        QList<Node *> childList = currentNode->findChildren<Node *>(QString(), Qt::FindDirectChildrenOnly);
        for(int i=0; i<childList.length(); i++)
        {
            heuristicValue = qMax(heuristicValue, alphaBeta(childList.at(i), alpha, beta, false));
            currentNode->heuristicValue = heuristicValue;
            alpha = qMax(alpha, heuristicValue);
            if(alpha > beta)
                break;
        }
        return heuristicValue;
    }
    else
    {
        qint8 heuristicValue = MAX;
        QList<Node *> childList = currentNode->findChildren<Node *>(QString(), Qt::FindDirectChildrenOnly);
        for(int i=0; i<childList.length(); i++)
        {
            heuristicValue = qMin(heuristicValue, alphaBeta(childList.at(i), alpha, beta, true));
            currentNode->heuristicValue = heuristicValue;
            beta = qMin(beta, heuristicValue);
            if(alpha > beta)
                break;
        }
        return heuristicValue;
    }
}

void GameEngine::makeComputerMove(qint8 heuristicValue)
{
    QList<Node *> childList = currentNode->findChildren<Node *>(QString(), Qt::FindDirectChildrenOnly);
    QList<int> cellList;

    for(int i=0; i<childList.length(); i++)
    {
        if(childList.at(i)->heuristicValue == heuristicValue)
            cellList.append(childList.at(i)->thisMove);
    }

    qDebug() << cellList;

    if(cellList.length() > 0)
    {
        // choose a move in cellList
        int numberOfChoices = cellList.length();
        QRandomGenerator *generator = QRandomGenerator::global();
        int choice = generator->bounded(numberOfChoices);
        int cellNumber = cellList.at(choice);
        qDebug() << cellNumber;
        board[cellNumber] = Computer;

        // increment current node to computer last move
        int childIndex = board.mid(1, cellNumber).count(None);
        currentNode = childList.at(childIndex);

        emit displayMove(cellNumber, true, cellList, heuristicValue);
    }

    GameStatus status = getBoardStatus();
    emit updateBoardStatus(status);
    if(status == Unknown)
        playerTurn = true;
}
