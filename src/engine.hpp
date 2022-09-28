#pragma once

#include <vector>

#include "world.hpp"
#include "action.hpp"
#include "entity.hpp"

class Engine {
   private:
    World world;
    std::vector<Entity> entities;

    tcod::Console console;
    tcod::Context context;

   public:
    Engine()= default;

    void init(int argc, char* argv[]);
    void loop();
    void render();
    static Action processInput();
    static void executeAction(Action action);
};
