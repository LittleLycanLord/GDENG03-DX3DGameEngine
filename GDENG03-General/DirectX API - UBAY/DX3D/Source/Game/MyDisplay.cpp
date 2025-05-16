#include <Game/MyDisplay.h>
#include <Graphics/MyGraphicsDevice.h>

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
DX3D::MyDisplay::MyDisplay(const DisplayDescription& description) : MyWindow(description.window) {
	swapChain = description.graphicsDevice.createSwapChain({handle,size });
}
//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝

//* ╔═══════════════════╗
//* ║ Getters & Setters ║
//* ╚═══════════════════╝
DX3D::MySwapChain& DX3D::MyDisplay::getSwapChain() noexcept {
	return *swapChain;
}