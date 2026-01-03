#include <iostream>

#include "core/task_store.hpp"
#include "core/robot_store.hpp"
#include "core/dispatcher.hpp"


int main() {
    sd::TaskStore tasks;
    sd::RobotStore robots;
    sd::Dispatcher dispatcher;

    robots.upsert(sd::RobotId{1}, sd::Vec2{0,0}); // robot 1, position (0,0)
    robots.upsert(sd::RobotId{2}, sd::Vec2{5,5}); // robot 2, position (5,5)

    auto t1 = tasks.add_task(sd::Vec2{1,1}, sd::Vec2{9,9});
    auto t2 = tasks.add_task(sd::Vec2{2,2}, sd::Vec2{8,8});

    auto a1 = dispatcher.assign_one(tasks, robots);
    auto a2 = dispatcher.assign_one(tasks, robots);
    auto a3 = dispatcher.assign_one(tasks, robots);

    std::cout << "Assignment 1: " << (a1 ? "yes" : "no") << "\n";
    std::cout << "Assignment 2: " << (a1 ? "yes" : "no") << "\n";
    std::cout << "Assignment 3: " << (a1 ? "yes" : "no") << "\n"; // assignment 3 should be a no 
}