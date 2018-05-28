

#ifndef BONUS_H
#define BONUS_H

#include "mapobject.h"
#include "bonuscomponent.h"

class CrazyBricks;

class Bonus: public MapObject, public BonusComponent
{
public:
    Bonus();
    Bonus(float posX, float posY, int radius, int platformId, int points, CrazyBricks* game);
    int getRadius();
    virtual void onCollision(int id);
    void accept(PaintVisitor& v);
    void setPos(float posX, float posY);
    CrazyBricks* getGame();
    int getPlatformId();

private:
    int m_addedPoints;
    int m_bonusToPlatformId;
    CrazyBricks* m_game;
    int m_points;
    int m_radius;
};

#endif // BONUS_H
