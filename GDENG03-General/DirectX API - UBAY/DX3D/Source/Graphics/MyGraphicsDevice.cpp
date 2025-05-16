

#include <Graphics/MyGraphicsDevice.h>
#include <Graphics/GraphicsLogUtils.h>
#include <Graphics/MySwapChain.h>
#include <Graphics/MyDeviceContext.h>

using namespace DX3D;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
DX3D::MyGraphicsDevice::MyGraphicsDevice(const GraphicsDeviceDesc& desc) : MyBase(desc.base) {
	D3D_FEATURE_LEVEL featureLevel{};
	UINT createDeviceFlags{};

#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	DX3DGraphicsLogThrowOnFail(D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags,
		NULL, 0, D3D11_SDK_VERSION,
		&m_d3dDevice, &featureLevel, &m_d3dContext),
		"Direct3D11 initialization failed.");

	DX3DGraphicsLogThrowOnFail(m_d3dDevice->QueryInterface(IID_PPV_ARGS(&m_dxgiDevice)),
		"QueryInterface failed to retrieve IDXGIDevice.");

	DX3DGraphicsLogThrowOnFail(m_dxgiDevice->GetParent(IID_PPV_ARGS(&m_dxgiAdapter)),
		"GetParent failed to retrieve IDXGIAdapter.");

	DX3DGraphicsLogThrowOnFail(m_dxgiAdapter->GetParent(IID_PPV_ARGS(&m_dxgiFactory)),
		"GetParent failed to retrieve IDXGIFactory.");

}

DX3D::MyGraphicsDevice::~MyGraphicsDevice() {
}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝
SwapChainPointer DX3D::MyGraphicsDevice::createSwapChain(const SwapChainDesc& desc) {
	return std::make_shared<MySwapChain>(desc, getGraphicsResourceDesc());
}

DeviceContextPointer DX3D::MyGraphicsDevice::createDeviceContext() {
	return std::make_shared<MyDeviceContext>(getGraphicsResourceDesc());
}

void DX3D::MyGraphicsDevice::executeCommandList(MyDeviceContext& context) {
	Microsoft::WRL::ComPtr<ID3D11CommandList> list{};
	DX3DGraphicsLogThrowOnFail(context.m_context->FinishCommandList(false, &list),
		"FinishCommandList failed.");
	m_d3dContext->ExecuteCommandList(list.Get(), false);
}

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝

//* ╔═══════════════════╗
//* ║ Getters & Setters ║
//* ╚═══════════════════╝
GraphicsResourceDesc DX3D::MyGraphicsDevice::getGraphicsResourceDesc() const noexcept {
	return { {m_logger}, shared_from_this(), *m_d3dDevice.Get(), *m_dxgiFactory.Get() };
}