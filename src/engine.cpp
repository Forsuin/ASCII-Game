#include <SDL.h>
#include <iostream>
#include <filesystem>
#include <optional>

#include <libtcod.hpp>

#include "engine.hpp"


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

    auto tileset = tcod::load_tilesheet(dataPath.value() / "dejavu16x16_gs_tc.png", {32, 8}, tcod::CHARMAP_TCOD);
    params.tileset = tileset.get();

    context = tcod::Context(params);

    Entity test;
    test.addComponent("Position", makeComponent<Position>(40, 20));
    test.addComponent("Renderer", makeComponent<Renderer>(TCOD_ColorRGB{255, 128, 128}, '@', "Test"));
    test.addComponent("Movable", makeComponent<Movable>());

    for(auto const& [key, value] : test.components){
        std::cout << key << '\n';
    }

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
    tcod::print(console, {0, 0}, ".", std::nullopt, std::nullopt);

    for(const Entity& entity : entities){
        if(entity.hasComponents({"Position", "Renderer"})){
            std::cout << "Entity has components" << std::endl;
            Position* pos = entity.getComponent<Position>("Position").value();
            Renderer* renderer = entity.getComponent<Renderer>("Renderer").value();
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
        }
    }
}

void Engine::executeAction(Action action) {

}
