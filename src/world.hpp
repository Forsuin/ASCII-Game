#pragma once

#include <vector>
#include <unordered_set>

#include "libtcod.hpp"

#include "tile.hpp"


class World {
   private:
    tcod::Matrix<Tile, 2> tiles;

   public:
    World() = default;
    World(int x, int y) : tiles({x, y}, Tile(Material::STONE)) {}

    [[nodiscard]]inline constexpr auto begin() noexcept {
        return tiles.begin();
    }

    [[nodiscard]] inline constexpr auto begin() const noexcept {
        return tiles.begin();
    }

    [[nodiscard]] inline constexpr auto end() noexcept {
        return tiles.end();
    }

    [[nodiscard]] inline constexpr auto end() const noexcept {
        return tiles.end();
    }

    //Get tile at index
    inline auto operator[](const std::array<int, 2>& index) {
        return tiles[index];
    }

    //Get the const tile at index
    inline auto operator[](const std::array<int, 2>& index) const {
        return tiles[index];
    }

    //Get the tile at index, with bounds checking
    inline auto at(const std::array<int, 2>& index) {
        return tiles.at(index);
    }

    //Get the const tile at index, with bounds checking
    [[nodiscard]] inline auto at(const std::array<int, 2>& index) const {
        return tiles.at(index);
    }

    [[nodiscard]] inline bool inBounds(const std::array<int, 2>& index) const noexcept {
        return tiles.in_bounds(index);
    }
};
