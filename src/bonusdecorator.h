

#ifndef BONUSDECORATOR_H
#define BONUSDECORATOR_H

#include "bonus.h"

class BonusDecorator: public Bonus, public BonusComponent
{
public:
   BonusDecorator(Bonus*);
   void setPos(float posX, float posY);
   void accept(PaintVisitor& v);
   virtual void onCollision(int id);

protected:
   CrazyBricks* getGame();
   int getPlatformId();

private:
    Bonus* m_component;
};

#endif // BONUSDECORATOR_H
