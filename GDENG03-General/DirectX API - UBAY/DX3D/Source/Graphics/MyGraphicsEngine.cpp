

#include <Graphics/MyGraphicsEngine.h>
#include <Graphics/MyGraphicsDevice.h>
#include <Graphics/MyDeviceContext.h>
#include <Graphics/MySwapChain.h>

using namespace DX3D;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
DX3D::MyGraphicsEngine::MyGraphicsEngine(const GraphicsEngineDesc& desc) : MyBase(desc.base) {
	graphicsDevice = std::make_shared<MyGraphicsDevice>(GraphicsDeviceDesc{logger });

	auto& device = *graphicsDevice;
	deviceContext = device.createDeviceContext();

}

DX3D::MyGraphicsEngine::~MyGraphicsEngine() {
}
//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝
void DX3D::MyGraphicsEngine::render(MySwapChain& swapChain) {
	auto& context = *deviceContext;
	context.clearAndSetBackBuffer(swapChain, { 1,0,0,1 });


	auto& device = *graphicsDevice;
	device.executeCommandList(context);
	swapChain.present();
}
MyGraphicsDevice& DX3D::MyGraphicsEngine::getGraphicsDevice() noexcept {
	return *graphicsDevice;
}

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝

//* ╔═══════════════════╗
//* ║ Getters & Setters ║
//* ╚═══════════════════╝