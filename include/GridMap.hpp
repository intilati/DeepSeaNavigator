#pragma once
#include <vector>
#include <array>
#include<string>

using coord = std:: array<int,3>;


class GridMap {
    public:
        using coord = std:: array<int,3>;
        GridMap(int nx,int ny,int nz);
        bool loadFromText(const std::string &path);
        bool saveToText(const std::string &path) const;

        bool inBounds(int x,int y,int z) const;
        bool isFree(int x,int y,int z) const;
        bool setOccupied(int x,int y,int z,bool occ);

        std :: vector<coord> neighbors(int x,int y,int z, bool diag=false) const;


        float distance(const coord &a, const coord& b) const;
        int getNX() const { return nx; }
        int getNY() const { return ny; }
        int getNZ() const { return nz; }

    private:
        int nx,ny,nz;
        std::vector<uint8_t> data;

        inline int idx(int x,int y,int z) const { return x + nx * (y + ny * z); }

};