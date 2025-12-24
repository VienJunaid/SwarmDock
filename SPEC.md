1) Core concepts

Robot: id, pose(x,y), battery, state, last_heartbeat, assigned_mission_id

Mission: id, tote_id, pickup_station, dropoff_station, priority, status

Station: id, type(PICKUP/DROPOFF/CHARGE), capacity, queue

Telemetry: timestamp, robot_id, state, battery, position, fault_code, message

2) Robot FSM (minimum viable)

Idle

NavigateToPickup

Load

NavigateToDropoff

Unload

NavigateToCharge

Charging

Fault (safe stop)

Transitions must be explicit and logged.

3) Fleet manager responsibilities

Maintain registry of robots and stations

Assign missions using a policy (nearest-robot + battery threshold + station availability)

Detect failures:

heartbeat timeout

stuck detection (no progress)

low battery

Recovery:

mission retry (limited)

reassign mission to a new robot

mark robot Fault and quarantine until recovered

4) Telemetry + observability

Heartbeat every N ms

Event stream includes:

mission assigned

state transition

fault raised/cleared

recovery action taken

CLI dashboard shows:

robots (state, battery, last heartbeat)

missions (pending/active/done)

alerts (timeouts, faults)

5) Failure injection (for demos)

drop heartbeats for robot X

force “stuck” behavior

random sensor fault

battery drain spike

6) Definition of done

docker compose up (optional) or ./run_sim.sh runs a full demo

One command starts fleet manager + N robot agents + dashboard

Demo script reproduces:

normal operations

injected failure

recovery + mission completion
