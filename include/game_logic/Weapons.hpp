#pragma once
#include "Events.hpp"
#include "Scene.hpp"

class IWeapon {
 public:
  virtual void Cooldown(TimeEvent event) = 0;
  virtual void TrySpawnBullet(Scene& scene, EntityRegistry& registry) = 0;
  virtual ~IWeapon() {}
};

class DefaultWeapon : public IWeapon {
 public:
  DefaultWeapon(EntityHandle player) : player_{player} {}
  void Cooldown(TimeEvent event) override;
  void TrySpawnBullet(Scene& scene, EntityRegistry& registry) override;

 private:
  static const int damage_ = 7;
  static constexpr float cooldown_ = 0.1;
  float time_from_last_shot_ = 0;
  EntityHandle player_;
};