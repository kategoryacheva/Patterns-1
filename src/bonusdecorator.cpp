

#include "bonusdecorator.h"
#include "crazybricks.h"

BonusDecorator::BonusDecorator(Bonus *bonus): Bonus(),
    m_component(bonus){
}

void BonusDecorator::onCollision(int id){
  m_component->onCollision(id);
}

CrazyBricks* BonusDecorator::getGame(){
    m_component->getGame();
}

int BonusDecorator::getPlatformId(){
    m_component->getPlatformId();
}

void BonusDecorator::accept(PaintVisitor& v){
    v.VisitBonus(m_component);
}

void BonusDecorator::setPos(float posX, float posY) {
    m_component->setPos(posX, posY);
}

