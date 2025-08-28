#include "GridMap.hpp"
#include <iostream>
#include <cassert>
using namespace std;


int main() {
  GridMap m(5,5,2);
  // toggle occupancy pattern
  for (int z=0; z<m.getNZ(); ++z)
    for (int y=0; y<m.getNY(); ++y)
      for (int x=0; x<m.getNX(); ++x)
        m.setOccupied(x,y,z, ((x+y+z)%2)==1);

  assert(m.inBounds(0,0,0));
  assert(!m.inBounds(-1,0,0));
  assert(!m.inBounds(5,0,0));

  bool f00 = m.isFree(0,0,0); (void)f00;
  auto nbrs6 = m.neighbors(2,2,0,false);
  auto nbrs26 = m.neighbors(2,2,0,true);
  cout << "Neighbors (6): " << nbrs6.size() << "\n";
  cout << "Neighbors (26): " << nbrs26.size() << "\n";

  GridMap::coord a = {0,0,0}, b = {1,1,1};
  float d = m.distance(a,b);
  cout << "Distance (0,0,0)-(1,1,1): " << d << "\n";
  assert(d > 1.7f && d < 1.74f);

  cout << "test_gridmap OK\n";
  return 0;
}
