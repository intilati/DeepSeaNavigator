#include "GridMap.hpp"
#include <iostream>
using namespace std;

int main(int argc, char** argv) {
  string mapfile = (argc>1 ? argv[1] : "../config/example_map.txt");
  GridMap grid(0,0,0);
  if (!grid.loadFromText(mapfile)) {
    cerr<<"Failed to load map: "<<mapfile<<"\n";
    return 1;
  }
  cout<<"Loaded grid: "
           <<grid.getNX()<<"×"<<grid.getNY()<<"×"<<grid.getNZ()<<"\n";

  // Count free vs blocked
  int freeC=0, blkC=0;
  for(int z=0;z<grid.getNZ();++z)
    for(int y=0;y<grid.getNY();++y)
      for(int x=0;x<grid.getNX();++x)
        if (grid.isFree(x,y,z)) ++freeC; else ++blkC;

  cout<<"Free voxels: "<<freeC<<", Blocked voxels: "<<blkC<<"\n";
  return 0;
}
