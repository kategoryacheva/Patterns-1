

#include "simplepaintvisitor.h"

static const int outerRingTickness = 3;

SimplePaintVisitor::SimplePaintVisitor(QWidget *widget) :
    m_canvasWidget(widget){}

void SimplePaintVisitor::VisitBlock(Block* b, Qt::GlobalColor stateColor){
        QPainter painter(m_canvasWidget);
        QRect rect(b->getPosX() - b->getWidth() / 2 , b->getPosY() - b->getHeight() / 2, b->getWidth(), b->getHeight());
        painter.setBrush(QBrush(stateColor));
        painter.setPen(Qt::NoPen);
        painter.drawRect(rect);
}

void SimplePaintVisitor::VisitBall(Ball* b, Qt::GlobalColor stateColor){
    QPainter painter(m_canvasWidget);
    painter.setRenderHint(QPainter::Antialiasing);
    //rectangle that defines the ellipse
    QRect rectOuterCircle(b->getPosX() - b->getRadius(), b->getPosY() - b->getRadius(), b->getRadius() * 2, b->getRadius() * 2);
    painter.setBrush(QBrush(stateColor));
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(rectOuterCircle);

    QRect rect((b->getPosX() + outerRingTickness) - b->getRadius(), (b->getPosY() + outerRingTickness) - b->getRadius(), (b->getRadius() - outerRingTickness) * 2, (b->getRadius() - outerRingTickness) * 2);
    painter.setBrush(QBrush(Qt::black));
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(rect);
}

void SimplePaintVisitor::VisitPlatform(Platform* p){
    QPainter painter(m_canvasWidget);
    QRect rect(p->getPosX() - p->getWidth() / 2, p->getPosY() - p->getHeight() / 2, p->getWidth(), p->getHeight());
    painter.setBrush(QBrush(Qt::darkBlue));
    painter.setPen(Qt::NoPen);
    painter.drawRect(rect);
}

void SimplePaintVisitor::VisitBonus(Bonus* b){
    QPainter painter(m_canvasWidget);
    QRect rectOuterCircle(b->getPosX() - b->getRadius(), b->getPosY() - b->getRadius(), b->getRadius() * 2, b->getRadius() * 2);
    painter.setBrush(QBrush(Qt::white));
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(rectOuterCircle);
}
