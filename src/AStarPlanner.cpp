#include "AStarPlanner.hpp"
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <chrono>
#include <sstream>
#include <iostream>
#include<algorithm>

using namespace std;

AStarPlanner::AStarPlanner(const GridMap& grid, bool use_diag)
  : map(grid), diag(use_diag) {}

float AStarPlanner::heuristic(const Coord &a, const Coord &b) const {
    float dx = float(a[0]-b[0]);
    float dy = float(a[1]-b[1]);
    float dz = float(a[2]-b[2]);
    return sqrt(dx*dx + dy*dy + dz*dz);
}

std::string AStarPlanner::key(const Coord &c) const {
    return to_string(c[0]) + "," + to_string(c[1]) + "," + to_string(c[2]);
}

Coord AStarPlanner::parseKey(const std::string &k) const {
    Coord c = {-1,-1,-1};
    int x,y,z;
    if (sscanf(k.c_str(), "%d,%d,%d", &x,&y,&z) == 3) {
        c = {x,y,z};
    }
    return c;
}

bool AStarPlanner::plan(const Coord &start, const Coord &goal, Path &out_path) {
    nodes_expanded = 0;
    out_path.clear();

    // validate
    if (!map.inBounds(start[0], start[1], start[2]) ||
        !map.inBounds(goal[0], goal[1], goal[2])) {
        return false;
    }
    if (!map.isFree(start[0], start[1], start[2]) ||
        !map.isFree(goal[0], goal[1], goal[2])) {
        return false;
    }

    using Clock = chrono::high_resolution_clock;
    auto t0 = Clock::now();

    // open set: min-heap by f. pair<f, key>
    priority_queue<pair<float,string>, vector<pair<float,string>>, greater<pair<float,string>>> open;

    unordered_map<string, Node> all;       // key -> Node
    unordered_set<string> closed;          // visited keys

    string start_key = key(start);
    string goal_key  = key(goal);

    Node s;
    s.pos = start; s.g = 0.0f; s.f = heuristic(start, goal); s.parent = "";
    all[start_key] = s;
    open.push({s.f, start_key});

    while (!open.empty()) {
        auto top = open.top(); open.pop();
        string cur_key = top.second;

        // skip stale entries
        if (closed.find(cur_key) != closed.end()) continue;

        Node cur = all[cur_key]; // copy

        nodes_expanded++;
        // goal?
        if (cur_key == goal_key) {
            // reconstruct path
            string k = cur_key;
            while (!k.empty()) {
                Node &nref = all[k];
                out_path.push_back(nref.pos);
                if (nref.parent.empty()) break;
                k = nref.parent;
            }
            reverse(out_path.begin(), out_path.end());
            auto t1 = Clock::now();
            last_time_ms = chrono::duration<double, milli>(t1 - t0).count();
            return true;
        }

        closed.insert(cur_key);

        // expand neighbors from grid
        auto nbrs = map.neighbors(cur.pos[0], cur.pos[1], cur.pos[2], diag);
        for (auto &nb : nbrs) {
            string nbk = key(nb);
            if (closed.find(nbk) != closed.end()) continue;

            float step_cost = map.distance(cur.pos, nb);
            float tentative_g = cur.g + step_cost;

            auto it = all.find(nbk);
            if (it == all.end()) {
                Node n;
                n.pos = nb;
                n.g = tentative_g;
                n.f = tentative_g + heuristic(nb, goal);
                n.parent = cur_key;
                all[nbk] = n;
                open.push({n.f, nbk});
            } else {
                if (tentative_g < it->second.g) {
                    it->second.g = tentative_g;
                    it->second.f = tentative_g + heuristic(nb, goal);
                    it->second.parent = cur_key;
                    open.push({it->second.f, nbk});
                }
            }
        }
    }

    auto t1 = Clock::now();
    last_time_ms = chrono::duration<double, milli>(t1 - t0).count();
    return false; // no path found
}
