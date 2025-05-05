// #include "Core/MyBase.h"
#include "Core/MyGame.h"

using namespace DX3D;

int main() {
    MyGame* game = new MyGame(); // Create a new game instance
    game->Run(); // Run the game loop
    return 0;
}