#include "game_logic/PlayerEventHandler.hpp"

#include "Components.hpp"

void PlayerEventHandler::RespondLeftArrowDown(const LeftArrowDown&) {
  player_direction_ += Vector2{-1, 0};
  ChangeSpeedDirection();
}
void PlayerEventHandler::RespondLeftArrowUp(const LeftArrowUp&) {
  player_direction_ += Vector2{1, 0};
  ChangeSpeedDirection();
}

void PlayerEventHandler::RespondRightArrowDown(const RightArrowDown&) {
  player_direction_ += Vector2{1, 0};
  ChangeSpeedDirection();
}
void PlayerEventHandler::RespondRightArrowUp(const RightArrowUp&) {
  player_direction_ += Vector2{-1, 0};
  ChangeSpeedDirection();
}
void PlayerEventHandler::RespondUpArrowDown(const UpArrowDown&) {
  player_direction_ += Vector2{0, -1};
  ChangeSpeedDirection();
}
void PlayerEventHandler::RespondUpArrowUp(const UpArrowUp&) {
  player_direction_ += Vector2{0, 1};
  ChangeSpeedDirection();
}
void PlayerEventHandler::RespondDownArrowDown(const DownArrowDown&) {
  player_direction_ += Vector2{0, 1};
  ChangeSpeedDirection();
}
void PlayerEventHandler::RespondDownArrowUp(const DownArrowUp&) {
  player_direction_ += Vector2{0, -1};
  ChangeSpeedDirection();
}

void PlayerEventHandler::RespondMouseMove(const MouseMoved& event) {
  Vector2 direction = event.pos - player_.GetComponent<Transform>()->pos;
  player_.GetComponent<Transform>()->rotation = Angle(Vector2{0, -1}, direction);
}

void PlayerEventHandler::RespondLMBDown(const LeftMouseDown&) { currently_shooting_ = true; }
void PlayerEventHandler::RespondLMBUp(const LeftMouseUp&) { currently_shooting_ = false; }

void PlayerEventHandler::RespondTime(const TimeEvent& time) {
  if (currently_shooting_) {
    player_.GetComponent<Weapon>()->weapon->TrySpawnBullet(scene_, registry_);
  }
}

void PlayerEventHandler::ChangeSpeedDirection() {
  player_.GetComponent<Speed>()->speed = player_direction_.GetNormalized() * player_speed_;
}