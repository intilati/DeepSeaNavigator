
#include "GridMap.hpp"
#include "AStarPlanner.hpp"
#include <iostream>
#include <vector>
#include <array>

using namespace std;

typedef array<int,3> Coord;
typedef vector<Coord> Path;

int main() {
    int fails = 0;

    // Case 1: start == goal (trivial)
    {
        cout << "case_start_eq_goal: ";
        GridMap g(3,3,1);
        g.setOccupied(0,0,0, false); // start is free

        Coord s = {0,0,0};
        Coord t = {0,0,0};

        AStarPlanner planner(g, false);
        Path path;
        bool found = planner.plan(s, t, path);

        if (!found) {
            cout << "FAILED (no path found)\n";
            ++fails;
        } else if (path.size() != 1) {
            cout << "FAILED (expected size 1, got " << path.size() << ")\n";
            ++fails;
        } else {
            cout << "PASS\n";
        }
    }

    // Case 2: start out of bounds 
    {
        cout << "case_oob_start: ";
        GridMap g(4,4,2);
        Coord s = {-1,0,0}; // out of bounds
        Coord t = {1,1,0};

        AStarPlanner planner(g, false);
        Path path;
        bool found = planner.plan(s, t, path);

        if (found) {
            cout << "FAILED (expected no path)\n";
            ++fails;
        } else {
            cout << "PASS\n";
        }
    }

    // Case 3: start occupied
    {
        cout << "case_start_occupied: ";
        GridMap g(4,4,2);
        g.setOccupied(2,2,0, true); // block the start cell

        Coord s = {2,2,0};
        Coord t = {3,3,0};

        AStarPlanner planner(g, false);
        Path path;
        bool found = planner.plan(s, t, path);

        if (found) {
            cout << "FAILED (expected no path)\n";
            ++fails;
        } else {
            cout << "PASS\n";
        }
    }

    // Case 4: no path exists (blocked corridor)
    {
        cout << "case_no_path: ";
        GridMap g(5,5,1);
        // make all cells free first
        for (int y = 0; y < 5; ++y) {
            for (int x = 0; x < 5; ++x) {
                g.setOccupied(x,y,0, false);
            }
        }
        // block the middle row y = 2
        for (int x = 0; x < 5; ++x) {
            g.setOccupied(x,2,0, true);
        }

        Coord s = {2,0,0};
        Coord t = {2,4,0};

        AStarPlanner planner(g, false);
        Path path;
        bool found = planner.plan(s, t, path);

        if (found) {
            cout << "FAILED (expected no path)\n";
            ++fails;
        } else {
            cout << "PASS\n";
        }
    }

    // Case 5: small map correctness (diagonals allowed) 
    {
        cout << "case_small_map: ";
        GridMap g(3,3,1);
        // make all cells free
        for (int x = 0; x < 3; ++x) {
            for (int y = 0; y < 3; ++y) {
                g.setOccupied(x,y,0, false);
            }
        }

        Coord s = {0,0,0};
        Coord t = {2,2,0};

        AStarPlanner planner(g, true); // allow diagonal moves
        Path path;
        bool found = planner.plan(s, t, path);

        if (!found) {
            cout << "FAILED (no path found)\n";
            ++fails;
        } else {
            // with diagonal allowed, minimal waypoints should be small (2 or 3)
            cout << "PASS (size=" << path.size() << ")\n";
        }
    }

    // Case 6: benchmark moderate map (timing only)
    {
        cout << "case_benchmark: ";
        int nx = 80, ny = 80, nz = 6;
        GridMap g(nx, ny, nz);

        // set all free
        for (int z = 0; z < nz; ++z) {
            for (int y = 0; y < ny; ++y) {
                for (int x = 0; x < nx; ++x) {
                    g.setOccupied(x,y,z, false);
                }
            }
        }

        Coord s = {0,0,0};
        Coord t = {nx-1, ny-1, nz-1};

        AStarPlanner planner(g, true);
        Path path;
        bool found = planner.plan(s, t, path);

        if (!found) {
            cout << "FAILED to find path\n";
            ++fails;
        } else {
            cout << "PASS nodes=" << planner.nodesExpanded()
                 << " time_ms=" << planner.lastTimeMs() << "\n";
        }
    }

    // final result
    if (fails != 0) {
        cout << "TESTS FAILED: " << fails << " case(s)\n";
        return 1;
    }

    cout << "ALL EDGE CASES PASSED\n";
    return 0;
}



