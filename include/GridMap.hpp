#pragma once
#include <vector>
#include <array>
#include<string>


class GridMap {
    public:
        GridMap(int nx,int ny,int nz);
        bool loadFromText(const std::string &path);

        bool inBounds(int x,int y,int z) const;
        bool isFree(int x,int y,int z) const;

        int getNX() const { return nx; }
        int getNY() const { return ny; }
        int getNZ() const { return nz; }

    private:
        int nx,ny,nz;
        std::vector<uint8_t> data;

        inline int idx(int x,int y,int z) const { return x + nx * (y + ny * z); }

};