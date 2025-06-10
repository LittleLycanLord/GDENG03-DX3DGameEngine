#include "Graphics/MyGraphicsEngine.hpp"

DX3D::MyGraphicsEngine* DX3D::MyGraphicsEngine::instance = nullptr;

using namespace DX3D;

extern const std::wstring LAYOUT_SHADER_DIRECTORY;
extern bool LOG_INFO_GRAPHICS_ENGINE;
extern bool LOG_INFO_VERTEX_SHADER;
extern bool LOG_INFO_PIXEL_SHADER;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MyGraphicsEngine::MyGraphicsEngine() {
    if (LOG_INFO_GRAPHICS_ENGINE) std::cout << "[INFO]: MyGraphicsEngine constructed" << std::endl;

    try {
        this->renderSystem = new MyRenderSystem();
        if (!this->renderSystem) {
            std::cerr << "[ERROR]: Failed to allocate MyRenderSystem in MyGraphicsEngine::Initialize" << std::endl;
            throw std::exception("Failed to allocate MyRenderSystem in MyGraphicsEngine::Initialize");
        }
    }
    catch (const std::exception& ex) {
        std::cerr << "[ERROR]: Exception in MyGraphicsEngine: " << ex.what() << std::endl;
    }
    try {
        this->textureManager = new MyTextureManager();
        if (!this->textureManager) {
            std::cerr << "[ERROR]: Failed to allocate MyTextureManager in MyGraphicsEngine::Initialize" << std::endl;
            throw std::exception("Failed to allocate MyTextureManager in MyGraphicsEngine::Initialize");
        }
    }
    catch (const std::exception& ex) {
        std::cerr << "[ERROR]: Exception in MyGraphicsEngine: " << ex.what() << std::endl;
    }
    try {
        this->meshManager = new MyMeshManager();
        if (!this->meshManager) {
            std::cerr << "[ERROR]: Failed to allocate MyMeshManager in MyGraphicsEngine::Initialize" << std::endl;
            throw std::exception("Failed to allocate MyMeshManager in MyGraphicsEngine::Initialize");
        }
    }
    catch (const std::exception& ex) {
        std::cerr << "[ERROR]: Exception in MyGraphicsEngine: " << ex.what() << std::endl;
    }

    //* Layout Shader Application
    void* layoutShaderByteCode = nullptr;
    size_t layoutShaderSize = 0;
    if (!this->renderSystem->CompileVertexShader(
        LAYOUT_SHADER_DIRECTORY.c_str(), "main", &layoutShaderByteCode, &layoutShaderSize)) {
        throw std::exception("Failed to compile layout shader!");
        return;
    }

    memcpy(this->layoutShaderByteCode, layoutShaderByteCode, layoutShaderSize);
    this->layoutShaderSize = layoutShaderSize;

    this->renderSystem->ReleaseCompiledShader();
}
MyGraphicsEngine::~MyGraphicsEngine() {
    if (LOG_INFO_GRAPHICS_ENGINE) std::cout << "[INFO]: MyGraphicsEngine destructed" << std::endl;

    MyGraphicsEngine::instance = nullptr;

    if (this->renderSystem) {
        delete this->renderSystem;
        this->renderSystem = nullptr;
        if (LOG_INFO_GRAPHICS_ENGINE) std::cout << "[INFO]: MyRenderSystem released" << std::endl;
    }
    if (this->textureManager) {
        delete this->textureManager;
        this->textureManager = nullptr;
        if (LOG_INFO_GRAPHICS_ENGINE) std::cout << "[INFO]: MyTextureManager released" << std::endl;
    }
    if (this->meshManager) {
        delete this->meshManager;
        this->meshManager = nullptr;
        if (LOG_INFO_GRAPHICS_ENGINE) std::cout << "[INFO]: MyMeshManager released" << std::endl;
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
        if (LOG_INFO_GRAPHICS_ENGINE) std::cout << "[INFO]: MyGraphicsEngine released" << std::endl;
    }
    else {
        throw std::exception("MyGraphicsEngine is already null in MyGraphicsEngine::Release");
    }
}
void MyGraphicsEngine::GetShaderByteCodeAndSize(void** shaderByteCode, size_t* shaderSize) {
    *shaderByteCode = this->layoutShaderByteCode;
    *shaderSize = this->layoutShaderSize;
}
//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝