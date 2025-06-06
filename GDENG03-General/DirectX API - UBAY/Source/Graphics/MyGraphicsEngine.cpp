#include "Graphics/MyGraphicsEngine.hpp"

using namespace DX3D;

extern bool LOG_INFO_RENDER_SYSTEM;
extern bool LOG_INFO_VERTEX_SHADER;
extern bool LOG_INFO_PIXEL_SHADER;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MyGraphicsEngine::MyGraphicsEngine() {
    if (LOG_INFO_RENDER_SYSTEM) std::cout << "[INFO] : MyGraphicsEngine constructed" << std::endl;
}
MyGraphicsEngine::~MyGraphicsEngine() {
    if (LOG_INFO_RENDER_SYSTEM) std::cout << "[INFO] : MyGraphicsEngine destructed" << std::endl;
}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝
bool MyGraphicsEngine::Initialize() {
    if (LOG_INFO_RENDER_SYSTEM) std::cout << "[INFO] : MyGraphicsEngine::Initialize called" << std::endl;
    this->renderSystem = new MyRenderSystem();
    this->renderSystem->Initialize();
    return true;
}

bool MyGraphicsEngine::Release() {
    if (LOG_INFO_RENDER_SYSTEM) std::cout << "[INFO] : MyGraphicsEngine::Release called" << std::endl;
    if (this->renderSystem) {
        delete this->renderSystem;
        this->renderSystem = nullptr;
        if (LOG_INFO_RENDER_SYSTEM) std::cout << "[INFO] : MyRenderSystem released" << std::endl;
    }
    else {
        throw std::exception("MyRenderSystem is already null in MyGraphicsEngine::Release");
    }
    return true;
}

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝