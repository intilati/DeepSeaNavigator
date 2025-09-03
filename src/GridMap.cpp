// GridMap.cpp
#include "GridMap.hpp"
#include <fstream>
#include <cmath>
#include<stdexcept>
#include <iostream>
using namespace std;

GridMap::GridMap() {
    nx = 0;
    ny = 0;
    nz = 0;
    data.clear();
}

// Constructor with sizes
GridMap::GridMap(int nx_, int ny_, int nz_) {
    nx = nx_;
    ny = ny_;
    nz = nz_;
    data.assign(nx * ny * nz, 1); // initially mark all as occupied (1)
}

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

bool GridMap:: saveToText(const string &path) const{
    ofstream out(path);
    if(!out) return false;
    out << nx<< " "<< ny<<" "<<nz<<"\n";
    for(int z=0;z<nz;++z){
        for(int y=0;y<ny;++y){
            for(int x=0;x<nx;++x){
                out<< int(data[idx(x,y,z)])<< (x+1==nx ? "\n" : " ");
            }
            out<<"\n";
        }
        out<<"\n";
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
bool GridMap::setOccupied(int x, int y, int z, bool occ) {
    if (!inBounds(x, y, z)) return false;
    data[idx(x, y, z)] = occ ? 1 : 0;  
    return true;
}


vector<coord> GridMap::neighbors(int x, int y, int z, bool diag) const {
    int offs6[6][3] = {
        {1,0,0}, {-1,0,0}, {0,1,0}, {0,-1,0}, {0,0,1}, {0,0,-1}
    };

    vector<coord> out;
    if(!diag){
        for(int i=0;i<6;i++){
            int nx=x+offs6[i][0];
            int ny=y+offs6[i][1];
            int nz=z+offs6[i][2];
            if(inBounds(nx,ny,nz) && isFree(nx,ny,nz))
                out.push_back({nx,ny,nz});
        }
        return out;
    }

    out.reserve(26);
    for(int dx=-1;dx<=1;dx++){
        for(int dy=-1;dy<=1;dy++){
            for(int dz=-1; dz<=1;dz++){
                if(dx==0 && dy==0 && dz==0) continue;
                int nx=x+dx, ny=y+dy, nz=z+dz;
                if(inBounds(nx,ny,nz) && isFree(nx,ny,nz))
                    out.push_back({nx,ny,nz});
            }
        }
    }
    return out;
}

float GridMap:: distance(const coord&a, const coord &b) const{
    float dx=float(a[0]-b[0]);
    float dy=float(a[1]-b[1]);
    float dz=float(a[2]-b[2]);
    return sqrt(dx*dx+ dy*dy + dz*dz);
}

    





