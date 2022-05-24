#pragma once

#include "ecs/Api.hpp"
#include "Events.hpp"
#include "Scene.hpp"

class PlayerEventHandler {
  public:
    PlayerEventHandler(EntityHandle player, Scene& scene, EntityRegistry& registry, float player_speed) : player_{player}, scene_{scene}, registry_{registry}, player_speed_{player_speed} {}
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

    void RespondMouseMove(const MouseMoved&);

    void RespondTime(const TimeEvent&);
  private:
    // void ChangePlayerRotation();
    Vector2 player_direction{0, 0};
    bool currently_shooting = false;
    float time_from_last_shot = INFINITY;
    EntityHandle player_;
    Scene& scene_;
    EntityRegistry& registry_;
    float player_speed_;
};