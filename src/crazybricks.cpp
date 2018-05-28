
#define QT_USE_FAST_CONCATENATION
#define QT_USE_FAST_OPERATOR_PLUS

#include "crazybricks.h"
#include "paintvisitor.h"
#include "dumbbehaviour.h"
#include "smartbehaviour.h"


CrazyBricks::CrazyBricks(int width, int height, QWidget *parent)
    : QWidget(parent), m_scoreTopGamer(0), m_scoreBottomGamer(0), m_width(width), m_heigth(height), m_painterVisitor(NULL){
    m_engine = new PhysicSystem;
    connect(this, SIGNAL(endOfGame(QString)), parent, SLOT(gameEnded(QString)));
    m_theEnd = new QTimer();
}

void CrazyBricks::createMap(MapBuilder& builder, int choice){
    if(choice == 0){
       m_factory = new StandardFactory(*m_engine, *builder.getMap());
    } else {
        m_factory = new EasyFactory(*m_engine, *builder.getMap());
    }
    m_painterVisitor = m_factory->createPaintVisitor(this);
    m_factory->createBackground(this);
    builder.buildMap(*m_factory);
    builder.buildBlock(*m_factory, this);
    builder.buildPlatform(*m_factory);
    builder.buildBall(*m_factory);
    m_map = builder.getMap();

    connect(this->getEngine(), SIGNAL(collision(int,int)), this, SLOT(collisionDetected(int,int)));
    connect(this->getEngine(), SIGNAL(newPosition(int,float,float)), this, SLOT(positionChanged(int, float, float)));
    connect(this, SIGNAL(newPosition(int,float,float)), this, SLOT(positionChanged(int, float, float)));
    Platform *bottomPlat = static_cast<Platform*>(m_map->getObject(m_map->getBottomPlatform()));
    Platform *topPlat = static_cast<Platform*>(m_map->getObject(m_map->getTopPlatform()));
    connect(bottomPlat->getBehaviour(), SIGNAL(newPosition(int,float,float)), this, SLOT(positionChanged(int, float, float)));
    connect(topPlat->getBehaviour(), SIGNAL(newPosition(int,float,float)), this, SLOT(positionChanged(int, float, float)));
}

void CrazyBricks::collisionDetected(int idA, int idB){
    MapObject *objA = m_map->getObject(idA);
    MapObject *objB = m_map->getObject(idB);
    //collison objA=ball, objB = platform
    if(m_map->isBall(idA) && (idB == m_map->getBottomPlatform() || idB == m_map->getTopPlatform())){
        objA->onCollision(idB); //set last platform collided id
        objB->onCollision(-1);
        //collison objA=ball, objB = BottomWall
    } else if(m_map->isBall(idA) && (idB == m_map->getBottomWall())){
        objA->onCollision(-1);
        objB->onCollision(-1);
        Ball *ball = static_cast<Ball*>(objA);
        //last platform collided was Bottom one so KILL the ball!
        if(ball->getLastPlatformCollided() == m_map->getBottomPlatform()){
            m_map->removeObject(idA);
            //if player has lifes get new ball
            updateBottomLifes(-1);
            if(m_map->getBottomLifes() > 0){
                m_timerBallBottom = new QTimer();
                connect( m_timerBallBottom, SIGNAL(timeout()), this, SLOT(newBottomBall()) );
                m_timerBallBottom->setSingleShot(true);
                m_timerBallBottom->start(500);
            } else {
                m_map->mapPause();
                connect( m_theEnd, SIGNAL(timeout()), this, SLOT(endGame()));
                m_theEnd->setSingleShot(true);
                m_theEnd->start(1000);
            }
        }
        //collison objA=ball, objB = TopWall
    } else if(m_map->isBall(idA) && (idB == m_map->getTopWall())){
        objA->onCollision(-1);
        objB->onCollision(-1);
        Ball *ball = static_cast<Ball*>(objA);
        //last platform collided was Top one so KILL the ball!
        if(ball->getLastPlatformCollided() == m_map->getTopPlatform()){
            m_map->removeObject(idA);
            //if player has lifes get new ball
            updateTopLifes(-1);
            if(m_map->getTopLifes() > 0){
                m_timerBallTop = new QTimer();
                connect( m_timerBallTop, SIGNAL(timeout()), this, SLOT(newTopBall()));
                m_timerBallTop->setSingleShot(true);
                m_timerBallTop->start(500);
            } else {
                m_map->mapPause();
                connect( m_theEnd, SIGNAL(timeout()), this, SLOT(endGame()));
                m_theEnd->setSingleShot(true);
                m_theEnd->start(1000);
            }
        }
        //collison objA=ball, objB = block
    } else if(m_map->isBall(idA)){
        Ball *ball = static_cast<Ball*>(objA);
        objA->onCollision(-1);
        //set the id of platform that controls the ball, for bonus use
        objB->onCollision(ball->getLastPlatformCollided());
        if(ball->getLastPlatformCollided() == m_map->getBottomPlatform()){
            m_scoreBottomGamer += objB->getPoints();
            emit scoreBottomChanged(m_scoreBottomGamer);
        } else {
            m_scoreTopGamer += objB->getPoints();
            emit scoreTopChanged(m_scoreTopGamer);
        }
        //collison objA=bonus, objB = platform
    } else if(m_map->isBonus(idA) && (idB == m_map->getBottomPlatform() || idB == m_map->getTopPlatform())){
        //set the id of platform that controls the ball
        objA->onCollision(idB);
        objB->onCollision(-1);
        //remove bonus when catched
        m_map->removeObject(idA);
    } else if(m_map->isBonus(idA) && (idB == m_map->getTopWall() | idB == m_map->getBottomWall())){
        objA->onCollision(-1);
        objB->onCollision(-1);
        //remove bonus when catched
        m_map->removeObject(idA);
    }
}

void CrazyBricks::positionChanged(int bodyId, float posX, float posY){
    m_map->getObject(bodyId)->setPos(posX, posY);
    Platform *bottomPlat = static_cast<Platform*>(m_map->getObject(m_map->getBottomPlatform()));
    Platform *topPlat = static_cast<Platform*>(m_map->getObject(m_map->getTopPlatform()));
    //if object is ball, move platforms according to ball coordinates
    if(m_map->isBall(bodyId)) {
        bottomPlat->move(posX, posY, NULL);
        topPlat->move(posX, posY, NULL);
    }
    update();
}

void CrazyBricks::keyPressEvent(QKeyEvent *e){
    //call move for both platforms but only the playercontroled ones use the event, we call it for both just to be consistent
    // and treat both platforms the same way
    Platform *bottomPlat = static_cast<Platform*>(m_map->getObject(m_map->getBottomPlatform()));
    bottomPlat->move(0, 0, e);
    Platform *topPlat = static_cast<Platform*>(m_map->getObject(m_map->getTopPlatform()));
    topPlat->move(0, 0, e);
}

void CrazyBricks::keyReleaseEvent(QKeyEvent *e){
    //call move for both platforms but only the playercontroled ones use the event, we call it for both just to be consistent
    // and treat both platforms the same way
    Platform *bottomPlat = static_cast<Platform*>(m_map->getObject(m_map->getBottomPlatform()));
    bottomPlat->move(0, 0, e);
    Platform *topPlat = static_cast<Platform*>(m_map->getObject(m_map->getTopPlatform()));
    topPlat->move(0, 0, e);
}

void CrazyBricks::paintEvent(QPaintEvent *event){
    QMutableHashIterator<int,MapObject*> obj(*(m_map->getObjects()));
    while (obj.hasNext()) {
        obj.next();
        if(obj.value()->isEnabled()){
            obj.value()->accept(*m_painterVisitor);
        } else {
            obj.remove();
        }
    }
}

Ball* CrazyBricks::newBottomBall(){
    int platHeight = 17; //FIXME: find a way to get platform height for initial ball position
    Ball *bottomBall = static_cast<Ball*>(m_factory->createBall(m_width / 2,  m_heigth - platHeight * 3, BOTTOMBALL));
    bottomBall->setLastPlatformCollided(m_map->getBottomPlatform());
    return bottomBall;
}

Ball* CrazyBricks::newTopBall(){
    int platHeight = 17; //FIXME: find a way to get platform height for inital ball position
    Ball *topBall = static_cast<Ball*>(m_factory->createBall(m_width / 2, platHeight * 3, TOPBALL));
    topBall->setLastPlatformCollided(m_map->getTopPlatform());
    return topBall;
}

PhysicSystem* CrazyBricks::getEngine(){
    return m_engine;
}

void CrazyBricks::initializeLifeCounters(){
    //initialize life counters
    emit lifesTopChanged(m_map->getTopLifes());
    emit lifesBottomChanged(m_map->getBottomLifes());
}

void CrazyBricks::bonusStart(int posX, int posY, bonusType type,int bonusToPlatformId){
    m_factory->createBonus(posX, posY, type, bonusToPlatformId, this);
}

int CrazyBricks::updateTopScore(int score){
    m_scoreTopGamer += score;
    emit scoreTopChanged(m_scoreTopGamer);
    return m_scoreTopGamer;
}

int CrazyBricks::updateBottomScore(int score){
    m_scoreBottomGamer += score;
    emit scoreBottomChanged(m_scoreBottomGamer);
    return m_scoreBottomGamer;
}

int CrazyBricks::getTopPlatform(){
    return m_map->getTopPlatform();
}

int CrazyBricks::getBottomPlatform(){
    return m_map->getBottomPlatform();
}

void CrazyBricks::freezePlatform(int time, int id){
    if(id == m_map->getBottomPlatform()){
        Platform *bottomPlat = static_cast<Platform*>(m_map->getObject(m_map->getBottomPlatform()));
        PBehaviour *pehaviour = new DumbBehaviour(*m_engine, *m_map, id);
        bottomPlat->setBehaviour(pehaviour);
    } else if (id == m_map->getTopPlatform()) {
        Platform *topPlat = static_cast<Platform*>(m_map->getObject(m_map->getBottomPlatform()));
        PBehaviour *pehaviour = new DumbBehaviour(*m_engine, *m_map, id);
        topPlat->setBehaviour(pehaviour);
    }
}

int CrazyBricks::updateBottomLifes(int lifes){
    m_map->setBottomLifes(m_map->getBottomLifes()+lifes);
    emit lifesBottomChanged(m_map->getBottomLifes());
    return m_map->getBottomLifes();
}

int CrazyBricks::updateTopLifes(int lifes){
    m_map->setTopLifes(m_map->getTopLifes()+lifes);
    emit lifesTopChanged(m_map->getTopLifes());
    return m_map->getTopLifes();
}

void CrazyBricks::endGame(){
    //end game if no user has more lifes left
    emit lifesTopChanged(0);
    emit lifesBottomChanged(0);
    emit scoreBottomChanged(0);
    emit scoreTopChanged(0);
    if(m_scoreBottomGamer > m_scoreTopGamer){
        emit endOfGame(QString("BOTTOM user won with ")+QString::number(m_scoreBottomGamer) + " points");
    } else {
        emit endOfGame(QString("TOP user won with ")+QString::number(m_scoreTopGamer) + " points");
    }
}

CrazyBricks::~CrazyBricks(){
    delete m_engine;
    delete m_map;
}
