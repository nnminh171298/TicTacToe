#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGroupBox>
#include <QButtonGroup>
#include <QPushButton>
#include <QGridLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QThread>
#include <QLineEdit>
#include <QLabel>
#include <QHeaderView>
QT_BEGIN_NAMESPACE
class GameEngine;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void tableWidgetClicked(int row, int column);
    void displayMove(int cellNumber, bool computerMove, const QList<int> choiceList, const qint8 heuristicValue);
    void goFirst();
    void reset();

signals:
    void playerMoveMade(int cellNumber);

private:
    void makeGameBox();
    void updateBoardStatus(int status);

    GameEngine *gameEngine;
    QThread workerThread;

    QGroupBox *gameBox;
    QButtonGroup *goFirstButtonGroup;
    QPushButton *computerFirstButton;
    QPushButton *playerFirstButton;
    QPushButton *resetButton;
    QTableWidget *tableWidget;
    QLineEdit *boardStatusEdit;
    QLineEdit *computerChoicesEdit;
    QLineEdit *computerAnalysisEdit;
};

#endif // MAINWINDOW_H
