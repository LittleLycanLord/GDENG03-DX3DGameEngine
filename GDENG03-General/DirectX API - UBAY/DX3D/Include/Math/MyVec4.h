#pragma once
#include <Core/DX3DCore.h>

namespace DX3D {
	class MyVec4 {
		//* ╔════════════╗
		//* ║ Attributes ║
		//* ╚════════════╝
	private:
	public:
		float x{}, y{}, z{}, w{};

		//* ╔════════════════════════════╗
		//* ║ Constructors & Destructors ║
		//* ╚════════════════════════════╝
	public:
		MyVec4() = default;
		MyVec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

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

