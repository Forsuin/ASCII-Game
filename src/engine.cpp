#include <iostream>
#include <filesystem>
#include <optional>

#include <SDL.h>
#include <libtcod.hpp>

#include "engine.hpp"
#include "tile.hpp"


static std::optional<std::filesystem::path> getDataDir(){
    static auto root = std::filesystem::path{"."};

    while(!std::filesystem::exists(root / "data")){
        //If not current directory doesn't contain data, then check parent
        root /= "..";

        //At top level
        if(!std::filesystem::exists(root)){
            return std::nullopt;
        }
    }

    return root / "data";
}

void Engine::init(int argc, char* argv[]) {
    console = tcod::Console{80, 40};


    auto params = TCOD_ContextParams{};
    params.tcod_version = TCOD_COMPILEDVERSION;
    params.argc = argc;
    params.argv = argv;
    params.console = console.get();
    params.sdl_window_flags = SDL_WINDOW_RESIZABLE;
    params.vsync = true;
    params.window_title = "ASCII Game";

    std::optional<std::filesystem::path> dataPath = getDataDir();

    if (!dataPath.has_value()) {
        std::cout << "Unable to locate 'data' directory\n";
        std::exit(EXIT_FAILURE);
    }

    auto tileset = tcod::load_tilesheet(dataPath.value() / "sapphos_square_16x16.png", {16, 16}, tcod::CHARMAP_CP437);
    params.tileset = tileset.get();

    context = tcod::Context(params);



    Entity test;
    test.addComponent("Position", makeComponent<Position>(40, 20));
    test.addComponent("Renderable", makeComponent<Renderable>(TCOD_ColorRGB{255, 128, 128}, '@', "Test"));
    test.addComponent("Movable", makeComponent<Movable>());

    entities.push_back(std::move(test));
}

[[noreturn]] void Engine::loop() {
    while(true) {
        render();

        Action action = processInput();
        executeAction(action);
    }
}

void Engine::render() {
    TCOD_console_clear(console.get());

    for(int y = 0; y < 40; y++){
        for(int x = 0; x < 80; x++){
            tcod::print(console, {x, y}, "█", TCOD_color_RGB(x, y, 0), std::nullopt);
        }
    }

    for(const Entity& entity : entities){
        if(entity.hasComponents({"Position", "Renderable"})){
            Position* pos = entity.getComponent<Position>("Position").value();
            Renderable* renderer = entity.getComponent<Renderable>("Renderable").value();
            tcod::print(console, {pos->x, pos->y}, std::string(1, renderer->character), renderer->color, std::nullopt);
        }
    }

    context.present(console);
}

Action Engine::processInput() {
    SDL_Event event;
    SDL_WaitEvent(nullptr);

    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_KEYDOWN:
                //TODO: change to agent system
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
            default:
                return Action::NO_OP;
                break;
        }
    }
}

void Engine::executeAction(Action action) {
    if(action == Action::NO_OP) return;

    for(const Entity& entity : entities){
        if(entity.hasComponent("Movable")){
            Position* pos = entity.getComponent<Position>("Position").value();

            switch(action){
                case Action::MOVE_UP:
                    pos->y--;
                    break;
                case Action::MOVE_DOWN:
                    pos->y++;
                    break;
                case Action::MOVE_LEFT:
                    pos->x--;
                    break;
                case Action::MOVE_RIGHT:
                    pos->x++;
                    break;
                default:
                    return;
            }
        }
    }
}
