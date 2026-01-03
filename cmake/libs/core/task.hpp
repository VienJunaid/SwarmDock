#pragma once

#include <cstdint>

#include "core/ids.hpp"
#include "core/geometry.hpp"

namespace sd {

enum class TaskStatus : std::uint8_t {
  Queued = 0,
  Assigned = 1,
  InProgress = 2,
  Done = 3,
  Failed = 4
};

struct Task {
  TaskId id{};
  Vec2 pickup{};
  Vec2 dropoff{};

  TaskStatus status = TaskStatus::Queued;
  RobotId assigned_robot{};   // 0 means "none"
  std::int32_t priority = 0;  // higher = more important
};

} // namespace sd
