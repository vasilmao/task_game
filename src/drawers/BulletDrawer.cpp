#include "BulletDrawer.hpp"

#include "Components.hpp"

void DefaultBulletDrawer::Render(Renderer& renderer) {
  Vector2 pos = bullet_.GetComponent<Transform>()->pos;
  float rotation = bullet_.GetComponent<Transform>()->rotation;
  float r = dynamic_cast<CollisionCircle*>(bullet_.GetComponent<CollisionShape>()->form)->GetR();
  Vector2 up_point{pos.GetX(), pos.GetY() - r};
  Vector2 down_point{pos.GetX(), pos.GetY() + r};

  Vector2 point1 = up_point.Rotate(pos, rotation);

  down_point = down_point.Rotate(pos, rotation);

  Vector2 point3 = down_point;

  Vector2 point2 = down_point.Rotate(pos, acos(4.5f / 5.0f));
  Vector2 point4 = down_point.Rotate(pos, -acos(4.5f / 5.0f));

  Color bullet_color = {255, 0, 0, 255};

  renderer.DrawSegment(point1, point2, bullet_color);
  renderer.DrawSegment(point2, point3, bullet_color);
  renderer.DrawSegment(point3, point4, bullet_color);
  renderer.DrawSegment(point4, point1, bullet_color);
}