#pragma once

#include "Vector.hpp"

enum CollisionTypes { COLLISION_CIRCLE, COLLISION_WALL };

class ICollisionShape {
 public:
  CollisionTypes GetType() { return collision_type_; }

  virtual ~ICollisionShape() {}

 protected:
  ICollisionShape(CollisionTypes collision_type) : collision_type_(collision_type) {}
  CollisionTypes collision_type_;
};

class CollisionCircle : public ICollisionShape {
 public:
  CollisionCircle(const Vector2& center, float r) : ICollisionShape(COLLISION_CIRCLE), center_{center}, r_{r} {}
  float GetR() { return r_; }
  const Vector2& GetCenter() { return center_; }
  void UpdateCenter(const Vector2& new_center) { center_ = new_center; }

 private:
  Vector2 center_;
  float r_;
};

class CollisionWall : public ICollisionShape {
 public:
  CollisionWall(const Vector2& pos1, const Vector2& pos2) : ICollisionShape(COLLISION_WALL), pos1_{pos1}, pos2_{pos2} {}
  const Vector2& GetFirstPoint() { return pos1_; }
  const Vector2& GetSecondPoint() { return pos2_; }

 private:
  Vector2 pos1_;
  Vector2 pos2_;
};
