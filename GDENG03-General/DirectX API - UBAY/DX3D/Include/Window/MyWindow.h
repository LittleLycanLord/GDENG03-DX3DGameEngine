#pragma once
#include <Core/MyBase.h>
#include <Core/DX3DCommon.h>

namespace DX3D {
	class MyWindow : public MyBase {
		//* ╔════════════╗
		//* ║ Attributes ║
		//* ╚════════════╝

	private:
	protected:
		void* handle{};
		MyRectangle size{};
	public:

		//* ╔════════════════════════════╗
		//* ║ Constructors & Destructors ║
		//* ╚════════════════════════════╝
	public:
		explicit MyWindow(const WindowDescription& desc);
		virtual ~MyWindow() override;

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

