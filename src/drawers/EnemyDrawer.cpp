#include "drawers/EnemyDrawer.hpp"
#include "Components.hpp"
#include "Vector.hpp"
#include <iostream>

void StrangeEnemyDrawer::Render(Renderer& renderer) {
    Vector2 pos = enemy_.GetComponent<Transform>()->pos;
    float rotation = enemy_.GetComponent<Transform>()->rotation;
    Vector2 up_point{pos.GetX(), pos.GetY() - r_};
    Vector2 down_point{pos.GetX(), pos.GetY() + r_};

    Vector2 point1 = up_point.Rotate(pos, rotation);

    down_point = down_point.Rotate(pos, rotation);

    Vector2 point3 = down_point;

    Vector2 point2 = down_point.Rotate(pos, acos(4.0f/5.0f));
    Vector2 point4 = down_point.Rotate(pos, -acos(4.0f/5.0f));

    Color enemy_color = {255, 0, 0, 255};

    renderer.DrawSegment(point1, point2, enemy_color);
    renderer.DrawSegment(point2, point3, enemy_color);
    renderer.DrawSegment(point3, point4, enemy_color);
    renderer.DrawSegment(point4, point1, enemy_color);

}