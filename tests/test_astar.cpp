#include "GridMap.hpp"
#include "AStarPlanner.hpp"
#include <iostream>

using namespace std;

int main() {
    GridMap grid;
    if (!grid.loadFromText("config/example_map.txt")) {
        cerr << "Failed to load config/example_map.txt\n";
        return 1;
    }

    array<int,3> start = {0,0,0};
    array<int,3> goal  = {5,5,2}; // change to a valid cell within your map dims
    AStarPlanner planner(grid, false);
    Path path;
    bool ok = planner.plan(start, goal, path);
    if (!ok) {
        cout << "No path found\n";
        return 0;
    }
    cout << "Path length (waypoints): " << path.size() << "\n";
    for (auto &p : path) cout << p[0] << "," << p[1] << "," << p[2] << "\n";
    cout << "Nodes expanded: " << planner.nodesExpanded() << "\n";
    cout << "Time (ms): " << planner.lastTimeMs() << "\n";
    return 0;
}
