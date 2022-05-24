#include "drawers/PlayerDrawer.hpp"

#include "Components.hpp"
#include "Vector.hpp"

void PlayerDrawer::Render(Renderer& renderer) {
  Vector2 pos = player_.GetComponent<Transform>()->pos;
  float rotation = player_.GetComponent<Transform>()->rotation;
  Vector2 up_point{pos.GetX(), pos.GetY() - r_};
  Vector2 down_point{pos.GetX(), pos.GetY() + r_};

  Vector2 point1 = up_point.Rotate(pos, rotation);

  down_point = down_point.Rotate(pos, rotation);

  Vector2 point3 = pos;

  Vector2 point2 = down_point.Rotate(pos, acos(4.0f / 5.0f));
  Vector2 point4 = down_point.Rotate(pos, -acos(4.0f / 5.0f));

  Color player_color = {0, 255, 0, 255};

  renderer.DrawSegment(point1, point2, player_color);
  renderer.DrawSegment(point2, point3, player_color);
  renderer.DrawSegment(point3, point4, player_color);
  renderer.DrawSegment(point4, point1, player_color);
}