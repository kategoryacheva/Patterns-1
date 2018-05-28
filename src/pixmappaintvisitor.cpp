

#include "pixmappaintvisitor.h"

PixmapPaintVisitor::PixmapPaintVisitor(QWidget *widget) :
    m_canvasWidget(widget){
}

void PixmapPaintVisitor::VisitBlock(Block* b, Qt::GlobalColor stateColor){
    QPainter painter(m_canvasWidget);
    QRect rect(b->getPosX() - b->getWidth() / 2 , b->getPosY() - b->getHeight() / 2, b->getWidth(), b->getHeight());
    painter.setPen(Qt::NoPen);
    if(stateColor == Qt::cyan){
        painter.setBrush(QBrush(QPixmap(":/images/brick.png")));
        painter.setOpacity(1);
    } else if(stateColor == Qt::yellow) {
        painter.setBrush(QBrush(QPixmap(":/images/brick.png")));
        painter.setOpacity(0.7);
    } else if(stateColor == Qt::darkGreen){
        painter.setBrush(QBrush(QPixmap(":/images/brick.png")));
        painter.setOpacity(0.4);
    } else if(stateColor == Qt::darkRed){
        painter.setBrush(QBrush(QPixmap(":/images/stone.png")));
    } else {
        painter.setBrush(QBrush(QPixmap(":/images/brick.png")));
    }
    painter.drawRect(rect);
}

void PixmapPaintVisitor::VisitBall(Ball* b, Qt::GlobalColor stateColor){
    QPainter painter(m_canvasWidget);
    painter.setRenderHint(QPainter::Antialiasing);
    //rectangle that defines the ellipse
    QRect rectOuterCircle(b->getPosX() - b->getRadius(), b->getPosY() - b->getRadius(), b->getRadius() * 2, b->getRadius() * 2);
    QRadialGradient radialGradient(b->getPosX(), b->getPosY(), b->getRadius(), 300, 200);
    radialGradient.setColorAt(0.0, Qt::white);
    radialGradient.setColorAt(0.95, stateColor);
    radialGradient.setColorAt(1.0, Qt::black);
    painter.setBrush(QBrush(radialGradient));
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(rectOuterCircle);
}

void PixmapPaintVisitor::VisitPlatform(Platform* p){
    QPainter painter(m_canvasWidget);
    QRect rect(p->getPosX() - p->getWidth() / 2, p->getPosY() - p->getHeight() / 2, p->getWidth(), p->getHeight());
    QLinearGradient linearGradient(p->getPosX() - p->getWidth() / 2, p->getPosY() + p->getHeight() /2, (p->getPosX() + p->getWidth() / 2), p->getPosY() + p->getHeight() /2);
    linearGradient.setColorAt(0.0, Qt::darkYellow);
    linearGradient.setColorAt(0.5, Qt::black);
    linearGradient.setColorAt(1.0, Qt::darkYellow);
    painter.setBrush(QBrush(linearGradient));
    painter.setPen(QPen(Qt::yellow, 1, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin));
    painter.drawRect(rect);
}

void PixmapPaintVisitor::VisitBonus(Bonus* b){
    //TODO: set beautiful paint
    QPainter painter(m_canvasWidget);
    QRect rectOuterCircle(b->getPosX() - b->getRadius(), b->getPosY() - b->getRadius(), b->getRadius() * 2, b->getRadius() * 2);
    painter.setBrush(QBrush(Qt::white));
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(rectOuterCircle);
}
