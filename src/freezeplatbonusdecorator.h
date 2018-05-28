

#ifndef FREEZEPLATBONUSDECORATOR_H
#define FREEZEPLATBONUSDECORATOR_H

#include "bonusdecorator.h"

class Bonus;

class FreezePlatBonusDecorator : public BonusDecorator
{
public:
    FreezePlatBonusDecorator(Bonus*, int time);
    virtual void onCollision(int id);

private:
    void freezePlatform(int id);

private:
    int m_timeTofreeze;
};

#endif // FREEZEPLATBONUSDECORATOR_H
