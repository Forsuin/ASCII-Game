#pragma once

#include <string>
#include <utility>

#include "libtcod.h"

class Material {
   public:
    static const Material STONE;
    static const Material WOOD;
    static const Material DIRT;
    static const Material SAND;

   private:
    const std::string name;
    const TCOD_ColorRGB color;

    Material(std::string name, TCOD_ColorRGB color) : name(std::move(name)), color(color) {}

   public:
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] TCOD_ColorRGB getColor() const;
    [[nodiscard]] std::string toString() const;
};

