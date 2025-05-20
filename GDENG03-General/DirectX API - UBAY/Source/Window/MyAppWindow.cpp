#include "Window/MyAppWindow.hpp"

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
DX3D::MyAppWindow::MyAppWindow() {}
DX3D::MyAppWindow::~MyAppWindow() {}

//* ╔═════════════════════════════════╗
//* ║ Magical Shit I Don't Understand ║
//* ╚═════════════════════════════════╝

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝
void DX3D::MyAppWindow::OnCreate() {
    MyWindow::OnCreate();
    MyGraphicsEngine::GetInstance()->Initialize();
}
void DX3D::MyAppWindow::OnUpdate() {}
void DX3D::MyAppWindow::OnDestroy() {
    MyWindow::OnDestroy();
    MyGraphicsEngine::GetInstance()->Release();
}