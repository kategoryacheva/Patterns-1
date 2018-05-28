

#include "stateblockcollided.h"
#include "block.h"

static int const points = 50;

StateBlockCollided* StateBlockCollided::m_stateInstance = NULL;

StateBlockCollided::StateBlockCollided(){}

StateBlock* StateBlockCollided::Instance(){
   if (!m_stateInstance)   // Only allow one instance of class to be generated.
      m_stateInstance = new StateBlockCollided;
   return m_stateInstance;
}

void StateBlockCollided::accept(Block *b,PaintVisitor& v){
    v.VisitBlock(b, Qt::yellow);
}

void StateBlockCollided::onCollision(Block *b){
    b->setPoints(points);
    changeState(b, StateBlockFinal::Instance());
}

