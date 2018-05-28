

#ifndef VISITORCOLLISION_H
#define VISITORCOLLISION_H

class VisitorCollision
{
public:
    virtual void VisitElementA(ElementA*);
    virtual void VisitElementB(ElementB*);
protected
    VisitorCollision();
};

#endif // VISITORCOLLISION_H
