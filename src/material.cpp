#include <fmt/format.h>

#include "material.hpp"


std::string Material::getName() const {
    return name;
}

TCOD_ColorRGB Material::getColor() const {
    return color;
}

std::string Material::toString() const {
    std::string output = "";

    output += name;
    output += " " + color.r;
    output += " " + color.g;
    output += " " + color.b;

    return output;
    //return fmt::format("{} Color: ({}, {}, {})", name, color.r, color.g, color.b);
}

const Material Material::STONE = Material("Stone", {220,220,220});
const Material Material::WOOD = Material("Wood", {186, 140, 99});
const Material Material::DIRT = Material("Dirt", {155, 118, 83});
const Material Material::SAND = Material("Sand", {194, 178, 128});