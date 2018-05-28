

#ifndef CRAZYBRICKS_H
#define CRAZYBRICKS_H

#include <QObject>
#include <QWidget>
#include <QKeyEvent>

#include "mapbuilder.h"
#include "map.h"
#include "standardbuilder.h"
#include "crossbuilder.h"
#include "dualbuilder.h"
#include "easyfactory.h"
#include "standardfactory.h"
#include "paintvisitor.h"

class CrazyBricks :  public QWidget
{
    Q_OBJECT
public:
    explicit CrazyBricks(int width, int height, QWidget *parent = 0);
    void createMap(MapBuilder& builder, int choice);
    PhysicSystem* getEngine();
    void keyPressEvent(QKeyEvent* e);
    void keyReleaseEvent(QKeyEvent *e);
    void initializeLifeCounters();
    int updateBottomScore(int score);
    int updateTopScore(int score);
    int getTopPlatform();
    int getBottomPlatform();
    void freezePlatform(int time, int id);
    int updateBottomLifes(int lifes);
    int updateTopLifes(int lifes);
    ~CrazyBricks();

public:
    Map* m_map;
    PhysicSystem* m_engine;

signals:
    void newPosition(int bodyAId, float posX, float posY);
    void scoreTopChanged(int score);
    void scoreBottomChanged(int score);
    void lifesBottomChanged(int lifes);
    void lifesTopChanged(int lifes);
    void endOfGame(QString);

public slots:
    void collisionDetected(int bodyAId, int bodyBId);
    void positionChanged(int bodyId, float posX, float posY);
    void bonusStart(int posX, int posY, bonusType type,int bonusToPlatformId);
    Ball* newTopBall();
    Ball* newBottomBall();

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void endGame();

private:
    int m_width;
    int m_heigth;
    int m_scoreTopGamer;
    int m_scoreBottomGamer;
    PaintVisitor *m_painterVisitor;
    ObjectFactory *m_factory;
    int elapsed;
    QTimer *m_timerBallBottom;
    QTimer *m_timerBallTop;
    QTimer *m_theEnd;
};

#endif // CRAZYBRICKS_H
