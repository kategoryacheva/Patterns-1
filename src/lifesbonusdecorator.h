

#ifndef LIFESBONUSDECORATOR_H
#define LIFESBONUSDECORATOR_H

#include "bonusdecorator.h"

class LifesBonusDecorator : public BonusDecorator
{
public:
    LifesBonusDecorator(Bonus *bonus, int nLifes);
    virtual void onCollision(int id);

private:
    void addLifes(int id);

private:
    int m_lifes;
};

#endif // LIFESBONUSDECORATOR_H
