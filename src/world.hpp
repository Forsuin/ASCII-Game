#pragma once

#include <vector>
#include <unordered_set>

#include "tile.hpp"

class World {
   private:
    std::vector<Tile> tiles;
    std::unordered_set<Entity> entities;

   public:

};
