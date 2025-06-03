#include "Game/Input System/MyInputSystem.hpp"

using namespace DX3D;

extern bool LOG_INFO_INPUTSYSTEM;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MyInputSystem::MyInputSystem() {}
MyInputSystem::~MyInputSystem() {}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝
void MyInputSystem::Update() {
    if (LOG_INFO_INPUTSYSTEM) std::cout << "[INFO] : MyInputSystem::Update called" << std::endl;
    if (GetKeyboardState(this->newKeyStates)) {
        for (int key = 0; key < 256; key++) {
            if (this->newKeyStates[key] & 0x80) { // Check if the key is pressed
                if (!(this->oldKeyStates[key] & 0x80)) {
                    for (auto& listenerPair : this->inputListeners) {
                        MyInputListener* listener = listenerPair.first;
                        if (listener != nullptr) {
                            listener->OnKeyDown(key);
                            if (LOG_INFO_INPUTSYSTEM) std::cout << "[INFO] : Key " << key << " pressed in MyInputSystem::Update" << std::endl;
                        }
                    }
                }
                for (auto& listenerPair : this->inputListeners) {
                    MyInputListener* listener = listenerPair.first;
                    if (listener != nullptr) {
                        listener->OnKeyHold(key);
                        if (LOG_INFO_INPUTSYSTEM) std::cout << "[INFO] : Key " << key << " being held in MyInputSystem::Update" << std::endl;
                    }
                }
            }
            else {
                if (this->oldKeyStates[key] & 0x80) {
                    for (auto& listenerPair : this->inputListeners) {
                        MyInputListener* listener = listenerPair.first;
                        if (listener != nullptr) {
                            listener->OnKeyUp(key);
                            if (LOG_INFO_INPUTSYSTEM) std::cout << "[INFO] : Key " << key << " released in MyInputSystem::Update" << std::endl;
                        }
                    }
                }
            }
        }
        memcpy(this->oldKeyStates, this->newKeyStates, sizeof(this->newKeyStates));
    }
    else {
        std::cout << "[ERROR] : Failed to get keyboard state in MyInputSystem::Update" << std::endl;
        return;
    }
}
void MyInputSystem::AddListener(MyInputListener* inputListener) {
    if (inputListener == nullptr) {
        std::cout << "[ERROR] : inputListener is null in MyInputSystem::AddListener" << std::endl;
        return;
    }
    auto iterator = this->inputListeners.find(inputListener);
    if (iterator != this->inputListeners.end()) {
        if (LOG_INFO_INPUTSYSTEM) std::cout << "[WARNING] : Listener already exists in MyInputSystem::AddListener" << std::endl;
    }
    else {
        this->inputListeners.insert(std::make_pair<MyInputListener*, MyInputListener*>(std::forward<MyInputListener*>(inputListener), std::forward<MyInputListener*>(inputListener)));
        if (LOG_INFO_INPUTSYSTEM) std::cout << "[INFO] : Listener added successfully in MyInputSystem::AddListener" << std::endl;
    }
}
void MyInputSystem::RemoveListener(MyInputListener* inputListener) {
    if (inputListener == nullptr) {
        std::cout << "[ERROR] : inputListener is null in MyInputSystem::RemoveListener" << std::endl;
        return;
    }
    auto iterator = this->inputListeners.find(inputListener);
    if (iterator != this->inputListeners.end()) {
        this->inputListeners.erase(iterator);
        if (LOG_INFO_INPUTSYSTEM) std::cout << "[INFO] : Listener removed successfully in MyInputSystem::RemoveListener" << std::endl;
    }
    else {
        if (LOG_INFO_INPUTSYSTEM) std::cout << "[WARNING] : Listener not found in MyInputSystem::RemoveListener" << std::endl;
    }
}

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝
