// GridMap.cpp
#include "GridMap.hpp"
#include <fstream>
#include <iostream>
using namespace std;

GridMap::GridMap(int nx_, int ny_, int nz_)
  : nx(nx_), ny(ny_), nz(nz_), data(nx_ * ny_ * nz_, 1)
{}

bool GridMap::loadFromText(const string& path) {
    ifstream in(path);
    if (!in) return false;

    in >> nx >> ny >> nz;
    data.assign(nx * ny * nz, 1);

    for (int z = 0; z < nz; ++z) {
        for (int y = 0; y < ny; ++y) {
            for (int x = 0; x < nx; ++x) {
                int v;
                in >> v;
                data[idx(x, y, z)] = (v == 0 ? 0 : 1);
            }
        }
    }
    return true;
}

bool GridMap::inBounds(int x, int y, int z) const {
    return x >= 0 && x < nx
        && y >= 0 && y < ny
        && z >= 0 && z < nz;
}

bool GridMap::isFree(int x, int y, int z) const {
    if (!inBounds(x, y, z)) return false;
    return data[idx(x, y, z)] == 0;
}


