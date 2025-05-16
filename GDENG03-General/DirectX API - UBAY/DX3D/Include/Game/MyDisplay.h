#pragma once
#include <Window/MyWindow.h>

namespace DX3D {
	class MyDisplay final : public MyWindow {
		//* ╔════════════╗
		//* ║ Attributes ║
		//* ╚════════════╝
	private:
		SwapChainPointer m_swapChain{};
	public:

		//* ╔════════════════════════════╗
		//* ║ Constructors & Destructors ║
		//* ╚════════════════════════════╝
	public:
		explicit MyDisplay(const DisplayDesc& desc);
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
		MySwapChain& getSwapChain() noexcept;
	};
} // namespace DX3D

