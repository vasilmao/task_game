#include "ObjectSpawn.hpp"
#include <random>
#include "Components.hpp"
#include "drawers/Drawers.hpp"

EntityHandle CreatePlayer(EntityRegistry& registry, const Vector2& pos, float r) {
  EntityHandle player = CreateEntity(registry);
  player.AddComponent<Health>(100, 100);
  player.AddComponent<RenderComponent>(
      std::bind(&PlayerDrawer::Render, PlayerDrawer{player, r}, std::placeholders::_1));
  player.AddComponent<Transform>(pos, 0.0f);
  player.AddComponent<CollisionShape>(new CollisionCircle{pos, r});
  player.AddComponent<Speed>(Vector2{0, 0});
  player.AddComponent<EntityTypeComponent>(PLAYER);
  return player;
}

EntityHandle CreateStrangeEnemy(EntityRegistry& registry, const Vector2& pos, float r, const Vector2& speed) {
  EntityHandle enemy = CreateEntity(registry);
  enemy.AddComponent<Health>(100, 100);
  enemy.AddComponent<RenderComponent>(
      std::bind(&StrangeEnemyDrawer::Render, StrangeEnemyDrawer{enemy, r}, std::placeholders::_1));
  enemy.AddComponent<Transform>(Vector2{300, 300}, 0.0f);
  enemy.AddComponent<CollisionShape>(new CollisionCircle{Vector2{300, 300}, r});
  enemy.AddComponent<Speed>(speed);
  enemy.AddComponent<EntityTypeComponent>(ENEMY);
  enemy.AddComponent<RotationSpeed>(1.5f);
  return enemy;
}

void EnemySpawner::TrySpawn(const TimeEvent& event) {
    time_from_last_spawn += event.dt;
    if (time_from_last_spawn > spawn_delay_) {
        time_from_last_spawn -= spawn_delay_;
        float enemy_r = 20.0f;
        float min = enemy_r + 20.0f;
        float max_x = field_size_.GetX() - 1 - min;
        float max_y = field_size_.GetY() - 1 - min;
        float random_x = enemy_r + 10.0f + (rand() % static_cast<int>(max_x - min + 1));
        float random_y = enemy_r + 10.0f + (rand() % static_cast<int>(max_y - min + 1));

        float random_speed_x = 50 + (rand() % 200);
        float random_speed_y = 50 + (rand() % 200);
        scene_.AddEntity(CreateStrangeEnemy(registry_, Vector2{random_x, random_y}, enemy_r, Vector2{random_speed_x, random_speed_y}));
    }
}