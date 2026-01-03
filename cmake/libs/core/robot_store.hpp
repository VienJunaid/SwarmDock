#pragma once

#include <vector>
#include "core/robot_state.hpp"

namespace sd {
    class RobotStore{
        public:

        // method: Add robot if missing or update its position/mode if it exists
        void upsert(RobotId id, Vec2 position, RobotMode mode = RobotMode::Idle) {
            RobotState* r = get(id);
            if (!r) {
                RobotState rs;
                rs.id = id;
                rs.position = position;
                rs.mode = mode;
                robots_.push_back(rs);
                return;
            }
            r->position = position;
            r->mode = mode;
        }

        RobotState* get(RobotId id) {
            for (auto& r : robots_) {
                if (r.id == id) return &r;
            }
            return nullptr;
        }

        const RobotState* get(RobotId id) const {
            for (const auto& r : robots_) {
                if (r.id == id) return &r;
            }
            return nullptr;
        }

        std::vector<RobotState*> idle_robots() {
            std::vector<RobotState*> out;
            for (auto& r : robots_) {
                if (r.mode == RobotMode::Idle) out.push_back(&r);
            }
            return out; 
        }

        private:
        std::vector<RobotState> robots_;
    };
}