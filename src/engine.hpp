#pragma once

#include <vector>

#include "world.hpp"
#include "action.hpp"
#include "entity.hpp"

class Engine {
   private:
    World world;
    std::vector<Entity> entities;

    //tcod::Console used for rendering only
    tcod::Console console;
    tcod::Context context;

   public:
    Engine()= default;

    void init(int argc, char* argv[]);
    [[noreturn]] void loop();
    void render();
    static Action processInput();

    //could have a cache of controllable entities, maybe if needed
    void executeAction(Action action);
};
