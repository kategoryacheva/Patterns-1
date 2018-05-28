#include "mainwindow.h"
#include "crazybricks.h"
#include <QTimer>
#include <QDebug>
#include <QtGui>

static const int gameWidth = 684; //10 * 60(blocos) + 11 * 4(espaços) + 2*(40/2)espessura paredes laterais
static const int gameHeight = 500;

//static const int gameWidth = 1004; //15 blocos
//static const int gameHeight = 700;

MainWindow::MainWindow():
    m_paused(true), m_comboChoice(0){

    menuLayout = new QGridLayout;
    menuPageWidget = new QWidget(this);
    userWinner = new QLabel;
    userWinner->setText("CrazyBricks");

    builderCombo = new QComboBox();
    builderCombo->addItem("Easy Level");
    builderCombo->addItem("Hard Level");
    builderCombo->addItem("Dual PC");
    connect(builderCombo, SIGNAL(activated(int)), this, SLOT(setBuilderOption(int)));
    menuLayout->addWidget(builderCombo, 2, 0);

    newGameButton = new QPushButton(tr("&Start"));
    menuLayout->addWidget(userWinner, 0, 0);
    menuLayout->addWidget(newGameButton, 1, 0);
    connect(newGameButton, SIGNAL(clicked()), this, SLOT(startGame()));

    menuPageWidget->setLayout(menuLayout);

    stackedLayout = new QStackedLayout;
    stackedLayout->addWidget(menuPageWidget);

    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(stackedLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("CrazyBricks"));
    resize(gameWidth, gameHeight);
}

QWidget* MainWindow::newGame(){
    gamePageWidget = new QWidget();
    scoreLayout = new QGridLayout;
    gameLayout = new QGridLayout;

    game = new CrazyBricks(gameWidth, gameHeight, this);
    MapBuilder *builder;
    switch(m_comboChoice) {
    case 0:
        builder = new StandardBuilder(gameWidth, gameHeight);
        game->createMap(*builder, 1);
        qDebug() << "Choice 0: StandardBuilder";
        break;
    case 1:
        builder = new CrossBuilder(gameWidth, gameHeight);
        game->createMap(*builder, 0);
        qDebug() << "Choice 1: StandardBuilder";
        break;
    case 2:
        builder = new DualBuilder(gameWidth, gameHeight);
        game->createMap(*builder, 1);
        qDebug() << "Choice Default: StandardBuilder";
        break;
    default:
        builder = new StandardBuilder(gameWidth, gameHeight);
        game->createMap(*builder, 1);
        qDebug() << "Choice Default: StandardBuilder";
        break;
    }

    game->setFocusPolicy(Qt::StrongFocus);
    game->setAutoFillBackground(true);
    game->setFixedSize(QSize(gameWidth, gameHeight));

    pauseButton = new QPushButton(tr("&Start"));
    pauseButton->setFocusPolicy(Qt::NoFocus);

    scoreTopGamer = new QLCDNumber(5);
    scoreTopGamer->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    scoreTopGamer->setSegmentStyle(QLCDNumber::Filled);
    scoreBottomGamer = new QLCDNumber(5);
    scoreBottomGamer->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    scoreBottomGamer->setSegmentStyle(QLCDNumber::Filled);

    lifesTopGamer = new QLCDNumber(2);
    lifesTopGamer->setSegmentStyle(QLCDNumber::Filled);
    lifesTopGamer->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    lifesBottomGamer = new QLCDNumber(2);
    lifesBottomGamer->setSegmentStyle(QLCDNumber::Filled);
    lifesBottomGamer->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);

    connect(pauseButton, SIGNAL(clicked()), this, SLOT(pauseGame()));
    connect(game, SIGNAL(scoreTopChanged(int)), scoreTopGamer, SLOT(display(int)));
    connect(game, SIGNAL(scoreBottomChanged(int)), scoreBottomGamer, SLOT(display(int)));
    connect(game, SIGNAL(lifesTopChanged(int)), lifesTopGamer, SLOT(display(int)));
    connect(game, SIGNAL(lifesBottomChanged(int)), lifesBottomGamer, SLOT(display(int)));

    game->initializeLifeCounters();

    scoreLayout->addWidget(createLabel(tr("Lives:")), 0, 0);
    scoreLayout->addWidget(lifesTopGamer, 1, 0);
    scoreLayout->addWidget(createLabel(tr("Score:")), 2, 0);
    scoreLayout->addWidget(scoreTopGamer, 3, 0);
    scoreLayout->addWidget(createLabel(tr("Lives:")), 4, 0);
    scoreLayout->addWidget(lifesBottomGamer, 5, 0);
    scoreLayout->addWidget(createLabel(tr("Score:")), 6, 0);
    scoreLayout->addWidget(scoreBottomGamer, 7, 0);

    gameLayout->addLayout(scoreLayout, 0, 1);
    gameLayout->addWidget(game, 0, 0);
    gameLayout->addWidget(pauseButton, 1, 0);
    gamePageWidget->setLayout(gameLayout);

    return gamePageWidget;
}

void MainWindow::startGame(){
    stackedLayout->addWidget(newGame());
    stackedLayout->setCurrentIndex(1);
}

void MainWindow::pauseGame(){
    if(m_paused) {
        game->m_map->mapStart();
        pauseButton->setText(tr("&Pause"));
        m_paused = false;
    } else {
        game->m_map->mapPause();
        pauseButton->setText(tr("&Start"));
        m_paused = true;
    }
}

void MainWindow::gameEnded(QString str){
    userWinner->setText(str);
    qDebug() << "GAME OVER!" << str;
    m_paused = true;
    stackedLayout->setCurrentIndex(0);
    stackedLayout->removeWidget(gamePageWidget);
    delete scoreLayout;
}

void MainWindow::setBuilderOption(int choice){
    m_comboChoice = choice;
}

QLabel* MainWindow::createLabel(const QString &text){
    QLabel *lbl = new QLabel(text);
    lbl->setAlignment(Qt::AlignLeft| Qt::AlignBottom);
    return lbl;
}

MainWindow::~MainWindow(){}
