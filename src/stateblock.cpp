

#include "stateblock.h"
#include "block.h"
#include "paintvisitor.h"

StateBlock::StateBlock(){}

void StateBlock::changeState(Block* b, StateBlock* s){
    b->changeState(s);
}

