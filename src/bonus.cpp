

#include "bonus.h"
#include "crazybricks.h"

Bonus::Bonus():
    MapObject(), BonusComponent(){}

Bonus::Bonus(float posX, float posY, int radius, int platformId, int points, CrazyBricks* game) :
    MapObject(posX, posY), m_bonusToPlatformId(platformId), m_game(game), BonusComponent(), m_radius(radius), m_points(points){
}

int Bonus::getRadius(){
    return m_radius;
}

CrazyBricks* Bonus::getGame(){
    return m_game;
}

int Bonus::getPlatformId(){
    return m_bonusToPlatformId;
}

void Bonus::setPos(float posX, float posY) {
    m_posX = posX;
    m_posY = posY;
}

void Bonus::onCollision(int id){
    if(id == m_game->getTopPlatform()){
        m_game->updateTopScore(m_points);
    } else if (id == m_game->getBottomPlatform()) {
        m_game->updateBottomScore(m_points);
    }
}

void Bonus::accept(PaintVisitor& v){
    v.VisitBonus(this);
}
