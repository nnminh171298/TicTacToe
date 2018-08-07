#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QDebug>
#include <QThread>

QT_BEGIN_NAMESPACE
class GameEngine;
QT_END_NAMESPACE

class Backend : public QObject
{
    Q_OBJECT
public:
    explicit Backend(QObject *parent = nullptr);
    ~Backend();

signals:
    void reset();
    void start();
    void goFirst(bool computerFirst);
    void playerMoveMade(int index);
    void displayMove(int index, QString imageSource, QString computerChoicesString, int computerAnalysisValue);
    void updateBoardStatus(int status);
    void ready();

public slots:
    void playerFirstButtonClicked();
    void computerFirstButtonClicked();
    void boardClicked(int index);
    void validMoveMade(int cellNumber, bool computerMove, const QList<int> choiceList = QList<int>(), const qint8 heuristicValue = 0);

private:
    GameEngine *gameEngine;
    QThread workerThread;

    QString boardStatusString;
    QString computerChoicesString;
    int computerAnalysisValue;
};

#endif // BACKEND_H
