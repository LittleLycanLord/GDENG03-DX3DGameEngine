#include <Game/MyDisplay.h>
#include <Graphics/MyGraphicsDevice.h>

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
DX3D::MyDisplay::MyDisplay(const DisplayDesc& desc) : MyWindow(desc.window) {
	m_swapChain = desc.graphicsDevice.createSwapChain({ m_handle, m_size });
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
	return *m_swapChain;
}