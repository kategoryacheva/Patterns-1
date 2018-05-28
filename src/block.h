

#ifndef BLOCK_H
#define BLOCK_H

#include "mapobject.h"
#include "stateblock.h"

class PaintVisitor;

class Block : public MapObject
{
    Q_OBJECT

    friend class StateBlock;
    friend class StateBlockInitial;
    friend class StateBlockCollided;
    friend class StateBlockFinal;

public:
    Block(StateBlock *state);
    Block(int width, int height, StateBlock *state);
    Block(float posX, float posY,int width, int height, StateBlock *state);
    void setPos(float posX, float posY);
    void onCollision(int id);
    int getWidth();
    int getHeight();
    void setBonus(bonusType type);
    void setBallControled(int id);
    void startBonus();
    virtual void accept(PaintVisitor& v);

signals:
    void startBonus(int posX, int posY, bonusType type, int platformId);

private:
    void changeState(StateBlock *newState);

private:
    StateBlock* m_currState;
    int m_height;
    int m_width;
    bonusType m_bonus;
    int m_ballControledId;
};

#endif // BLOCK_H
