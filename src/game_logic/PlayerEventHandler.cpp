#include "game_logic/PlayerEventHandler.hpp"
#include "Components.hpp"
#include <iostream>

void PlayerEventHandler::RespondLeftArrowDown(const LeftArrowDown&) {
    player_direction += Vector2{-1, 0};
    player_.GetComponent<Speed>()->speed = player_direction.GetNormalized() * player_speed_;
    // ChangePlayerRotation();
}
void PlayerEventHandler::RespondLeftArrowUp(const LeftArrowUp&) {
    player_direction += Vector2{1, 0};
    player_.GetComponent<Speed>()->speed = player_direction.GetNormalized() * player_speed_;
    // ChangePlayerRotation();
}

void PlayerEventHandler::RespondRightArrowDown(const RightArrowDown&) {
    player_direction += Vector2{1, 0};
    player_.GetComponent<Speed>()->speed = player_direction.GetNormalized() * player_speed_;
    // ChangePlayerRotation();
}
void PlayerEventHandler::RespondRightArrowUp(const RightArrowUp&) {
    player_direction += Vector2{-1, 0};
    player_.GetComponent<Speed>()->speed = player_direction.GetNormalized() * player_speed_;
    // ChangePlayerRotation();
}
void PlayerEventHandler::RespondUpArrowDown(const UpArrowDown&) {
    player_direction += Vector2{0, -1};
    player_.GetComponent<Speed>()->speed = player_direction.GetNormalized() * player_speed_;
    // ChangePlayerRotation();
}
void PlayerEventHandler::RespondUpArrowUp(const UpArrowUp&) {
    player_direction += Vector2{0, 1};
    player_.GetComponent<Speed>()->speed = player_direction.GetNormalized() * player_speed_;
    // ChangePlayerRotation();
    
}
void PlayerEventHandler::RespondDownArrowDown(const DownArrowDown&) {
    player_direction += Vector2{0, 1};
    player_.GetComponent<Speed>()->speed = player_direction.GetNormalized() * player_speed_;
    // ChangePlayerRotation();
}
void PlayerEventHandler::RespondDownArrowUp(const DownArrowUp&) {
    player_direction += Vector2{0, -1};
    player_.GetComponent<Speed>()->speed = player_direction.GetNormalized() * player_speed_;
    // ChangePlayerRotation();
}

void PlayerEventHandler::RespondMouseMove(const MouseMoved& event) {
    Vector2 direction = event.pos - player_.GetComponent<Transform>()->pos;
    player_.GetComponent<Transform>()->rotation = Angle(Vector2{0, -1}, direction);
}

void PlayerEventHandler::RespondLMBDown(const LeftMouseDown&) {
    currently_shooting = true;
}
void PlayerEventHandler::RespondLMBUp(const LeftMouseUp&) {
    currently_shooting = false;
}

void PlayerEventHandler::RespondTime(const TimeEvent& time) {
    if (currently_shooting) {
        player_.GetComponent<Weapon>()->weapon->TrySpawnBullet(scene_, registry_);
    }
}

// void PlayerEventHandler::ChangePlayerRotation() {
//     Vector2 speed = player_.GetComponent<Speed>()->speed;
//     speed.SetY(-speed.GetY());
//     player_.GetComponent<Transform>()->rotation = Angle(speed, Vector2{0, 1});
// }