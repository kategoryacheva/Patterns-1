

#include "testingfactory.h"


TestingFactory::TestingFactory(PhysicSystem& engine, Map& map) : ObjectFactory(engine, map)
{
}

MapObject* TestingFactory::createBlock(float posX, float posY,int width, int height){
    Block* block = new Block(posX, posY, width, height);
    Vector2D posRect(posX, posY);
    Rectangle* rect = new Rectangle(posRect, block->getId(), width, height);
    m_map->setEngine(*m_engine);
    m_map->addObject(block, rect);
    qDebug() << "pos:" << block->getPosX() << block->getPosY() << rect->getPosition().getX() << rect->getPosition().getY();
    return block;
}

MapObject* TestingFactory::createWallBlock(float posX, float posY,int width, int height){
    Block* block = new Block(posX, posY, width, height);
    Vector2D posRect(posX, posY);
    Rectangle* rect = new Rectangle(posRect, block->getId(), width, height);
    m_map->setEngine(*m_engine);
    m_map->addObject(block, rect);
    qDebug() << "posWall:" << block->getPosX() << block->getPosY() << rect->getPosition().getX() << rect->getPosition().getY();
    return block;
}

MapObject* TestingFactory::createBall(float posX, float posY,int radius, float velX, float velY){
    Ball* ball = new Ball(posX, posY, radius);
    Vector2D posBall(posX, posY);
    Circle *pball=new Circle(posBall, ball->getId(), radius);
    Vector2D bVel(velX, velY);
    pball->setVelocity(bVel);
    m_map->setEngine(*m_engine);
    m_map->addObject(ball, pball);
    qDebug() << "pos ball:" << ball->getPosX() << ball->getPosY() << pball->getPosition().getX() << pball->getPosition().getY();
    return ball;
}

MapObject* TestingFactory::createPlatform(float posX, float posY,int width, int height){
    Platform* platf = new Platform(posX, posY, width, height);
    Vector2D posRect(posX, posY);
    Rectangle* rect = new Rectangle(posRect, platf->getId(), width, height);
    m_map->setEngine(*m_engine);
    m_map->addObject(platf, rect);
    qDebug() << "posWall:" << platf->getPosX() << platf->getPosY() << rect->getPosition().getX() << rect->getPosition().getY();
    m_map->setUserPlatform(platf->getId());
    return platf;
}
