

#ifndef PIXMAPPAINTVISITOR_H
#define PIXMAPPAINTVISITOR_H

#include <QLabel>

#include "paintvisitor.h"

class PixmapPaintVisitor : public PaintVisitor
{
public:
    PixmapPaintVisitor(QWidget *widget);
    virtual void VisitBlock(Block*, Qt::GlobalColor stateColor);
    virtual void VisitBall(Ball*, Qt::GlobalColor stateColor);
    virtual void VisitPlatform(Platform*);
    virtual void VisitBonus(Bonus*);

private:
    QWidget* m_canvasWidget;
    QPixmap pixmap;
};

#endif // PIXMAPPAINTVISITOR_H
