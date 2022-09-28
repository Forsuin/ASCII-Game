#include "engine.hpp"

int main(int argc, char* argv[]){
    Engine engine;
    engine.init(argc, argv);
    engine.loop();
}