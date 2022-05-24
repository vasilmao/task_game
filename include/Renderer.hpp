#pragma once

#include <Engine.h>
#include <stdint.h>

#include "Vector.hpp"

class Renderer {
 public:
  Renderer(uint32_t* buffer, size_t width, size_t height) : width_(width), height_(height), buffer_(buffer){};
  void DrawSegment(Vector2 p1, Vector2 p2, Color color);

 private:
  size_t width_ = 0;
  size_t height_ = 0;
  uint32_t* buffer_ = 0;
};