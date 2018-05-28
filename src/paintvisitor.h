

#ifndef PAINTVISITOR_H
#define PAINTVISITOR_H

#include "ball.h"
#include "platform.h"
#include "block.h"
#include "bonus.h"

class PaintVisitor
{
public:
   virtual void VisitBlock(Block*, Qt::GlobalColor stateColor);
   virtual void VisitBall(Ball*, Qt::GlobalColor stateColor);
   virtual void VisitPlatform(Platform*);
   virtual void VisitBonus(Bonus*);

protected:
    PaintVisitor();
};

#endif // PAINTVISITOR_H
