# SwarmDock
SwarmDock is a C++ distributed robotics/automation control system that simulates a warehouse AMR fleet controller. It manages task assignment, robot state machines, telemetry streaming, and failure recovery for a fleet of mobile robots moving totes between stations.

Key features

Fleet Manager assigns missions (Pickup → Deliver → Return/Charge) and tracks global health.

Robot Agent runs a finite state machine (Idle, NavigateToPickup, Load, NavigateToDropoff, Unload, Charge, Fault).

Telemetry pipeline: robots stream heartbeats + metrics; dashboard/API consumes live state.

Fault tolerance: missed heartbeat detection, automatic re-assign, retry policies, safe-stop behavior.

Deterministic simulation: warehouse grid/map, travel time, station capacity constraints.

Everything in C++ with clean interfaces, unit tests, and reproducible builds.

Architecture (high level)

fleet_manager (central brain): mission scheduler + recovery logic

robot_agent (N instances): executes missions via FSM, publishes telemetry

telemetry_service: stores time-series-ish events + serves queries

dashboard_cli: view fleet status, missions, alerts

Tech

C++20, CMake, vcpkg (deps)

Protobuf + gRPC or ZeroMQ (pick one)

GoogleTest for unit tests

spdlog for logging

SQLite for event storage (optional but impressive)

Milestones

Single-process simulation (fleet + robots) with FSM

Split into multi-process services with IPC

Telemetry + CLI dashboard

Failure injection + recovery strategies

Packaging, docs, and demo video
