

#include "freezeplatbonusdecorator.h"
#include "crazybricks.h"

FreezePlatBonusDecorator::FreezePlatBonusDecorator(Bonus *bonus, int time) :
    BonusDecorator(bonus), m_timeTofreeze(time){
}

void FreezePlatBonusDecorator::onCollision(int id){
    if(id != -1){
        BonusDecorator::onCollision(id);
        freezePlatform(id);
    }
}

void FreezePlatBonusDecorator::freezePlatform(int id){
    //TODO: freze platform
    getGame()->freezePlatform(m_timeTofreeze, id);
}
