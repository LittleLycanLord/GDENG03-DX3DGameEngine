#include "Core/Resource System/Managers/MyMeshManager.hpp"

using namespace DX3D;

extern bool LOG_INFO_MESH_MANAGER;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MyMeshManager::MyMeshManager() {
    if (LOG_INFO_MESH_MANAGER) std::cout << "[INFO]: MyMeshManager constructed" << std::endl;
}
MyMeshManager::~MyMeshManager() {
    if (LOG_INFO_MESH_MANAGER) std::cout << "[INFO]: MyMeshManager destructed" << std::endl;
}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝
MyResource* MyMeshManager::CreateResourceFromFileConcrete(const wchar_t* resourcePath) {
    if (!resourcePath) {
        std::cerr << "[ERROR]: Resource path is empty in MyMeshManager::CreateResourceFromFileConcrete" << std::endl;
        throw std::invalid_argument("Resource path cannot be empty");
        return nullptr;
    }
    if (LOG_INFO_MESH_MANAGER) std::wcout << L"[INFO]: Loading mesh from file: " << resourcePath << std::endl;
    MyMesh* newMesh = nullptr;
    try {
        newMesh = new MyMesh(resourcePath);
    }
    catch (const std::exception& ex) {
        std::cerr << "[ERROR]: Failed to create MyMesh from file: " << ex.what() << std::endl;
        throw std::runtime_error("Failed to create MyMesh from file");
        return nullptr;
    }
    if (LOG_INFO_MESH_MANAGER) std::wcout << L"[INFO]: Mesh loaded successfully: " << resourcePath << std::endl;
    return newMesh;
}
