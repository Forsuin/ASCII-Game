#pragma once

#include <vector>
#include <unordered_set>

#include "tile.hpp"

class World {
   private:
    std::vector<Tile> tiles;

   public:
    World()= default;
    World(int x , int y) : tiles(x * y, Tile{}){}
};
