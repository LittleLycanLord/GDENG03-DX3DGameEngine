#pragma once
#include <Graphics/MyGraphicsResource.h>
#include <Core/DX3DCommon.h>
#include <Core/MyBase.h>
#include <d3d11.h>
#include <wrl.h>

namespace DX3D {
	class MyGraphicsDevice final : public MyBase, public std::enable_shared_from_this<MyGraphicsDevice> {
		//* ╔════════════╗
		//* ║ Attributes ║
		//* ╚════════════╝
	private:
		Microsoft::WRL::ComPtr<ID3D11Device>d3dDevice{};
		Microsoft::WRL::ComPtr<ID3D11DeviceContext>d3dContext{};
		Microsoft::WRL::ComPtr<IDXGIDevice>dxgiDevice{};
		Microsoft::WRL::ComPtr<IDXGIAdapter>dxgiAdapter{};
		Microsoft::WRL::ComPtr<IDXGIFactory>dxgiFactory{};
	public:

		//* ╔════════════════════════════╗
		//* ║ Constructors & Destructors ║
		//* ╚════════════════════════════╝
	public:
		explicit MyGraphicsDevice(const GraphicsDeviceDesc& desc);
		virtual ~MyGraphicsDevice() override;

		//* ╔═══════════╗
		//* ║ Functions ║
		//* ╚═══════════╝
	private:
		GraphicsResourceDesc getGraphicsResourceDesc() const noexcept;
	public:
		SwapChainPointer createSwapChain(const SwapChainDesc& desc);
		DeviceContextPointer createDeviceContext();
		void executeCommandList(MyDeviceContext& context);

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


