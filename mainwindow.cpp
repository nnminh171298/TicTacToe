#include "mainwindow.h"
#include "gameengine.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    qRegisterMetaType<QList<int>>("QList<int>");

    gameEngine = new GameEngine;

    makeGameBox();

    setWindowFlags(Qt::Widget | Qt::MSWindowsFixedSizeDialogHint);
    setWindowTitle("Tic Tac Toe");
    setStyleSheet("QLineEdit{border: 1px solid gray;}");

    QWidget *centralWidget = new QWidget;
    QGridLayout *layout = new QGridLayout(centralWidget);
    layout->addWidget(gameBox, 0, 0);
    setCentralWidget(centralWidget);

    connect(goFirstButtonGroup, QOverload<int>::of(&QButtonGroup::buttonClicked), gameEngine, &GameEngine::goFirst);
    connect(goFirstButtonGroup, QOverload<int>::of(&QButtonGroup::buttonClicked), this, &MainWindow::goFirst);
    connect(resetButton, &QPushButton::clicked, gameEngine, &GameEngine::reset);
    connect(resetButton, &QPushButton::clicked, this, &MainWindow::reset);
    connect(tableWidget, &QTableWidget::cellClicked, this, &MainWindow::tableWidgetClicked);

    connect(this, &MainWindow::playerMoveMade,  gameEngine, &GameEngine::playerMoveMade);
    connect(this, &MainWindow::start,           gameEngine, &GameEngine::start);

    connect(gameEngine, &GameEngine::displayMove,       this, &MainWindow::displayMove);
    connect(gameEngine, &GameEngine::updateBoardStatus, this, &MainWindow::updateBoardStatus);
    connect(gameEngine, &GameEngine::ready,             this, &MainWindow::ready);

    gameEngine->moveToThread(&workerThread);
    workerThread.start();
    resetButton->click();
    emit start();
}

MainWindow::~MainWindow()
{
    workerThread.quit();
    workerThread.wait();
}

void MainWindow::tableWidgetClicked(int row, int column)
{
    int cellNumber = QString("%1%2").arg(row).arg(column).toInt(nullptr, 3)+1;
    emit playerMoveMade(cellNumber);
}

void MainWindow::displayMove(int cellNumber, bool computerMove, const QList<int> choiceList, const qint8 heuristicValue)
{
    QImage *image;
    if(computerMove)
    {
        image = new QImage(":/images/X.png");

        QString choicesString = QString();
        for(int i=0; i<choiceList.length(); i++)
            choicesString += QString("%1 ").arg(choiceList.at(i));
        computerChoicesEdit->setText(choicesString);

        switch(heuristicValue)
        {
        case 0:
            computerAnalysisEdit->setStyleSheet("background-color: cyan;");
            computerAnalysisEdit->setText("It's a tie");
            break;
        case std::numeric_limits<qint8>::max():
            computerAnalysisEdit->setStyleSheet("background-color: lime;");
            computerAnalysisEdit->setText("Computer wins");
            break;
        case std::numeric_limits<qint8>::min():
            computerAnalysisEdit->setStyleSheet("background-color: red;");
            computerAnalysisEdit->setText("Computer loses");
            break;
        }
    }
    else
        image = new QImage(":/images/O.png");
    QTableWidgetItem *item = new QTableWidgetItem;
    item->setData(Qt::DecorationRole, QPixmap::fromImage(*image).scaled(scaledDimension, scaledDimension));
    int cellIndex = QString("%1").arg(cellNumber-1, 2, 3).toInt();
    tableWidget->setItem(cellIndex/10, cellIndex%10, item);
}

void MainWindow::goFirst()
{
    computerFirstButton->setDisabled(true);
    playerFirstButton->setDisabled(true);
}

void MainWindow::reset()
{
    computerFirstButton->setDisabled(false);
    playerFirstButton->setDisabled(false);
    tableWidget->clearContents();
    boardStatusEdit->clear();
    boardStatusEdit->setStyleSheet("background-color: white;");
    computerChoicesEdit->clear();
    computerAnalysisEdit->clear();
    computerAnalysisEdit->setStyleSheet("background-color: white;");
}

void MainWindow::ready()
{
    programStatusLabel->setText("Ready.");
}

void MainWindow::makeGameBox()
{
    gameBox = new QGroupBox;

    goFirstButtonGroup = new QButtonGroup(this);

    playerFirstButton = new QPushButton("Player 1st");
    goFirstButtonGroup->addButton(playerFirstButton, 0);

    computerFirstButton = new QPushButton("Computer 1st");
    goFirstButtonGroup->addButton(computerFirstButton, 1);

    resetButton = new QPushButton("Reset");

    tableWidget = new QTableWidget(3, 3);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setFocusPolicy(Qt::NoFocus);
    tableWidget->setStyleSheet("selection-background-color: transparent");

#ifdef Q_OS_ANDROID
    scaledDimension = 300;
#else
    scaledDimension = 100;
#endif

    for(int row=0; row<tableWidget->rowCount(); row++)
    {
        tableWidget->setRowHeight(row, scaledDimension);
        tableWidget->setColumnWidth(row, scaledDimension);
    }

    int tableWidth = 2 + tableWidget->verticalHeader()->width();
    for (int i=0; i<tableWidget->columnCount(); i++)
        tableWidth += tableWidget->columnWidth(i);

    int tableHeight = 2 + tableWidget->horizontalHeader()->height();
    for (int i=0; i<tableWidget->rowCount(); i++)
        tableHeight += tableWidget->rowHeight(i);

    tableWidget->setMaximumHeight(tableHeight);
    tableWidget->setMinimumHeight(tableHeight);
    tableWidget->setMaximumWidth(tableWidth);
    tableWidget->setMinimumWidth(tableWidth);

    QLabel *boardStatusLabel = new QLabel("Board status:");
    boardStatusEdit = new QLineEdit;
    boardStatusEdit->setReadOnly(true);

    QLabel *computerChoicesLabel = new QLabel("Computer choices:");
    computerChoicesEdit = new QLineEdit;
    computerChoicesEdit->setReadOnly(true);

    QLabel *computerAnalysisLabel = new QLabel("Computer analysis:");
    computerAnalysisEdit = new QLineEdit;
    computerAnalysisEdit->setReadOnly(true);

    programStatusLabel = new QLabel("Loading... (max 10s)");

    QGridLayout *gameBoxLayout = new QGridLayout(gameBox);
    gameBoxLayout->addWidget(playerFirstButton,     0, 0);
    gameBoxLayout->addWidget(computerFirstButton,   0, 1);
    gameBoxLayout->addWidget(resetButton,           0, 2);
    gameBoxLayout->addWidget(tableWidget,           1, 0, 1, 3, Qt::AlignCenter);
    gameBoxLayout->addWidget(boardStatusLabel,      2, 0, Qt::AlignBottom);
    gameBoxLayout->addWidget(boardStatusEdit,       2, 1, 1, 2, Qt::AlignBottom);
    gameBoxLayout->addWidget(computerChoicesLabel,  3, 0, Qt::AlignBottom);
    gameBoxLayout->addWidget(computerChoicesEdit,   3, 1, 1, 2, Qt::AlignBottom);
    gameBoxLayout->addWidget(computerAnalysisLabel, 4, 0, Qt::AlignBottom);
    gameBoxLayout->addWidget(computerAnalysisEdit,  4, 1, 1, 2, Qt::AlignBottom);
    gameBoxLayout->addWidget(programStatusLabel,    5, 0, 1, 3, Qt::AlignRight);
}

void MainWindow::updateBoardStatus(int status)
{
    switch(status)
    {
    case GameEngine::Win:
        boardStatusEdit->setStyleSheet("background-color: lime;");
        boardStatusEdit->setText("Computer wins");
        break;
    case GameEngine::Lose:
        boardStatusEdit->setStyleSheet("background-color: red;");
        boardStatusEdit->setText("Computer loses");
        break;
    case GameEngine::Tie:
        boardStatusEdit->setStyleSheet("background-color: cyan;");
        boardStatusEdit->setText("It's a tie");
        break;
    case GameEngine::Unknown:
        boardStatusEdit->setStyleSheet("background-color: yellow;");
        boardStatusEdit->setText("Unknown");
        break;
    }
}
