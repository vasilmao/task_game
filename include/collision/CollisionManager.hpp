#pragma once

#include "collision/CollisionTypes.hpp"

bool CirclesIntersec(const Vector2& c1, const float r1, const Vector2& c2, const float r2);

bool DetectCollisionCC(CollisionCircle* c1, CollisionCircle* c2);

bool DetectCollisionCW(CollisionCircle* circle, CollisionWall* wall);

bool DetectCollisionWW(CollisionWall* w1, CollisionWall* w2);

typedef bool (*func)(ICollisionShape*, ICollisionShape*);

class CollisionManager {
 public:
  bool DetectCollision(ICollisionShape* s1, ICollisionShape* s2);

 private:
  func detect_collision_virtual_table_[3][3] = {
      {reinterpret_cast<func>(DetectCollisionCC), reinterpret_cast<func>(DetectCollisionCW)},
      {0, reinterpret_cast<func>(DetectCollisionWW)},
  };
};
