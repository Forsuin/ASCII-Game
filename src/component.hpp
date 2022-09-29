#pragma once

#include <memory>

#include <libtcod.hpp>
#include <utility>


struct Component {
    virtual ~Component() = default;
};

struct Position : Component {
    int x{};
    int y{};

    Position() = default;
    Position(int x, int y) : x(x), y(y) {}

};

struct Renderer : Component {
    TCOD_ColorRGB color{};
    char character{};
    std::string name;

    Renderer() = default;
    Renderer(TCOD_ColorRGB color, char character, std::string name)
        : color(color), character(character), name(std::move(name)) {}
};

struct Movable : Component{};

template<typename T, typename... Args>
std::unique_ptr<Component> makeComponent(Args... args){
    return std::make_unique<T>(std::forward<Args>(args)...);
}
