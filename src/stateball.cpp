

#include "stateball.h"
#include "ball.h"
#include "paintvisitor.h"

StateBall::StateBall(){}

void StateBall::changeState(Ball* b, StateBall* s){
    b->changeState(s);
}

