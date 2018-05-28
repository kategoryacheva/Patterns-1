

#include "stateblockinitial.h"
#include "block.h"

static int const points = 20;

StateBlockInitial* StateBlockInitial::m_stateInstance = NULL;

StateBlockInitial::StateBlockInitial(){}

StateBlock* StateBlockInitial::Instance(){
   if (!m_stateInstance)   // Only allow one instance of class to be generated.
      m_stateInstance = new StateBlockInitial;
   return m_stateInstance;
}

void StateBlockInitial::accept(Block *b,PaintVisitor& v){
    v.VisitBlock(b, Qt::cyan);
}

void StateBlockInitial::onCollision(Block *b){
    b->setPoints(points);
    changeState(b, StateBlockCollided::Instance());
}


