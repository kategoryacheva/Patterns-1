

#include "lifesbonusdecorator.h"
#include "crazybricks.h"

LifesBonusDecorator::LifesBonusDecorator(Bonus *bonus, int lifes) :
    BonusDecorator(bonus), m_lifes(lifes){
}

void LifesBonusDecorator::onCollision(int id){
    BonusDecorator::onCollision(id);
    addLifes(id);
}

void LifesBonusDecorator::addLifes(int id){
    if(id == getGame()->getTopPlatform()){
        getGame()->updateTopLifes(m_lifes);
    } else if (id == getGame()->getBottomPlatform()) {
        getGame()->updateBottomLifes(m_lifes);
    }
}
