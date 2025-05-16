

#include <Graphics/MyGraphicsEngine.h>
#include <Graphics/MyGraphicsDevice.h>
#include <Graphics/MyDeviceContext.h>
#include <Graphics/MySwapChain.h>

using namespace DX3D;

DX3D::MyGraphicsEngine::MyGraphicsEngine(const GraphicsEngineDesc& desc) : MyBase(desc.base) {
	m_graphicsDevice = std::make_shared<MyGraphicsDevice>(GraphicsDeviceDesc{ m_logger });

	auto& device = *m_graphicsDevice;
	m_deviceContext = device.createDeviceContext();

}

DX3D::MyGraphicsEngine::~MyGraphicsEngine() {
}

MyGraphicsDevice& DX3D::MyGraphicsEngine::getGraphicsDevice() noexcept {
	return *m_graphicsDevice;
}

void DX3D::MyGraphicsEngine::render(MySwapChain& swapChain) {
	auto& context = *m_deviceContext;
	context.clearAndSetBackBuffer(swapChain, { 1,0,0,1 });


	auto& device = *m_graphicsDevice;
	device.executeCommandList(context);
	swapChain.present();
}
