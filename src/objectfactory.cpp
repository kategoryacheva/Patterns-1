

#include "objectfactory.h"

ObjectFactory::ObjectFactory(PhysicSystem& engine, Map& map){
    m_engine = &engine;
    m_map = &map;
    m_map->setEngine(engine);
}

PhysicSystem* ObjectFactory::getEngine(){
    return this->m_engine;
}
