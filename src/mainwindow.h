#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "physicsystem.h"
#include "map.h"
#include "crazybricks.h"

#include <QVBoxLayout>
#include <QStackedLayout>
#include <QGridLayout>
#include <QComboBox>

QT_BEGIN_NAMESPACE
class QPushButton;
class QLCDNumber;
class QLabel;
QT_END_NAMESPACE

class MainWindow : public QWidget{
    Q_OBJECT
    
public:
    explicit MainWindow();
    ~MainWindow();

public slots:
    void pauseGame();
    void gameEnded(QString);
    void startGame();
    void setBuilderOption(int choice);

private:
    QLabel* createLabel(const QString &text);
    QWidget* newGame();

private:
    QPushButton *pauseButton;
    QPushButton *newGameButton;
    CrazyBricks *game;
    QLCDNumber *scoreTopGamer;
    QLCDNumber *scoreBottomGamer;
    QLCDNumber *lifesTopGamer;
    QLCDNumber *lifesBottomGamer;
    QVBoxLayout *mainLayout;
    QGridLayout* gameLayout;
    QGridLayout* menuLayout;
    QGridLayout *scoreLayout;
    QStackedLayout* stackedLayout;
    QWidget* menuPageWidget;
    QWidget* gamePageWidget;
    QComboBox* builderCombo;
    QLabel* userWinner;
    int m_comboChoice;
    bool m_paused;
};

#endif // MAINWINDOW_H
