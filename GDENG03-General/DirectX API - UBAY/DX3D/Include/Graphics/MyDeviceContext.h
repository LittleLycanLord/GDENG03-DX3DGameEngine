

#pragma once
#include <Graphics/MyGraphicsResource.h>
#include <Math/MyVec4.h>

namespace DX3D {
	class MyDeviceContext final : public MyGraphicsResource {
		//* ╔════════════╗
		//* ║ Attributes ║
		//* ╚════════════╝
	private:
		Microsoft::WRL::ComPtr<ID3D11DeviceContext>context{};
		friend class MyGraphicsDevice;

	public:

		//* ╔════════════════════════════╗
		//* ║ Constructors & Destructors ║
		//* ╚════════════════════════════╝
	public:
		explicit MyDeviceContext(const GraphicsResourceDesc& gDesc);

		//* ╔═══════════╗
		//* ║ Functions ║
		//* ╚═══════════╝
	private:
	public:
		void clearAndSetBackBuffer(const MySwapChain& swapChain, const MyVec4& color);

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


