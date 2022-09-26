#pragma once

#include <string>

struct Stats{
    uint8_t strength;
    uint8_t dexterity;
    uint8_t constitution;
    uint8_t intelligence;
    uint8_t wisdom;
    uint8_t charisma;
};

struct Position{
    int x;
    int y;
};

class Entity {
   private:
    std::string firstName;
    std::string lastName;
    uint32_t age;
    uint8_t health;
    Stats stats;
    Position position;
};
