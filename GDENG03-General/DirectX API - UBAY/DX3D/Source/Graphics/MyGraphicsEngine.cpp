#include <Graphics/MyGraphicsEngine.h>
#include <Graphics/MyGraphicsDevice.h>
#include <Graphics/MyDeviceContext.h>
#include <Graphics/MySwapChain.h>

using namespace DX3D;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
DX3D::MyGraphicsEngine::MyGraphicsEngine(const GraphicsEngineDescription& description) : MyBase(description.base) {
	graphicsDevice = std::make_shared<MyGraphicsDevice>(GraphicsDeviceDescription{ logger });

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

MyVertexBuffer* DX3D::MyGraphicsEngine::createVertexBuffer() {
	return new MyVertexBuffer();
}

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝

//* ╔═══════════════════╗
//* ║ Getters & Setters ║
//* ╚═══════════════════╝