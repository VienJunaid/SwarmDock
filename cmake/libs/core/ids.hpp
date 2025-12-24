#pragma once

#include <cstdint>
#include <functional>
#include <ostream>
#include <string>
#include <string_view>

namespace swarmdock::core {

// Small, strongly-typed IDs so you don't mix RobotId with MissionId accidentally.

struct RobotId {
  std::uint32_t value{0};

  constexpr explicit RobotId(std::uint32_t v = 0) : value(v) {}

  friend constexpr bool operator==(RobotId a, RobotId b) { return a.value == b.value; }
  friend constexpr bool operator!=(RobotId a, RobotId b) { return !(a == b); }
  friend constexpr bool operator<(RobotId a, RobotId b) { return a.value < b.value; }

  friend std::ostream& operator<<(std::ostream& os, const RobotId& id) {
    return os << "R" << id.value;
  }
};

struct MissionId {
  std::uint64_t value{0};

  constexpr explicit MissionId(std::uint64_t v = 0) : value(v) {}

  friend constexpr bool operator==(MissionId a, MissionId b) { return a.value == b.value; }
  friend constexpr bool operator!=(MissionId a, MissionId b) { return !(a == b); }
  friend constexpr bool operator<(MissionId a, MissionId b) { return a.value < b.value; }

  friend std::ostream& operator<<(std::ostream& os, const MissionId& id) {
    return os << "M" << id.value;
  }
};

struct RunId {
  std::uint64_t value{0};

  constexpr explicit RunId(std::uint64_t v = 0) : value(v) {}

  friend constexpr bool operator==(RunId a, RunId b) { return a.value == b.value; }
  friend constexpr bool operator!=(RunId a, RunId b) { return !(a == b); }
  friend constexpr bool operator<(RunId a, RunId b) { return a.value < b.value; }

  friend std::ostream& operator<<(std::ostream& os, const RunId& id) {
    return os << "Run" << id.value;
  }
};

// Optional helpers if you want string formatting
inline std::string to_string(RobotId id)   { return "R" + std::to_string(id.value); }
inline std::string to_string(MissionId id) { return "M" + std::to_string(id.value); }
inline std::string to_string(RunId id)     { return "Run" + std::to_string(id.value); }

} // namespace swarmdock::core

// Hash support so RobotId/MissionId can be keys in unordered_map/unordered_set
template <>
struct std::hash<swarmdock::core::RobotId> {
  size_t operator()(swarmdock::core::RobotId id) const noexcept {
    return std::hash<std::uint32_t>{}(id.value);
  }
};

template <>
struct std::hash<swarmdock::core::MissionId> {
  size_t operator()(swarmdock::core::MissionId id) const noexcept {
    return std::hash<std::uint64_t>{}(id.value);
  }
};

template <>
struct std::hash<swarmdock::core::RunId> {
  size_t operator()(swarmdock::core::RunId id) const noexcept {
    return std::hash<std::uint64_t>{}(id.value);
  }
};
