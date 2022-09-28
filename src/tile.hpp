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
    } type;

    bool isWalkable;

    Object(Object::Type type, bool isWalkable) : type(type), isWalkable(isWalkable){}
};

struct Tile {
    FloorType floor;
    Object object;
    Entity entity;

    Tile(FloorType floor, Object object) : floor(floor), object(object){}
};
