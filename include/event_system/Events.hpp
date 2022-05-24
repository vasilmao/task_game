#pragma once

#include "Vector.hpp"

struct LeftArrowDown {};
struct LeftArrowUp {};

struct RightArrowDown {};
struct RightArrowUp {};

struct UpArrowDown {};
struct UpArrowUp {};

struct DownArrowDown {};
struct DownArrowUp {};

struct SpaceDown {};
struct SpaceUp {};

struct LeftMouseDown {};
struct LeftMouseUp {};

struct RightMouseDown {};
struct RightMouseUp {};

struct MouseMoved {
    Vector2 delta;
    Vector2 pos;
};

struct TimeEvent {
    float dt;
};
