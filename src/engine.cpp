#include <SDL.h>
#include <fmt/format.h>

#include "engine.hpp"

void Engine::init(){

}

void Engine::loop() {
    render();

    Action action = processInput();
    executeAction(action);
}

void Engine::render() {

}

Action Engine::processInput() {
    SDL_Event event;
    SDL_WaitEvent(nullptr);

    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_KEYDOWN:
                //TODO: return attack_dir based on enemy position
                switch(event.key.keysym.sym){
                    case SDLK_UP:
                        return Action::MOVE_UP;
                    case SDLK_DOWN:
                        return Action::MOVE_DOWN;
                    case SDLK_LEFT:
                        return Action::MOVE_LEFT;
                    case SDLK_RIGHT:
                        return Action::MOVE_RIGHT;
                }
            case SDL_QUIT:
                //TODO: could save on exit later
                std::exit(EXIT_SUCCESS);
                break;
        }
    }
}

void Engine::executeAction(Action action) {

}
