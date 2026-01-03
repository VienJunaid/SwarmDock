#pragma once

#include <optional>
#include <utility>

#include "core/task_store.hpp"
#include "core/robot_store.hpp"

namespace sd {
    class Dispatcher {
        public:

        // method: Returns (task_id, robot_id) if it made an assignment
        std::optional<std::pair<TaskId, RobotId>> assign_one(TaskStore& tasks, RobotStore& robots) {
            auto q = tasks.queued();
            if (q.empty()) return std::nullopt;

            auto idle = robots.idle_robots();
            if (idle.empty()) return std::nullopt;

            Task* t = q.front();
            RobotState* r = idle.front();

            if (!tasks.assign(t->id, r->id)) return std::nullopt;

            // Mark robot as busy immmediately
            r->mode = RobotMode::Busy;

            return std::make_pair(t->id, r->id);

        }
    };

} // namespace id 