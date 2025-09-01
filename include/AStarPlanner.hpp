#pragma once

#include "GridMap.hpp"
#include <vector>
#include <array>
#include <string>

using Coord = std::array<int,3>;
using Path = std::vector<Coord>;

struct Node {
    Coord pos;
    float g;         
    float f;         
    std::string parent; // parent key like "x,y,z", empty = none
};

class AStarPlanner {
public:
    
    AStarPlanner(const GridMap& grid, bool use_diag = false);

    bool plan(const Coord &start, const Coord &goal, Path &out_path);

    size_t nodesExpanded() const { return nodes_expanded; }
    double lastTimeMs() const { return last_time_ms; }

private:
    const GridMap& map;
    bool diag;

    size_t nodes_expanded = 0;
    double last_time_ms = 0.0;

    float heuristic(const Coord &a, const Coord &b) const;
    std::string key(const Coord &c) const;
    Coord parseKey(const std::string &k) const;
};
