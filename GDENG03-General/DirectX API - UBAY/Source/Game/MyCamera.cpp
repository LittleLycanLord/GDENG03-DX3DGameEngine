#include "Game/MyCamera.hpp"

using namespace DX3D;

extern bool LOG_INFO_CAMERA;
extern bool LOG_INFO_CONSTANT_BUFFER;
extern bool LOG_INFO_INPUT_SYSTEM_KEYBOARD;
extern bool LOG_INFO_INPUT_SYSTEM_MOUSE;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MyCamera::MyCamera(float windowWidth, float windowHeight) : windowWidth(windowWidth), windowHeight(windowHeight) {}
MyCamera::~MyCamera() {}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝
void MyCamera::Update(float deltaTime) {
    this->deltaTime = deltaTime;
    this->UpdateTransformation();
}
void MyCamera::UpdateTransformation() {
    this->viewMatrix.SetIdentity();
    this->viewMatrix *= MyMatrix4x4::RotationX(this->rotationInput.x);
    this->viewMatrix *= MyMatrix4x4::RotationY(this->rotationInput.y);
    this->viewMatrix *= MyMatrix4x4::RotationZ(this->rotationInput.z);
    this->cameraPosition += this->viewMatrix.GetTranslation() +
        (this->viewMatrix.GetZDirection() * this->moveSpeed * this->deltaTime) * this->movementInput.y +
        (this->viewMatrix.GetYDirection() * this->moveSpeed * this->deltaTime) * this->movementInput.z +
        (this->viewMatrix.GetXDirection() * this->moveSpeed * this->deltaTime) * this->movementInput.x;
    this->viewMatrix *= MyMatrix4x4::Translation(this->cameraPosition);
    this->viewMatrix.SetInverse();
}

void MyCamera::SetOrthographicLeftHand(float width, float height, float nearPlane, float farPlane) {
    this->projectionMatrix.SetMatrix(MyMatrix4x4::OrthographicLeftHand(width, height, nearPlane, farPlane));
}

void MyCamera::SetPerspectiveLeftHand(float fieldOfView, float aspectRatio, float nearPlane, float farPlane) {
    this->projectionMatrix.SetMatrix(MyMatrix4x4::PerspectiveLeftHand(fieldOfView, aspectRatio, nearPlane, farPlane));
}

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝
void MyCamera::OnKeyDown(int keyCode) {
    if (LOG_INFO_CAMERA) std::cout << "[INFO]: MyCamera::OnKeyDown called with keyCode: " << keyCode << std::endl;

    // Handle key down events here
    switch (keyCode) {
    default:
        if (LOG_INFO_INPUT_SYSTEM_KEYBOARD) std::cout << "[INFO]: Unhandled key down: " << keyCode << std::endl;
        break;
    }
}

void MyCamera::OnKeyHold(int keyCode) {
    if (LOG_INFO_CAMERA) std::cout << "[INFO]: MyCamera::OnKeyDown called with keyCode: " << keyCode << std::endl;

    // Handle key down events here
    switch (keyCode) {
    case 'W':
        // this->cameraPosition.z += moveSpeed * this->deltaTime; // Move camera forward
        this->movementInput.y = 1.0f; // Move camera forward
        break;
    case 'A':
        // this->cameraPosition.x -= moveSpeed * this->deltaTime; // Move camera left
        this->movementInput.x = -1.0f; // Move camera left
        break;
    case 'S':
        // this->cameraPosition.z -= moveSpeed * this->deltaTime; // Move camera backward
        this->movementInput.y = -1.0f; // Move camera backward
        break;
    case 'D':
        // this->cameraPosition.x += moveSpeed * this->deltaTime; // Move camera right
        this->movementInput.x = 1.0f; // Move camera right
        break;
    case 'Q':
        // this->cameraPosition.y += moveSpeed * this->deltaTime; // Move camera up
        this->movementInput.z = 1.0f; // Move camera up
        break;
    case 'E':
        // this->cameraPosition.y -= moveSpeed * this->deltaTime; // Move camera down
        this->movementInput.z = -1.0f; // Move camera down
        break;
    default:
        break;
    }
}

void MyCamera::OnKeyUp(int keyCode) {
    if (LOG_INFO_CAMERA) std::cout << "[INFO]: MyCamera::OnKeyUp called with keyCode: " << keyCode << std::endl;

    // Handle key up events here
    if (LOG_INFO_CAMERA) std::cout << "[INFO]: MyCamera::OnKeyDown called with keyCode: " << keyCode << std::endl;

    // Handle key down events here
    switch (keyCode) {
    case 'W':
        this->movementInput.y = 0.0f;
        break;
    case 'A':
        this->movementInput.x = 0.0f;
        break;
    case 'S':
        this->movementInput.y = 0.0f;
        break;
    case 'D':
        this->movementInput.x = 0.0f;
        break;
    case 'Q':
        this->movementInput.z = 0.0f;
        break;
    case 'E':
        this->movementInput.z = 0.0f;
        break;
    default:
        break;
    }
}

void MyCamera::OnMouseMove(const MyScreenPoint& deltaMousePosition) {
    if (LOG_INFO_INPUT_SYSTEM_MOUSE) std::cout << "[INFO]: MyCamera::OnMouseMove called with deltaMousePosition: ("
        << deltaMousePosition.x << ", " << deltaMousePosition.y << ")" << std::endl;

    // this->xRotation += deltaMousePosition.y * this->rotationSpeed * this->deltaTime;
    // this->yRotation += deltaMousePosition.x * this->rotationSpeed * this->deltaTime;
}

void MyCamera::OnLMBDown(const MyScreenPoint& mousePosition) {
    if (LOG_INFO_INPUT_SYSTEM_MOUSE) std::cout << "[INFO]: MyCamera::OnLMBDown called with mousePosition: ("
        << mousePosition.x << ", " << mousePosition.y << ")" << std::endl;
}

void MyCamera::OnLMBHold(const MyScreenPoint& deltaMousePosition) {
    std::cout << "[INFO]: deltaMousePosition.y -> " << deltaMousePosition.y << std::endl;
    this->rotationInput.x += (float)(deltaMousePosition.y * (this->rotationSpeed * this->deltaTime));
}

void MyCamera::OnLMBUp(const MyScreenPoint& mousePosition) {
    if (LOG_INFO_INPUT_SYSTEM_MOUSE) std::cout << "[INFO]: MyCamera::OnLMBUp called with mousePosition: ("
        << mousePosition.x << ", " << mousePosition.y << ")" << std::endl;
}

void MyCamera::OnRMBDown(const MyScreenPoint& mousePosition) {
    if (LOG_INFO_INPUT_SYSTEM_MOUSE) std::cout << "[INFO]: MyCamera::OnRMBDown called with mousePosition: ("
        << mousePosition.x << ", " << mousePosition.y << ")" << std::endl;
}

void MyCamera::OnRMBHold(const MyScreenPoint& deltaMousePosition) {
    std::cout << "[INFO]: deltaMousePosition.x -> " << deltaMousePosition.x << std::endl;
    this->rotationInput.y += (float)(deltaMousePosition.x * (this->rotationSpeed * this->deltaTime));
}

void MyCamera::OnRMBUp(const MyScreenPoint& mousePosition) {
    if (LOG_INFO_INPUT_SYSTEM_MOUSE) std::cout << "[INFO]: MyCamera::OnRMBUp called with mousePosition: ("
        << mousePosition.x << ", " << mousePosition.y << ")" << std::endl;
}
