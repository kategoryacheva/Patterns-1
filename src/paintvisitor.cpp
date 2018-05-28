

#include "paintvisitor.h"

PaintVisitor::PaintVisitor(){}

void PaintVisitor::VisitBlock(Block*, Qt::GlobalColor stateColor){}

void PaintVisitor::VisitBall(Ball*, Qt::GlobalColor stateColor){}

void PaintVisitor::VisitPlatform(Platform*){}

void PaintVisitor::VisitBonus(Bonus*){}
