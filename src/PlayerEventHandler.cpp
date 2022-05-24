#include "PlayerEventHandler.hpp"
#include "Components.hpp"

void PlayerEventHandler::RespondLeftArrowDown(const LeftArrowDown&) {
    player_.GetComponent<Speed>()->speed += Vector2{-player_speed_, 0};
    ChangePlayerRotation();
}
void PlayerEventHandler::RespondLeftArrowUp(const LeftArrowUp&) {
    player_.GetComponent<Speed>()->speed += Vector2{player_speed_, 0};
    ChangePlayerRotation();
}

void PlayerEventHandler::RespondRightArrowDown(const RightArrowDown&) {
    player_.GetComponent<Speed>()->speed += Vector2{player_speed_, 0};
    ChangePlayerRotation();
}
void PlayerEventHandler::RespondRightArrowUp(const RightArrowUp&) {
    player_.GetComponent<Speed>()->speed += Vector2{-player_speed_, 0};
    ChangePlayerRotation();
}
void PlayerEventHandler::RespondUpArrowDown(const UpArrowDown&) {
    player_.GetComponent<Speed>()->speed += Vector2{0, -player_speed_};
    ChangePlayerRotation();
}
void PlayerEventHandler::RespondUpArrowUp(const UpArrowUp&) {
    player_.GetComponent<Speed>()->speed += Vector2{0, player_speed_};
    ChangePlayerRotation();
    
}
void PlayerEventHandler::RespondDownArrowDown(const DownArrowDown&) {
    player_.GetComponent<Speed>()->speed += Vector2{0, player_speed_};
    ChangePlayerRotation();
}
void PlayerEventHandler::RespondDownArrowUp(const DownArrowUp&) {
    player_.GetComponent<Speed>()->speed += Vector2{0, -player_speed_};
    ChangePlayerRotation();   
}
void PlayerEventHandler::RespondLMBDown(const LeftMouseDown&) {
    
}
void PlayerEventHandler::RespondLMBUp(const LeftMouseUp&) {
    
}

void PlayerEventHandler::ChangePlayerRotation() {
    Vector2 speed = player_.GetComponent<Speed>()->speed;
    speed.SetY(-speed.GetY());
    player_.GetComponent<Transform>()->rotation = Angle(speed, Vector2{0, 1});
}