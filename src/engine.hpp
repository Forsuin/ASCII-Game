#pragma once

#include "world.hpp"
#include "action.hpp"

class Engine {
   private:
    World world;

   public:
    void init();
    void loop();
    void render();
    Action processInput();
    void executeAction(Action action);
};
