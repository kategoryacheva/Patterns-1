

#include "stateballtopcontrol.h"
#include "ball.h"

//static const int outerRingTickness = 3;

StateBallTopControl* StateBallTopControl::m_stateInstance = NULL;

StateBallTopControl::StateBallTopControl(){}

StateBall* StateBallTopControl::Instance(){
   if (!m_stateInstance)   // Only allow one instance of class to be generated.
      m_stateInstance = new StateBallTopControl;
   return m_stateInstance;
}

void StateBallTopControl::accept(Ball *b,PaintVisitor& v){
    v.VisitBall(b, Qt::red);
}

void StateBallTopControl::onCollision(Ball *b){
    changeState(b, StateBallBottomControl::Instance());
}

