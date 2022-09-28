#pragma once

#include <vector>
#include <unordered_set>

#include "tile.hpp"

class World {
   private:
    std::vector<Tile> tiles;

   public:
    World(){}
    World(int x , int y){
        for(int i = 0; i < x * y; i++){
            tiles.push_back({FloorType::STONE, {Object::Type::DOOR, true}});
        }
    }
};
