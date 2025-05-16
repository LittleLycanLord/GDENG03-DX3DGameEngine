
#pragma once
#include <Core/DX3DCommon.h>
#include <Core/MyBase.h>
#include <Graphics/GraphicsLogUtils.h>

#include <d3d11.h>
#include <wrl.h>

namespace DX3D {
	struct GraphicsResourceDesc {
		BaseDescription base;
		std::shared_ptr<const MyGraphicsDevice> graphicsDevice;
		ID3D11Device& device;
		IDXGIFactory& factory;
	};

	class MyGraphicsResource : public MyBase {
		//* ╔════════════╗
		//* ║ Attributes ║
		//* ╚════════════╝
	private:
	protected:
		std::shared_ptr<const MyGraphicsDevice>graphicsDevice;
		ID3D11Device&device;
		IDXGIFactory&factory;

	public:

		//* ╔════════════════════════════╗
		//* ║ Constructors & Destructors ║
		//* ╚════════════════════════════╝
	public:
		explicit MyGraphicsResource(const GraphicsResourceDesc& desc) :
			MyBase(desc.base),
			graphicsDevice(desc.graphicsDevice),
			device(desc.device),
			factory(desc.factory) {
		}

		//* ╔═══════════╗
		//* ║ Functions ║
		//* ╚═══════════╝
	private:
	public:

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

