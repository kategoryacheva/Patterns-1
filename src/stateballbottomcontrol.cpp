

#include "stateballbottomcontrol.h"
#include "ball.h"

//static const int outerRingTickness = 3;

StateBallBottomControl* StateBallBottomControl::m_stateInstance = NULL;

StateBallBottomControl::StateBallBottomControl(){}

StateBall* StateBallBottomControl::Instance(){
   if (!m_stateInstance)   // Only allow one instance of class to be generated.
      m_stateInstance = new StateBallBottomControl;
   return m_stateInstance;
}

void StateBallBottomControl::accept(Ball *b,PaintVisitor& v){
    v.VisitBall(b, Qt::green);
}

void StateBallBottomControl::onCollision(Ball *b){
    changeState(b, StateBallTopControl::Instance());
}

