#pragma once

#include <vector>
#include <cstdint>

#include "core/task.hpp"

namespace sd {
    class TaskStore {
        public: 

        // method: adding a new task and retun its id 
        TaskId add_task(Vec2 pickup, Vec2 dropoff, std::int32_t priority = 0) {
            Task t;
            t.id = TaskId{next_id++};
            t.pickup = pickup;
            t.dropoff = dropoff;
            t.priority = priority;
            t.status = TaskStatus::Queued;
            t.assigned_robot = RobotId{0};

            tasks_.push_back(t);
            return t.id;
        }


        // method: get a task by id (nullptr if not found)
        Task* get(TaskId id) {
            for (auto& t : tasks_) {
                if (t.id == id) return &t;
            }
            return nullptr;
        }

        const Task* get(TaskId id) const {
            for (const auto& t : tasks_) {
                if (t.id == id) return &t;
            }
            return nullptr;
        }

        // method: Return pointers to all queued tasks
        std::vector<Task*> queued() {
            std::vector<Task*> out;
            for (auto& t : tasks_) {
                if (t.status == TaskStatus::Queued) out.push_back(&t);
            }
            return out; 
        }

        // method: assign a task for a robot and mark it assigned
        bool assign(TaskId id, RobotId robot) {
            Task* t = get(id); // no instances of an overloaded fucntion with matching parameters (fix later) 
            if (!t) return false;
            if (t->status != TaskStatus::Queued) return false;

            t->assigned_robot = robot;
            t->status = TaskStatus::Assigned;
            return true; 
        }

        // method: Mark task progress
        bool set_status(TaskId id, TaskStatus s) {
            Task* t = get(id);
            if (!t) return false;
            t->status = s;
            return true; 
        }

        private: 
            std::uint32_t next_id = 1; // start at 1, 0 means invalid
            std::vector<Task> tasks_;

    };
}