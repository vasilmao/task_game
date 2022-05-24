#pragma once

#include "ecs/Api.hpp"
#include "Events.hpp"

class PlayerEventHandler {
  public:
    PlayerEventHandler(EntityHandle player, float player_speed) : player_{player}, player_speed_{player_speed} {}
    void RespondLeftArrowDown(const LeftArrowDown&);
    void RespondLeftArrowUp(const LeftArrowUp&);
    void RespondRightArrowDown(const RightArrowDown&);
    void RespondRightArrowUp(const RightArrowUp&);
    void RespondUpArrowDown(const UpArrowDown&);
    void RespondUpArrowUp(const UpArrowUp&);
    void RespondDownArrowDown(const DownArrowDown&);
    void RespondDownArrowUp(const DownArrowUp&);

    void RespondLMBDown(const LeftMouseDown&);
    void RespondLMBUp(const LeftMouseUp&);
  private:
    void ChangePlayerRotation();
    EntityHandle player_;
    float player_speed_;
};