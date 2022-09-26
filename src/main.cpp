#include <filesystem>
#include <optional>
#include <iostream>

#include <SDL.h>
#include <libtcod.hpp>
#include <fmt/format.h>

std::optional<std::filesystem::path> getDataDir(){
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

int main(int argc, char* argv[]){
    tcod::Console console = tcod::Console{80, 40};


    TCOD_ContextParams params = TCOD_ContextParams{};
    params.tcod_version = TCOD_COMPILEDVERSION;
    params.argc = argc;
    params.argv = argv;
    params.console = console.get();
    params.sdl_window_flags = SDL_WINDOW_RESIZABLE;
    params.vsync = true;
    params.window_title = "ASCII Game";


    std::optional<std::filesystem::path> dataPath = getDataDir();

    if(!dataPath.has_value()){
        fmt::print("Unable to locate 'data' directory");
        std::exit(EXIT_FAILURE);
    }

    auto tileset = tcod::load_tilesheet(dataPath.value() / "dejavu16x16_gs_tc.png", {32, 8}, tcod::CHARMAP_TCOD);
    params.tileset = tileset.get();

    tcod::Context context = tcod::Context(params);


    while(true){
        TCOD_console_clear(console.get());
        tcod::print(console, {0, 0}, "Hello World", std::nullopt, std::nullopt);
        context.present(console);

        SDL_Event event;
        SDL_WaitEvent(nullptr);
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym){
                        SDLK_UP:
                    }
                case SDL_QUIT:
                    return 0;
            }
        }
    }
}