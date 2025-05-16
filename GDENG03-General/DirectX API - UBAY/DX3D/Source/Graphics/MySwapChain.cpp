#include <Graphics/MySwapChain.h>

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
DX3D::MySwapChain::MySwapChain(const SwapChainDesc& desc, const GraphicsResourceDesc& gDesc) :
	MyGraphicsResource(gDesc) {
	DXGI_SWAP_CHAIN_DESC dxgiDesc{};

	dxgiDesc.BufferDesc.Width = max(1, desc.winSize.width);
	dxgiDesc.BufferDesc.Height = max(1, desc.winSize.height);
	dxgiDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	dxgiDesc.BufferCount = 2;
	dxgiDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	dxgiDesc.OutputWindow = static_cast<HWND>(desc.winHandle);
	dxgiDesc.SampleDesc.Count = 1;
	dxgiDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	dxgiDesc.Windowed = TRUE;

	DX3DGraphicsLogThrowOnFail(factory.CreateSwapChain(&device, &dxgiDesc, &swapChain),
		"CreateSwapChain failed.");

	reloadBuffers();
}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝
void DX3D::MySwapChain::present(bool vsync) {
	DX3DGraphicsLogThrowOnFail(swapChain->Present(vsync, 0),
		"Present failed.");
}

void DX3D::MySwapChain::reloadBuffers() {
	Microsoft::WRL::ComPtr<ID3D11Texture2D> buffer{};
	DX3DGraphicsLogThrowOnFail(swapChain->GetBuffer(0, IID_PPV_ARGS(&buffer)),
		"GetBuffer failed.");
	DX3DGraphicsLogThrowOnFail(device.CreateRenderTargetView(buffer.Get(), nullptr, &rtv),
		"CreateRenderTargetView failed.");
}


//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝

//* ╔═══════════════════╗
//* ║ Getters & Setters ║
//* ╚═══════════════════╝
