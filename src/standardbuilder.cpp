

#include "standardbuilder.h"
#include "playercontroledbehaviour.h"
#include "dumbbehaviour.h"
#include "smartbehaviour.h"

static const int sideWallTickness = 40;
static const int ballRadius = 13;
static const int brickWidth = 60;
static const int brickHeight = 20;
static const int platWidth = 60;
static const int platHeight = 17;
static const int spaceBlock = 4;
static const int nRow = 2;
static const int lifes = 3;

StandardBuilder::StandardBuilder(int width, int height):m_currentMap(NULL){
    m_width = width;
    m_height = height;
    if (m_currentMap == NULL){
        m_currentMap = new Map;
    }
}

void StandardBuilder::buildMap(ObjectFactory& factory){
    //left wall
    factory.createWallBlock(0.0, m_height / 2.0, sideWallTickness, m_height);
    //top wall
    MapObject *topWall = factory.createWallBlock(m_width / 2.0, 0.0 - sideWallTickness / 2, m_width, sideWallTickness);
    m_currentMap->setTopWall(topWall->getId());
    //right wall
    factory.createWallBlock(m_width, m_height / 2.0, sideWallTickness, m_height);
    //bottom wall
    MapObject *btmWall = factory.createWallBlock(m_width / 2.0, m_height + sideWallTickness / 2.0, m_width, sideWallTickness);
    m_currentMap->setBottomWall(btmWall->getId());

    //Final free width game zone is = width - sideWallTickness
    m_currentMap->setGameFreeWidth(m_width - sideWallTickness);
    m_currentMap->setWidth(m_width);
    m_currentMap->setBottomLifes(lifes);
    m_currentMap->setTopLifes(lifes);
}

void StandardBuilder::buildBlock(ObjectFactory& factory, QWidget *game){
    int availableWidth = m_width - 2 * (sideWallTickness / 2);
    int nCol = availableWidth / (brickWidth + spaceBlock);

    MapObject *blk;
    int blkY = m_height / 2 - spaceBlock / 2 - (nRow / 2 - 1) * spaceBlock - brickHeight / 2 - (nRow / 2 - 1) * brickHeight;
    for(int i = 0; i < nRow; i++){
        for(int j = 0; j < nCol; j++){
            int blcX = (sideWallTickness / 2) + brickWidth / 2 + j * brickWidth + (j + 1) * spaceBlock;
            if((i % 2 == 0) || (j % 2 == 0)){
                blk = factory.createBlock(blcX, blkY , brickWidth, brickHeight);
                connect(blk, SIGNAL(objectForRemoval(int)), this->getMap(), SLOT(removeObject(int)));
                connect(blk, SIGNAL(startBonus(int, int, bonusType, int)), game, SLOT(bonusStart(int, int, bonusType, int)));}
        }
        blkY += brickHeight + spaceBlock;
    }
}

void StandardBuilder::buildPlatform(ObjectFactory& factory){
    int leftLimit = sideWallTickness / 2 + platWidth / 2;
    int rightLimit = m_width - sideWallTickness / 2 - platWidth / 2;
    //Top Platform: DumbBehaviour SmartBehaviour PlayerControledBehaviour
    Platform *topPlat = static_cast<Platform*>(factory.createPlatform(m_width / 2, platHeight / 2 + 2 , platWidth, platHeight, leftLimit, rightLimit));
    PBehaviour *topBehaviour = new SmartBehaviour(*factory.getEngine(), *(this->getMap()), topPlat->getId());
    topPlat->setBehaviour(topBehaviour);
    m_currentMap->setTopPlatform(topPlat->getId());

    //Bottom Platform: DumbBehaviour SmartBehaviour PlayerControledBehaviour
    Platform *bottomPlat = static_cast<Platform*>(factory.createPlatform(m_width / 2, m_height - platHeight / 2 - 2, platWidth, platHeight, leftLimit, rightLimit));
    PBehaviour *bottomBehaviour = new PlayerControledBehaviour(*factory.getEngine(), *(this->getMap()), bottomPlat->getId());
    bottomPlat->setBehaviour(bottomBehaviour);
    m_currentMap->setBottomPlatform(bottomPlat->getId());
}

void StandardBuilder::buildBall(ObjectFactory& factory){
    Ball *bottomBall = static_cast<Ball*>(factory.createBall(m_width / 2,  m_height - platHeight * 2, BOTTOMBALL));
    Ball *topBall = static_cast<Ball*>(factory.createBall(m_width / 2, platHeight * 2, TOPBALL));
    topBall->setLastPlatformCollided(m_currentMap->getTopPlatform());
    bottomBall->setLastPlatformCollided(m_currentMap->getBottomPlatform());
}

Map* StandardBuilder::getMap(){
    return this->m_currentMap;
}
