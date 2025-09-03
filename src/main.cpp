
#include "GridMap.hpp"
#include "AStarPlanner.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <array>

using namespace std;

// Save waypoints to CSV (x,y,z per line)
bool writePathCSV(const Path &path, const string &filename) {
    ofstream out(filename);
    if (!out.is_open()) return false;
    out << "x,y,z\n";
    for (size_t i = 0; i < path.size(); ++i) {
        out << path[i][0] << "," << path[i][1] << "," << path[i][2] << "\n";
    }
    out.close();
    return true;
}

// Save only occupied voxels to CSV (x,y,z per line)
bool writeOccupiedCSV(const GridMap &map, const string &filename) {
    ofstream out(filename);
    if (!out.is_open()) return false;
    out << "x,y,z\n";
    for (int z = 0; z < map.getNZ(); ++z) {
        for (int y = 0; y < map.getNY(); ++y) {
            for (int x = 0; x < map.getNX(); ++x) {
                if (!map.isFree(x, y, z)) {
                    out << x << "," << y << "," << z << "\n";
                }
            }
        }
    }
    out.close();
    return true;
}

int main(int argc, char **argv) {
    
    if (argc < 8) {
        cout << "Usage: voxnav map.txt sx sy sz gx gy gz [--diag]\n";
        return 1;
    }


    string mapfile = argv[1];
    int sx = stoi(argv[2]);
    int sy = stoi(argv[3]);
    int sz = stoi(argv[4]);
    int gx = stoi(argv[5]);
    int gy = stoi(argv[6]);
    int gz = stoi(argv[7]);

    bool diag = false;
    if (argc > 8) {
        string flag = argv[8];
        if (flag == "--diag") diag = true;
    }

    // load map
    GridMap grid;                 // requires default ctor (empty)
    if (!grid.loadFromText(mapfile)) {
        cerr << "Failed to load map: " << mapfile << "\n";
        return 1;
    }

    // prepare planner and run
    array<int,3> start = { sx, sy, sz };
    array<int,3> goal  = { gx, gy, gz };

    AStarPlanner planner(grid, diag);
    Path path;
    bool found = planner.plan(start, goal, path);

    if (!found) {
        cout << "No path found (or invalid start/goal)\n";
        return 0;
    }

    // print path
    cout << "# Waypoints: " << path.size() << "\n";
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i][0] << "," << path[i][1] << "," << path[i][2] << "\n";
    }

    // print stats
    cout << "# Nodes expanded: " << planner.nodesExpanded() << "\n";
    cout << "# Time (ms): " << planner.lastTimeMs() << "\n";

    // export CSV files
    bool ok1 = writePathCSV(path, "out_path.csv");
    bool ok2 = writeOccupiedCSV(grid, "out_occupied.csv");

    if (ok1 && ok2) {
        cout << "Wrote out_path.csv and out_occupied.csv\n";
    } else {
        if (!ok1) cerr << "Failed to write out_path.csv\n";
        if (!ok2) cerr << "Failed to write out_occupied.csv\n";
    }

    return 0;
}



