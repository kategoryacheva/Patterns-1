

#include "block.h"
#include "paintvisitor.h"

Block::Block(StateBlock *state) :
    MapObject(){
    m_currState = state;
}

Block::Block(int width, int height, StateBlock *state):
    MapObject(){
    m_currState = state;
    m_width = width;
    m_height = height;
}

Block::Block(float posX, float posY,int width, int height, StateBlock *state):
    MapObject(posX, posY) {
    m_currState = state;
    m_width = width;
    m_height = height;
}

void Block::setPos(float posX, float posY) {
    m_posX = posX;
    m_posY = posY;
}

void Block::onCollision(int id){
    if(id != -1){
        m_ballControledId = id;
    }
    m_currState->onCollision(this);
}

void Block::changeState(StateBlock *newState){
    m_currState = newState;
}

int Block::getWidth(){
    return m_width;
}

int Block::getHeight(){
    return m_height;
}

void Block::startBonus(){
    emit startBonus(m_posX, m_posY, m_bonus, m_ballControledId);
}

void Block::setBonus(bonusType type){
    m_bonus = BONUS1;
}

void Block::setBallControled(int id){
    m_ballControledId = id;
}

void Block::accept(PaintVisitor& v){
    m_currState->accept(this, v);
}




