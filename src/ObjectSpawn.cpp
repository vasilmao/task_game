#include "ObjectSpawn.hpp"
#include "Components.hpp"
#include "drawers/Drawers.hpp"


EntityHandle CreatePlayer(EntityRegistry& registry, const Vector2& pos, float r) {
    EntityHandle player = CreateEntity(registry);
    player.AddComponent<Health>(100, 100);
    player.AddComponent<RenderComponent>(std::bind(&PlayerDrawer::Render, PlayerDrawer{player, r}, std::placeholders::_1));
    player.AddComponent<Transform>(pos, 0.0f);
    player.AddComponent<CollisionShape>(new CollisionCircle{pos, r});
    player.AddComponent<Speed>(Vector2{0, 0});
    player.AddComponent<EntityTypeComponent>(PLAYER);
    return player;
}

EntityHandle CreateStrangeEnemy(EntityRegistry& registry, const Vector2& pos, float r, const Vector2& speed) {
    EntityHandle enemy = CreateEntity(registry);
    enemy.AddComponent<Health>(100, 100);
    enemy.AddComponent<RenderComponent>(std::bind(&StrangeEnemyDrawer::Render, StrangeEnemyDrawer{enemy, r}, std::placeholders::_1));
    enemy.AddComponent<Transform>(Vector2{300, 300}, 0.0f);
    enemy.AddComponent<CollisionShape>(new CollisionCircle{Vector2{300, 300}, r});
    enemy.AddComponent<Speed>(speed);
    enemy.AddComponent<EntityTypeComponent>(ENEMY);
    return enemy;
}