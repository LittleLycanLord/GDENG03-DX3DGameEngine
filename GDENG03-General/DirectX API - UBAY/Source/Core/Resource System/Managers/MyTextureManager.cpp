#include "Core/Resource System/Managers/MyTextureManager.hpp"

using namespace DX3D;

extern bool LOG_INFO_TEXTURE_MANAGER;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MyTextureManager::MyTextureManager() {
    if (LOG_INFO_TEXTURE_MANAGER) std::cout << "[INFO]: MyTextureManager constructed" << std::endl;
}
MyTextureManager::~MyTextureManager() {
    if (LOG_INFO_TEXTURE_MANAGER) std::cout << "[INFO]: MyTextureManager destructed" << std::endl;
}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝
MyResource* MyTextureManager::CreateResourceFromFileConcrete(const wchar_t* resourcePath) {
    if (!resourcePath) {
        std::cerr << "[ERROR]: Resource path is empty in MyTextureManager::CreateResourceFromFileConcrete" << std::endl;
        throw std::invalid_argument("Resource path cannot be empty");
        return nullptr;
    }
    if (LOG_INFO_TEXTURE_MANAGER) std::wcout << L"[INFO]: Loading texture from file: " << resourcePath << std::endl;
    MyTexture* newTexture = nullptr;
    try {
        newTexture = new MyTexture(resourcePath);
    }
    catch (const std::exception& ex) {
        std::cerr << "[ERROR]: Failed to create MyTexture from file: " << ex.what() << std::endl;
        throw std::runtime_error("Failed to create MyTexture from file");
        return nullptr;
    }
    if (LOG_INFO_TEXTURE_MANAGER) std::wcout << L"[INFO]: Texture loaded successfully: " << resourcePath << std::endl;
    return newTexture;
}
