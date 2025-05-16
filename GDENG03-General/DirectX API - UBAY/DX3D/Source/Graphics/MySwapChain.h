

#pragma once
#include <Graphics/MyGraphicsResource.h>

namespace DX3D {
	class MySwapChain final : public MyGraphicsResource {
	public:
		MySwapChain(const SwapChainDesc& desc, const GraphicsResourceDesc& gDesc);

		void present(bool vsync = false);
	private:
		void reloadBuffers();
	private:
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_swapChain{};
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_rtv{};

		friend class MyDeviceContext;
	};
}

