#include "CollisionManager.hpp"

#include <algorithm>

bool CollisionManager::DetectCollision(ICollisionShape* s1, ICollisionShape* s2) {
  if (s1->GetType() > s2->GetType()) {
    std::swap(s1, s2);
  }
  if (detect_collision_virtual_table_[(int)s1->GetType()][(int)s2->GetType()] != nullptr) {
    return (*detect_collision_virtual_table_[(int)s1->GetType()][(int)s2->GetType()])(s1, s2);
  }
  return false;
}

bool CirclesIntersec(const Vector2& c1, const float r1, const Vector2& c2, const float r2) {
  float rsum_2 = (r1 + r2) * (r1 + r2);
  return DistSquare(c1, c2) <= rsum_2;
}

bool DetectCollisionCC(CollisionCircle* c1, CollisionCircle* c2) {
  float radius_sum = c1->GetR() + c2->GetR();
  return DistSquare(c1->GetCenter(), c2->GetCenter()) <= radius_sum * radius_sum;
}

bool DetectCollisionCW(CollisionCircle* circle, CollisionWall* wall) {
  Vector2 v1 = wall->GetFirstPoint();
  Vector2 v2 = wall->GetSecondPoint();
  Vector2 v3 = v2 - v1;
  Vector2 a = circle->GetCenter() - v1;
  Vector2 b = a.GetProjection(v3);
  if ((b ^ v3) >= 0 && b.GetLength() <= v3.GetLength()) {
    float dist = (a - b).GetLength();
    if (dist <= circle->GetR()) {
      return true;
    }
  }
  return false;
}

bool DetectCollisionWW(CollisionWall* w1, CollisionWall* w2) {
  return false;
}