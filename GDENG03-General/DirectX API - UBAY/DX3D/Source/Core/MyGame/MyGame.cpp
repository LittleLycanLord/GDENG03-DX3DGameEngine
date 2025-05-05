#include "Core/MyGame.h"
#include "Core/MyWindow.h"
//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
DX3D::MyGame::MyGame() {
    windowDisplay = new MyWindow(); // Create a new window display
}
DX3D::MyGame::~MyGame() {}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝

//* ╔═══════════════════╗
//* ║ Getters & Setters ║
//* ╚═══════════════════╝
bool DX3D::MyGame::IsRunning() {
    return this->running;
}