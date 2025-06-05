#include "Core/Input System/MyInputSystem.hpp"

using namespace DX3D;

extern bool LOG_INFO_INPUTSYSTEM_KEYBOARD;
extern bool LOG_INFO_INPUTSYSTEM_MOUSE;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MyInputSystem::MyInputSystem() {}
MyInputSystem::~MyInputSystem() {}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝
void MyInputSystem::Update() {

    //* Mouse Update
    POINT currentMousePosition = {};
    GetCursorPos(&currentMousePosition);

    if (this->firstFrame) {
        this->oldMousePosition.x = currentMousePosition.x;
        this->oldMousePosition.y = currentMousePosition.y;
        this->firstFrame = false;
    }

    this->newMousePosition.x = currentMousePosition.x;
    this->newMousePosition.y = currentMousePosition.y;

    this->deltaMousePosition.x = this->newMousePosition.x - this->oldMousePosition.x;
    this->deltaMousePosition.y = this->newMousePosition.y - this->oldMousePosition.y;

    if (this->newMousePosition.x != this->oldMousePosition.x || this->newMousePosition.y != this->oldMousePosition.y) {
        for (auto& listenerPair : this->inputListeners) {
            MyInputListener* listener = listenerPair.first;
            if (listener != nullptr) {
                listener->OnMouseMove(this->deltaMousePosition);
                if (LOG_INFO_INPUTSYSTEM_MOUSE) std::cout << "[INFO] : Mouse moved to (" << this->newMousePosition.x << ", " << this->newMousePosition.y << ") in MyInputSystem::Update" << std::endl;
            }
        }
    }

    this->oldMousePosition = this->newMousePosition;


    //* Keyboard Update
    if (LOG_INFO_INPUTSYSTEM_KEYBOARD) std::cout << "[INFO] : MyInputSystem::Update called" << std::endl;
    if (GetKeyboardState(this->newKeyStates)) {
        for (int key = 0; key < 256; key++) {
            if (this->newKeyStates[key] & 0x80) { // Check if the key is pressed
                if (!(this->oldKeyStates[key] & 0x80)) {
                    for (auto& listenerPair : this->inputListeners) {
                        MyInputListener* listener = listenerPair.first;
                        if (listener != nullptr) {
                            if (key == VK_LBUTTON)
                                listener->OnLMBDown(this->newMousePosition);
                            if (key == VK_RBUTTON)
                                listener->OnRMBDown(this->newMousePosition);
                            listener->OnKeyDown(key);
                            if (LOG_INFO_INPUTSYSTEM_KEYBOARD) std::cout << "[INFO] : Key " << key << " pressed in MyInputSystem::Update" << std::endl;
                        }
                    }
                }
                for (auto& listenerPair : this->inputListeners) {
                    MyInputListener* listener = listenerPair.first;
                    if (listener != nullptr) {
                        if (key == VK_LBUTTON)
                            listener->OnLMBHold(this->newMousePosition);
                        if (key == VK_RBUTTON)
                            listener->OnRMBHold(this->newMousePosition);
                        listener->OnKeyHold(key);
                        if (LOG_INFO_INPUTSYSTEM_KEYBOARD) std::cout << "[INFO] : Key " << key << " being held in MyInputSystem::Update" << std::endl;
                    }
                }
            }
            else {
                if (this->oldKeyStates[key] & 0x80) {
                    for (auto& listenerPair : this->inputListeners) {
                        MyInputListener* listener = listenerPair.first;
                        if (listener != nullptr) {
                            if (key == VK_LBUTTON)
                                listener->OnLMBUp(this->newMousePosition);
                            if (key == VK_RBUTTON)
                                listener->OnRMBUp(this->newMousePosition);
                            listener->OnKeyUp(key);
                            if (LOG_INFO_INPUTSYSTEM_KEYBOARD) std::cout << "[INFO] : Key " << key << " released in MyInputSystem::Update" << std::endl;
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
        if (LOG_INFO_INPUTSYSTEM_KEYBOARD) std::cout << "[WARNING] : Listener already exists in MyInputSystem::AddListener" << std::endl;
    }
    else {
        this->inputListeners.insert(std::make_pair<MyInputListener*, MyInputListener*>(std::forward<MyInputListener*>(inputListener), std::forward<MyInputListener*>(inputListener)));
        if (LOG_INFO_INPUTSYSTEM_KEYBOARD) std::cout << "[INFO] : Listener added successfully in MyInputSystem::AddListener" << std::endl;
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
        if (LOG_INFO_INPUTSYSTEM_KEYBOARD) std::cout << "[INFO] : Listener removed successfully in MyInputSystem::RemoveListener" << std::endl;
    }
    else {
        if (LOG_INFO_INPUTSYSTEM_KEYBOARD) std::cout << "[WARNING] : Listener not found in MyInputSystem::RemoveListener" << std::endl;
    }
}
void MyInputSystem::SetCursorPosition(const MyScreenPoint& position) {
    SetCursorPos(position.x, position.y);
}
void MyInputSystem::SetCursorVisibility(bool showCursor) {
    ShowCursor(showCursor);
}

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝
