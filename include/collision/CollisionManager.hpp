#pragma once

#include "collision/CollisionTypes.hpp"

bool CirclesIntersec(const Vector2& c1, const float r1, const Vector2& c2, const float r2);

bool detectCollisionCC(CollisionCircle* c1, CollisionCircle* c2, const float dt);

bool detectCollisionCW(CollisionCircle* circle, CollisionWall* wall, const float dt);

bool detectCollisionWW(CollisionWall* w1, CollisionWall* w2, const float dt);

typedef bool (*func)(ICollisionShape*, ICollisionShape*);

class CollisionManager {
  public:    
    bool DetectCollision(ICollisionShape* s1, ICollisionShape* s2);
  private:
    func detect_collision_virtual_table_[3][3] = {
        {reinterpret_cast<func>(detectCollisionCC), reinterpret_cast<func>(detectCollisionCW)},
        {                                        0, reinterpret_cast<func>(detectCollisionWW)},
    };

};
