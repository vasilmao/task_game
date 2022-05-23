#pragma once

template <typename Id>
class IdGenerator {
 public:
  Id Next();

 private:
  Id current_{1};
};

template <typename Id>
class StaticIdGenerator {
 public:
  static Id Next();
 
 private:
  static Id current_;
};

#include "ecs/Generator.ipp"
