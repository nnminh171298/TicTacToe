#include "backend.h"
#include "gameengine.h"

Backend::Backend(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<QList<int>>("QList<int>");
    gameEngine = new GameEngine;

    connect(this, &Backend::reset,          gameEngine, &GameEngine::reset);
    connect(this, &Backend::start,          gameEngine, &GameEngine::start);
    connect(this, &Backend::goFirst,        gameEngine, &GameEngine::goFirst);
    connect(this, &Backend::playerMoveMade, gameEngine, &GameEngine::playerMoveMade);

    connect(gameEngine, &GameEngine::validMoveMade,     this, &Backend::validMoveMade);
    connect(gameEngine, &GameEngine::updateBoardStatus, this, &Backend::updateBoardStatus);
    connect(gameEngine, &GameEngine::ready,             this, &Backend::ready);

    gameEngine->moveToThread(&workerThread);
    workerThread.start();

    emit reset();
    emit start();
}

Backend::~Backend()
{
    workerThread.quit();
    workerThread.wait();
}

void Backend::playerFirstButtonClicked()
{
    emit reset();
    emit goFirst(false);
}

void Backend::computerFirstButtonClicked()
{
    emit reset();
    emit goFirst(true);
}

void Backend::boardClicked(int index)
{
    emit playerMoveMade(index+1);
}

void Backend::validMoveMade(int cellNumber, bool computerMove, const QList<int> choiceList, const qint8 heuristicValue)
{
    int index = cellNumber-1;
    QString imageSource = QString();
    if(computerMove)
    {
        imageSource += "qrc:/images/X.png";
        computerChoicesString = QString("(");
        for(int i=0; i<choiceList.length(); i++)
            computerChoicesString += QString("%1, ").arg(choiceList.at(i));
        computerChoicesString.replace(computerChoicesString.length()-2, 2, QChar(')'));
        computerAnalysisValue = heuristicValue;
    }
    else
        imageSource += "qrc:/images/O.png";

    emit displayMove(index, imageSource, computerChoicesString, computerAnalysisValue);
}
