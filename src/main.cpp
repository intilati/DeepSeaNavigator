#include "GridMap.hpp"
#include "AStarPlanner.hpp"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    if (argc < 8) {
        cout << "Usage: DeepSeaNavigator map.txt sx sy sz gx gy gz [--diag]\n";
        return 1;
    }
    string mapfile = argv[1];
    GridMap grid;
    if (!grid.loadFromText(mapfile)) {
        cerr << "Failed to load map: " << mapfile << "\n";
        return 1;
    }

    array<int,3> start = { stoi(argv[2]), stoi(argv[3]), stoi(argv[4]) };
    array<int,3> goal  = { stoi(argv[5]), stoi(argv[6]), stoi(argv[7]) };
    bool diag = (argc > 8 && string(argv[8]) == "--diag");

    AStarPlanner planner(grid, diag);
    Path path;
    bool ok = planner.plan(start, goal, path);
    if (!ok) {
        cout << "No path found (or invalid start/goal)\n";
        return 0;
    }

    cout << "# Waypoints: " << path.size() << "\n";
    for (auto &p : path) cout << p[0] << "," << p[1] << "," << p[2] << "\n";
    cout << "# Nodes expanded: " << planner.nodesExpanded() << "\n";
    cout << "# Time (ms): " << planner.lastTimeMs() << "\n";
    return 0;
}
