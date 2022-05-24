#include "Weapons.hpp"
#include "ecs/Api.hpp"
#include "Components.hpp"
#include "BulletDrawer.hpp"
#include <iostream>

const int DefaultWeapon::damage_;

void DefaultWeapon::TrySpawnBullet(Scene& scene, EntityRegistry& registry) {
    if (time_from_last_shot_ >= cooldown_) {
        Vector2 spawn_pos = player_.GetComponent<Transform>()->pos;
        float angle = player_.GetComponent<Transform>()->rotation - M_PI_2;
        Vector2 direction = Vector2{std::cos(angle), std::sin(angle)};
        spawn_pos += direction * dynamic_cast<CollisionCircle*>(player_.GetComponent<CollisionShape>()->form)->GetR() * 2;
        EntityHandle bullet = CreateEntity(registry);
        bullet.AddComponent<CollisionShape>(new CollisionCircle{spawn_pos, 5});
        bullet.AddComponent<EntityTypeComponent>(BULLET);
        bullet.AddComponent<Transform>(spawn_pos, angle + M_PI_2f);
        bullet.AddComponent<Speed>(direction * 500);
        bullet.AddComponent<RenderComponent>(std::bind(&DefaultBulletDrawer::Render, DefaultBulletDrawer{bullet}, std::placeholders::_1));
        bullet.AddComponent<Damage>(damage_);
        scene.AddEntity(bullet);
        time_from_last_shot_ = 0;
    }
}

void DefaultWeapon::Cooldown(TimeEvent event) {
    time_from_last_shot_ += event.dt;
}