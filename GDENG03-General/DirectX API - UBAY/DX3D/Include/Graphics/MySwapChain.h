

#pragma once
#include <Graphics/MyGraphicsResource.h>

namespace DX3D {
	class MySwapChain final : public MyGraphicsResource {
		//* ╔════════════╗
		//* ║ Attributes ║
		//* ╚════════════╝
	private:
		Microsoft::WRL::ComPtr<IDXGISwapChain>swapChain{};
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>rtv{};

		friend class MyDeviceContext;
	public:

		//* ╔════════════════════════════╗
		//* ║ Constructors & Destructors ║
		//* ╚════════════════════════════╝
	public:
		MySwapChain(const SwapChainDesc& desc, const GraphicsResourceDesc& gDesc);

		//* ╔═══════════╗
		//* ║ Functions ║
		//* ╚═══════════╝
	private:
		void reloadBuffers();
	public:
		void present(bool vsync = false);
		//* ╔════════════════════════════════╗
		//* ║ Virtual / Overridden Functions ║
		//* ╚════════════════════════════════╝
	protected:
	public:

		//* ╔═══════════════════╗
		//* ║ Getters & Setters ║
		//* ╚═══════════════════╝
	public:
	};
} // namespace DX3D

