#include "drawers/EnemyDrawer.hpp"

#include "Components.hpp"
#include "Vector.hpp"

void StrangeEnemyDrawer::Render(Renderer& renderer) {
  Vector2 pos = enemy_.GetComponent<Transform>()->pos;
  float rotation = enemy_.GetComponent<Transform>()->rotation;
  Vector2 up_point{pos.GetX(), pos.GetY() - r_};
  Vector2 down_point{pos.GetX(), pos.GetY() + r_};
  Vector2 left_point{pos.GetX() - r_, pos.GetY()};
  Vector2 right_point{pos.GetX() + r_, pos.GetY()};

  up_point = up_point.Rotate(pos, rotation);
  down_point = down_point.Rotate(pos, rotation);
  left_point = left_point.Rotate(pos, rotation);
  right_point = right_point.Rotate(pos, rotation);

  Color enemy_color = {255, 0, 255, 255};

  renderer.DrawSegment(up_point, right_point, enemy_color);
  renderer.DrawSegment(right_point, down_point, enemy_color);
  renderer.DrawSegment(down_point, left_point, enemy_color);
  renderer.DrawSegment(left_point, up_point, enemy_color);
}