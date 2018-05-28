

#include "pbehaviour.h"

PBehaviour::PBehaviour(PhysicSystem& engine, Map& map, int platformId){
    m_engine = &engine;
    m_platformId = platformId;
    m_currentMap = &map;
}

