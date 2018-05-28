

#include "standardfactory.h"
#include "stateblockinitial.h"
#include "stateblockcollided.h"
#include "stateblockfinal.h"
#include "stateblockwall.h"
#include "stateballtopcontrol.h"
#include "stateballbottomcontrol.h"
#include "simplepaintvisitor.h"
#include "pixmappaintvisitor.h"
#include "lifesbonusdecorator.h"
#include "freezeplatbonusdecorator.h"

static const int ballVelX = 3.0;
static const int ballVelY = 2.0;
static const int bonusVelYup = -1.0;
static const int bonusVelYdown = 1.0;
static const int ballRadius = 13;
static const int pointsBonus = 200;
static const int lifesBonus = 1;
static const int bonusRadius = 9;

StandardFactory::StandardFactory(PhysicSystem& engine, Map& map) :
    ObjectFactory(engine, map){}

MapObject* StandardFactory::createBlock(float posX, float posY,int width, int height){
    Block* block = new Block(posX, posY, width, height, StateBlockInitial::Instance());
    Vector2D posRect(posX, posY);
    Rectangle* rect = new Rectangle(posRect, block->getId(), width, height);
    m_map->addObject(block, rect);
    return block;
}

MapObject* StandardFactory::createWallBlock(float posX, float posY,int width, int height){
    Block* block = new Block(posX, posY, width, height, StateBlockWall::Instance());
    Vector2D posRect(posX, posY);
    Rectangle* rect = new Rectangle(posRect, block->getId(), width, height);
    m_map->addObject(block, rect);
    return block;
}

MapObject* StandardFactory::createBall(float posX, float posY, ballInit location){
    Ball* ball;
    if(location == TOPBALL) {
        ball = new Ball(posX, posY, ballRadius, StateBallTopControl::Instance());
    } else {
        ball = new Ball(posX, posY, ballRadius, StateBallBottomControl::Instance());
    }
    Vector2D posBall(posX, posY);
    Circle* pball=new Circle(posBall, ball->getId(), ballRadius);
    //if ball in top half of game it will go down
    Vector2D bVel(0, 0);
    if(location == TOPBALL) {
        bVel.setX(ballVelX);
        bVel.setY(ballVelY);
    } else {
        bVel.setX(ballVelX);
        bVel.setY(-ballVelY);
    }
    pball->setVelocity(bVel);
    m_map->addObject(ball, pball);
    m_map->addBallToList(ball->getId());
    return ball;
}

MapObject* StandardFactory::createPlatform(float posX, float posY,int width, int height, int limitXLeft, int limitXRight){
    Platform* platf = new Platform(posX, posY, width, height);
    Vector2D posRect(posX, posY);
    Rectangle* rect = new Rectangle(posRect, platf->getId(), width, height);
    rect->setXLimits(limitXLeft, limitXRight);
    m_map->addObject(platf, rect);
    return platf;
}

MapObject* StandardFactory::createBonus(float posX, float posY, bonusType type, int bonusToPlatformId, CrazyBricks* game){
//    Bonus* bonus = new FreezePlatBonusDecorator(new LifesBonusDecorator(new Bonus(posX, posY, bonusRadius, bonusToPlatformId, pointsBonus, game), lifesBonus), 5);
    Bonus* bonus = new LifesBonusDecorator(new Bonus(posX, posY, bonusRadius, bonusToPlatformId, pointsBonus, game), lifesBonus);
    Vector2D posBonus(posX, posY);
    Circle* cbonus=new Circle(posBonus, bonus->getId(), bonusRadius);
    Vector2D bVel(0, 0);
    if(bonusToPlatformId == game->getBottomPlatform()) {
        bVel.setY(1.0);
    } else {
        bVel.setY(-1.0);
    }
    cbonus->setVelocity(bVel);
    m_map->addObject(bonus, cbonus);
    m_map->addBonusToList(bonus->getId());
    return bonus;
}

PaintVisitor* StandardFactory::createPaintVisitor(QWidget *widget){
    return new PixmapPaintVisitor(widget);
}

void StandardFactory::createBackground(QWidget *widget){
    QPalette palette;
    palette.setBrush(widget->backgroundRole(), QBrush(QPixmap(":/images/space.png")));
    widget->setPalette(palette);
}
