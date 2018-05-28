

#include "stateblockfinal.h"
#include "block.h"

static int const points = 100;

StateBlockFinal* StateBlockFinal::m_stateInstance = NULL;

StateBlockFinal::StateBlockFinal(){}

StateBlock* StateBlockFinal::Instance(){
   if (!m_stateInstance)   // Only allow one instance of class to be generated.
      m_stateInstance = new StateBlockFinal;
   return m_stateInstance;
}

void StateBlockFinal::accept(Block *b,PaintVisitor& v){
    v.VisitBlock(b, Qt::darkGreen);
}

void StateBlockFinal::onCollision(Block *b){
    b->startBonus();
    b->setPoints(points);
    b->emitObjectRemoval(b->getId());
}


