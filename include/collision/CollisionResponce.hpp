#pragma once

#include "EntityTypes.hpp"
#include "ecs/Api.hpp"

void ResponceCollisionPW(EntityHandle& e1, EntityHandle& e2);

void ResponceCollisionPE(EntityHandle& e1, EntityHandle& e2);

void ResponceCollisionPB(EntityHandle& e1, EntityHandle& e2);

void ResponceCollisionWE(EntityHandle& e1, EntityHandle& e2);

void ResponceCollisionWB(EntityHandle& e1, EntityHandle& e2);

void ResponceCollisionEB(EntityHandle& e1, EntityHandle& e2);

typedef void (*responce_func)(EntityHandle&, EntityHandle&);

class CollisionResponcer {
  public:    
    void ResponceCollision(EntityHandle& e1, EntityHandle& e2);
  private:
    responce_func responce_collision_virtual_table_[ENTITY_TYPE_CNT][ENTITY_TYPE_CNT] = {
        {0, reinterpret_cast<responce_func>(ResponceCollisionPW), reinterpret_cast<responce_func>(ResponceCollisionPE), reinterpret_cast<responce_func>(ResponceCollisionPB)},
        {0,                                                    0, reinterpret_cast<responce_func>(ResponceCollisionWE), reinterpret_cast<responce_func>(ResponceCollisionWB)},
        {0,                                                    0,                                                    0, reinterpret_cast<responce_func>(ResponceCollisionEB)},
        {0, 0, 0, 0}
    };
};
