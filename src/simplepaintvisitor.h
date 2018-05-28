

#ifndef SIMPLEPAINTVISITOR_H
#define SIMPLEPAINTVISITOR_H

#include "paintvisitor.h"

class SimplePaintVisitor : public PaintVisitor
{
public:
    SimplePaintVisitor(QWidget *widget);
    virtual void VisitBlock(Block*, Qt::GlobalColor stateColor);
    virtual void VisitBall(Ball*,Qt::GlobalColor stateColor);
    virtual void VisitPlatform(Platform*);
    virtual void VisitBonus(Bonus*);

private:
    QWidget* m_canvasWidget;
};

#endif // SIMPLEPAINTVISITOR_H
