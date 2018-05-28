

#include "stateblockwall.h"
#include "block.h"

static int const points = 0;

StateBlockWall* StateBlockWall::m_stateInstance = NULL;

StateBlockWall::StateBlockWall(){}

StateBlock* StateBlockWall::Instance(){
   if (!m_stateInstance)   // Only allow one instance of class to be generated.
      m_stateInstance = new StateBlockWall;
   return m_stateInstance;
}

void StateBlockWall::accept(Block *b,PaintVisitor& v){
    v.VisitBlock(b, Qt::darkRed);
}

void StateBlockWall::onCollision(Block *b){
    b->setPoints(points);
}

