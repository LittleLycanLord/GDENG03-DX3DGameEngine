#include "Graphics/MyGraphicsEngine.hpp"

DX3D::MyGraphicsEngine* DX3D::MyGraphicsEngine::instance = nullptr;

using namespace DX3D;

extern bool LOG_INFO_RENDER_SYSTEM;
extern bool LOG_INFO_VERTEX_SHADER;
extern bool LOG_INFO_PIXEL_SHADER;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MyGraphicsEngine::MyGraphicsEngine() {
    if (LOG_INFO_RENDER_SYSTEM) std::cout << "[INFO] : MyGraphicsEngine constructed" << std::endl;

    try {
        this->renderSystem = new MyRenderSystem();
        if (!this->renderSystem) {
            std::cerr << "[ERROR] Failed to allocate MyRenderSystem in MyGraphicsEngine::Initialize" << std::endl;
            throw std::exception("Failed to allocate MyRenderSystem in MyGraphicsEngine::Initialize");
        }

    }
    catch (const std::exception& ex) {
        std::cerr << "[ERROR] Exception in MyGraphicsEngine: " << ex.what() << std::endl;

    }
}
MyGraphicsEngine::~MyGraphicsEngine() {
    if (LOG_INFO_RENDER_SYSTEM) std::cout << "[INFO] : MyGraphicsEngine destructed" << std::endl;

    MyGraphicsEngine::instance = nullptr;

    if (this->renderSystem) {
        this->renderSystem = nullptr;
        if (LOG_INFO_RENDER_SYSTEM) std::cout << "[INFO] : MyRenderSystem released" << std::endl;
    }
}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝
void MyGraphicsEngine::Create() {
    if (MyGraphicsEngine::instance) {
        std::cerr << "[ERROR]: MyGraphicsEngine already created" << std::endl;
        throw std::exception("MyGraphicsEngine already created");
    }
    MyGraphicsEngine::instance = new MyGraphicsEngine();
}
void MyGraphicsEngine::Release() {
    if (MyGraphicsEngine::instance) {
        delete MyGraphicsEngine::instance;
        MyGraphicsEngine::instance = nullptr;
        if (LOG_INFO_RENDER_SYSTEM) std::cout << "[INFO] : MyGraphicsEngine released" << std::endl;
    }
    else {
        throw std::exception("MyGraphicsEngine is already null in MyGraphicsEngine::Release");
    }
}
//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝