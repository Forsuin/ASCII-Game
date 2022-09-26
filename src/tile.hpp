#pragma once

#include "entity.hpp"

enum struct FloorType {
    STONE,
    WOOD,
    TILE
};

struct Object {
    enum struct Type{
        DOOR,
        CHAIR,
        CRAFTING_TABLE,
    };

    bool isTransparent;
};

class Tile {
   private:
    FloorType floor;
    Object object;
};
