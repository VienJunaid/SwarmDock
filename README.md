# SwarmDock — Warehouse AMR Fleet Controller (C++)

## One-liner
SwarmDock is a fault-tolerant distributed control system for a warehouse AMR fleet: it assigns missions, orchestrates robot state machines, streams telemetry, and recovers safely from failures — built end-to-end in modern C++.

## Resume-ready project title
**SwarmDock: Fault-Tolerant Warehouse AMR Fleet Controller (C++)**

## Context (what SwarmDock “is”)
A simulated warehouse has:
- 5–50 AMRs (Autonomous Mobile Robots) that move totes between locations
- Tasks like: “Pickup tote at A3 → deliver to Pack-02”
- Fleet controller services that:
  - assign jobs
  - monitor robot health/telemetry
  - coordinate traffic and docking/charging
  - detect failures and recover (timeouts, dropped robots, stuck robots)

SwarmDock provides this as a distributed, production-style system.

## Key features
1) Distributed services (microservice-like architecture) in C++
- Fleet Manager (job assignment + global policy)
- Robot Agent (runs per robot; state machine + local safety)
- Telemetry Service (ingest/store/stream robot metrics)
- Mission Service (task queue + persistence)
- UI/CLI Dashboard (real-time status + logs)

2) Explicit state machines
- Robot state machine: IDLE → DISPATCHED → NAVIGATING → PICKING → DELIVERING → DOCKING → CHARGING → IDLE
- Failure states: DEGRADED, LOST_COMMS, EMERGENCY_STOP, RECOVERING

3) Telemetry + observability
- Heartbeats, pose, velocity, battery, mission progress
- Structured logging, metrics, trace IDs

4) Failure recovery
- Lease-based assignment to avoid duplicate control
- Heartbeat timeouts → reassign mission
- Robot rejoin protocol after reconnect
- Dead-letter queue for missions that repeatedly fail
- “Safe stop” behavior when comms drop

## Tech choices (all C++)
Language: C++20 (or C++17 if you prefer)
Build: CMake
Tests: GoogleTest
Formatting: clang-format
Lint: clang-tidy

Recommended networking:
Option A (simple, impressive): gRPC + Protobuf (C++)
Option B (lightweight): REST over HTTP (Boost.Beast) + JSON
Option C (middleware vibe): ZeroMQ pub/sub + request/reply

Data:
- SQLite for mission persistence (simple + real-world)
- In-memory cache for hot state (robot last-known)

## Repo structure
swarmdock/
  CMakeLists.txt
  README.md
  PROJECT_SPEC.md
  docs/
    architecture.md
    state_machines.md
    message_schemas.md
    failure_recovery.md
  proto/                      (if using gRPC)
  common/
    include/
    src/
  services/
    fleet_manager/
      include/
      src/
      tests/
    robot_agent/
      include/
      src/
      tests/
    telemetry_service/
      include/
      src/
      tests/
    mission_service/
      include/
      src/
      tests/
    sim_world/
      include/
      src/
      tests/
  tools/
    cli_dashboard/
  scripts/
    run_local.sh
  .clang-format
  .clang-tidy
  .github/workflows/ci.yml

## System architecture (high level)
- RobotAgent publishes telemetry + heartbeat periodically.
- FleetManager maintains global view of fleet and assigns missions.
- MissionService owns mission queue + persistence.
- TelemetryService aggregates telemetry and exposes streams for dashboard.
- SimWorld provides a warehouse map + robot motion simulation.

### Core message types
- Heartbeat { robot_id, ts, status, battery, lease_epoch }
- Telemetry { robot_id, ts, pose(x,y,theta), vel, errors[] }
- Mission { mission_id, pickup_node, dropoff_node, priority, deadline }
- Assignment { mission_id, robot_id, lease_id, ttl_ms }
- Ack/Nack { message_id, reason }

## Robot state machine (must implement)
States:
- IDLE
- DISPATCHED
- NAVIGATING_TO_PICKUP
- PICKING
- NAVIGATING_TO_DROPOFF
- DROPPING
- DOCKING
- CHARGING
Failure/override:
- DEGRADED
- LOST_COMMS
- EMERGENCY_STOP
- RECOVERING

Triggers:
- assignment received
- reached waypoint
- pickup success/fail
- dropoff success/fail
- battery low threshold
- obstacle/stuck detected
- heartbeat missed
- manual e-stop

## Failure recovery policy (must implement)
1) Heartbeat timeout:
- FleetManager marks robot LOST_COMMS after N missed heartbeats.
- Any mission leased to that robot returns to pending queue after TTL.

2) Leasing:
- FleetManager issues Assignment with lease_id + TTL.
- RobotAgent must renew lease periodically.
- If lease expires, RobotAgent must stop controlling mission and return to IDLE/RECOVERING.

3) Mission retries:
- Each mission has retry_count.
- After max retries, mission goes to Dead Letter Queue with reason.

4) Rejoin:
- RobotAgent reconnects with last known mission_id + lease_id.
- FleetManager decides: resume mission OR cancel/reassign.

## Simulation (so you can demo without hardware)
- Grid or graph map (nodes + edges)
- Simple path planning: A* over grid OR shortest path over graph
- Robot motion model: constant velocity + acceleration limits
- Collision avoidance (minimal version):
  - reserve edges/time slots OR
  - simple “stop if too close” rule (still okay for v1)

## Deliverables recruiters care about
- Live demo: run 10 robots, enqueue 50 missions, show dashboard
- Failure demo: kill a service or drop robot comms and show recovery
- CI pipeline: build + unit tests + formatting checks
- Clean documentation + diagrams

## Milestones (build order)
M0: Repo + CMake + CI + lint/format + basic tests
M1: Message bus + common types (protobuf/json), logging
M2: MissionService (queue + SQLite persistence)
M3: RobotAgent state machine (single robot) + heartbeats
M4: FleetManager assignment + leasing
M5: TelemetryService + CLI dashboard
M6: SimWorld map + motion + simple planner
M7: Failure injection + recovery demos (timeouts, restarts)
M8: Polish: docs, diagrams, performance, README screenshots/gifs

## “How to run” (target command)
./scripts/run_local.sh --robots 10 --missions 50

## README bullets you’ll eventually claim (targets)
- Built a distributed C++20 fleet controller for warehouse AMRs with gRPC messaging, mission persistence, and real-time telemetry streaming.
- Implemented robot state machines, lease-based assignment, and automated recovery from heartbeat loss and service restarts.
- Shipped CI with unit/integration tests, clang-tidy, and reproducible local simulation demo.

## Nice-to-have stretch goals (choose 1–2)
- Web dashboard (optional) fed by telemetry service
- Deterministic replay of runs from recorded telemetry
- Load testing: 100 robots / 10k telemetry msgs/sec
- Formal state machine modeling + property tests




## Actual Implementation
1. Simulate:
    - 3 Robots
    - 10 missions
    - Finite State Machine Transitions
    - Basic Assignments 

2. Telemetry 
    - Every state transition emits an "event"
    - "print status"

3. After Logic works
    - fleet_manager process
    - multiple robot_agent processes

4. Failure Recovery 
    - Heartbeat timeout -> Mark robot lost -> reassign mission
    - Stuck Detection -> Cancel Mission -> replan or reassign
    - Low Battery -> preempt mission -> go charge (and reassign) 

    
>>>>>>> 613a55a (Worked on core files)
